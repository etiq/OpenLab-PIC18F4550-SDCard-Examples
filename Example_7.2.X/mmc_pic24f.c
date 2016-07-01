/*------------------------------------------------------------------------/
/  MMCv3/SDv1/SDv2 (in SPI mode) control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/


#include <pic18f4620.h>
#include <xc.h>
#include "diskio.h"
#define _XTAL_FREQ 20000000

/* Port Controls  (Platform dependent) */
#define CS_LOW()  LATB4 = 0	/* MMC CS = L */
#define CS_HIGH() LATB4 = 1	/* MMC CS = H */
#define INS	!(PORTB & (1<<11))	/* Card detected   (yes:true, no:false, default:true) */
#define WP	(PORTB & (1<<10))	/* Write protected (yes:true, no:false, default:false) */

#define	FCLK_SLOW()			/* Set slow clock (100k-400k) */
#define	FCLK_FAST()			/* Set fast clock (depends on the CSD) */


/*----------------------------------------COMMANDS----------------------------------------------------*/

/* Definitions for MMC/SDC command */
#define CMD0   (0)			/* GO_IDLE_STATE */
#define CMD1   (1)			/* SEND_OP_COND */
#define ACMD41 (41|0x80)	/* SEND_OP_COND (SDC) */
#define CMD8   (8)			/* SEND_IF_COND */
#define CMD9   (9)			/* SEND_CSD */
#define CMD10  (10)			/* SEND_CID */
#define CMD12  (12)			/* STOP_TRANSMISSION */
#define ACMD13 (13|0x80)	/* SD_STATUS (SDC) */
#define CMD16  (16)			/* SET_BLOCKLEN */
#define CMD17  (17)			/* READ_SINGLE_BLOCK */
#define CMD18  (18)			/* READ_MULTIPLE_BLOCK */
#define CMD23  (23)			/* SET_BLOCK_COUNT */
#define ACMD23 (23|0x80)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24  (24)			/* WRITE_BLOCK */
#define CMD25  (25)			/* WRITE_MULTIPLE_BLOCK */
#define CMD41  (41)			/* SEND_OP_COND (ACMD) */
#define CMD55  (55)			/* APP_CMD */
#define CMD58  (58)			/* READ_OCR */


static volatile
DSTATUS Stat = STA_NOINIT;	/* Disk status */

static volatile
UINT Timer1, Timer2;		/* 1000Hz decrement timer */

static
UINT CardType;





/*------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Power Control  (Platform dependent)                                   */
/*-----------------------------------------------------------------------*/
/* When the target system does not support socket power control, there   */
/* is nothing to do in these functions.                                  */



/*-----------------------------------------------------------------------*/
/* Transmit/Receive data to/from MMC via SPI  (Platform dependent)       */
/*-----------------------------------------------------------------------*/


/* Alternative macro to transfer data fast */
#define XMIT_SPI_MULTI(src,cnt) {UINT c=cnt/2; const BYTE *p=src; do {SSPBUF=*p++; while(!SSPBUF); SSPBUF; SSPBUF=*p++; while(!SSPBUF); SSPBUF; } while(--c);}
#define RCVR_SPI_MULTI(dst,cnt)	{UINT c=cnt/2; BYTE *p=dst; do {SSPBUF=0xFF; while(!SSPBUF); *p++=SSPBUF; SSPBUF=0xFF; while(!SSPBUF); *p++=SSPBUF; } while(--c);}



/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (void)
{
	BYTE d;

	Timer2 = 500;	/* Wait for ready in timeout of 500ms */
	do {
		d = WriteSPI_(0xFF);
	} while ((d != 0xFF) && Timer2);

	return (d == 0xFF) ? 1 : 0;
}



/*-----------------------------------------------------------------------*/
/* Deselect the card and release SPI bus                                 */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();
	WriteSPI_(0xFF);		/* Dummy clock (force DO hi-z for multiple slave SPI) */
}



/*-----------------------------------------------------------------------*/
/* Select the card and wait ready                                        */
/*-----------------------------------------------------------------------*/

static
int select (void)	/* 1:Successful, 0:Timeout */
{
	CS_LOW();
	WriteSPI_(0xFF);		/* Dummy clock (force DO enabled) */

	if (wait_ready()) return 1;	/* OK */
	deselect();
	return 0;	/* Timeout */
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from MMC                                        */
/*-----------------------------------------------------------------------*/

static
int rcvr_datablock (	/* 1:OK, 0:Failed */
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token;


	Timer1 = 100;
	do {							/* Wait for data packet in timeout of 100ms */
		token = WriteSPI_(0xFF);
	} while ((token == 0xFF) && Timer1);

	if(token != 0xFE) return 0;		/* If not valid data token, retutn with error */

	RCVR_SPI_MULTI(buff, btr);		/* Receive the data block into buffer */
	WriteSPI_(0xFF);					/* Discard CRC */
	WriteSPI_(0xFF);

	return 1;						/* Return with success */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to MMC                                             */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* 512 byte data block to be transmitted */
	BYTE token			/* Data token */
)
{
	BYTE resp;


	if (!wait_ready()) return 0;

	WriteSPI_(token);		/* Xmit a token */
	if (token != 0xFD) {	/* Not StopTran token */
		XMIT_SPI_MULTI(buff, 512);	/* Xmit the data block to the MMC */
		WriteSPI_(0xFF);				/* CRC (Dummy) */
		WriteSPI_(0xFF);
		resp = WriteSPI_(0xFF);		/* Receive a data response */
		if ((resp & 0x1F) != 0x05)	/* If not accepted, return with error */
			return 0;
	}

	return 1;
}
#endif



/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static
BYTE send_cmd (
	BYTE cmd,		/* Command byte */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;

/* ACMD<n> is the command sequense of CMD55-CMD<n> */


	/* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect();
		if (!select()) return 0xFF;
	}

	/* Send command packet */
	WriteSPI_(0x40 | cmd);			/* Start + Command index */
	WriteSPI_((BYTE)(arg >> 24));	/* Argument[31..24] */
	WriteSPI_((BYTE)(arg >> 16));	/* Argument[23..16] */
	WriteSPI_((BYTE)(arg >> 8));		/* Argument[15..8] */
	WriteSPI_((BYTE)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) + Stop */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) + Stop */
	WriteSPI_(n);

	/* Receive command response */
	if (cmd == CMD12) WriteSPI_(0xFF);	/* Skip a stuff byte on stop to read */
	n = 10;							/* Wait for a valid response in timeout of 10 attempts */
	do
		res = WriteSPI_(0xFF);
	while ((res & 0x80) && --n);

	return res;			/* Return with the response value */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv		/* Physical drive nmuber (0) */
)
{
	BYTE n, cmd, ty, ocr[4];


	if (pdrv) return STA_NOINIT;		/* Supports only single drive */
	if (Stat & STA_NODISK) return Stat;	/* No card in the socket */
						/* Force socket power on */
	FCLK_SLOW();
	for (n = 10; n; n--) WriteSPI_(0xFF);	/* 80 dummy clocks */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* Enter Idle state */
		Timer1 = 1000;						/* Initialization timeout of 1000 msec */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = WriteSPI_(0xFF);			/* Get trailing return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* The card can work at vdd range of 2.7-3.6V */
				while (Timer1 && send_cmd(ACMD41, 0x40000000));	/* Wait for leaving idle state (ACMD41 with HCS bit) */
				if (Timer1 && send_cmd(CMD58, 0) == 0) {			/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = WriteSPI_(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2|CT_BLOCK : CT_SD2;	/* SDv2 */
				}
			}
		} else {							/* SDv1 or MMCv3 */
			if (send_cmd(ACMD41, 0) <= 1) 	{
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
			}
			while (Timer1 && send_cmd(cmd, 0));		/* Wait for leaving idle state */
			if (!Timer1 || send_cmd(CMD16, 512) != 0)	/* Set read/write block length to 512 */
				ty = 0;
		}
	}
	CardType = ty;
	deselect();

	if (ty) {			/* Initialization succeded */
		Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT */
		FCLK_FAST();
	} else {			/* Initialization failed */
	}

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0) */
)
{
	if (pdrv) return STA_NOINIT;	/* Supports only single drive */
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0) */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	DWORD sector,	/* Start sector number (LBA) */
	UINT count		/* Sector count (1..128) */
)
{
	if (pdrv || !count)
            return RES_PARERR;
	if (Stat & STA_NOINIT)
            return RES_NOTRDY;

	if (!(CardType & CT_BLOCK))
            sector *= 512;	/* Convert to byte address if needed */

	if (count == 1)
        {		/* Single block read */
		if ((send_cmd(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
			&& rcvr_datablock(buff, 512))
			count = 0;
	}
	else {				/* Multiple block read */
		if (send_cmd(CMD18, sector) == 0)
                {	/* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock(buff, 512)) break;
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,				/* Physical drive nmuber (0) */
	const BYTE *buff,		/* Pointer to the data to be written */
	DWORD sector,			/* Start sector number (LBA) */
	UINT count				/* Sector count (1..128) */
)
{
	if (pdrv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;

	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	if (count == 1)
            {		/* Single block write */
		if ((send_cmd(CMD24, sector) == 0)	/* WRITE_BLOCK */
		&& xmit_datablock(buff, 0xFE))
		count = 0;
            }
	else
            {				/* Multiple block write */
		if (CardType & CT_SDC)
                    send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sector) == 0)
                    {	/* WRITE_MULTIPLE_BLOCK */
			do
                        {
                         if (!xmit_datablock(buff, 0xFC)) break;
                            buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD))	/* STOP_TRAN token */
                            count = 1;
                    }
            }
	deselect();
	return count ? RES_ERROR : RES_OK;
}
#endif



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD csz;


	if (pdrv) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	res = RES_ERROR;
	switch (cmd) {
	case CTRL_SYNC :	/* Flush write-back cache, Wait for end of internal process */
		if (select()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (WORD) */
		if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
			if ((csd[0] >> 6) == 1) {	/* SDv2? */
				csz = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(DWORD*)buff = csz << 10;
			} else {					/* SDv1 or MMCv3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csz = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(DWORD*)buff = csz << (n - 9);
			}
			res = RES_OK;
		}
		break;

	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sectors (DWORD) */
		if (CardType & CT_SD2) {	/* SDv2? */
			if (send_cmd(ACMD13, 0) == 0) {		/* Read SD status */
				WriteSPI_(0xFF);
				if (rcvr_datablock(csd, 16)) {				/* Read partial block */
					for (n = 64 - 16; n; n--) WriteSPI_(0xFF);	/* Purge trailing data */
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
		} else {					/* SDv1 or MMCv3 */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
				if (CardType & CT_SD1) {	/* SDv1 */
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
				} else {					/* MMCv3 */
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		break;

	case MMC_GET_TYPE :		/* Get card type flags (1 byte) */
		*ptr = CardType;
		res = RES_OK;
		break;

	case MMC_GET_CSD :	/* Receive CSD as a data block (16 bytes) */
		if ((send_cmd(CMD9, 0) == 0)	/* READ_CSD */
			&& rcvr_datablock(buff, 16))
			res = RES_OK;
		break;

	case MMC_GET_CID :	/* Receive CID as a data block (16 bytes) */
		if ((send_cmd(CMD10, 0) == 0)	/* READ_CID */
			&& rcvr_datablock(buff, 16))
			res = RES_OK;
		break;

	case MMC_GET_OCR :	/* Receive OCR as an R3 resp (4 bytes) */
		if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
			for (n = 0; n < 4; n++)
				*((BYTE*)buff+n) = WriteSPI_(0xFF);
			res = RES_OK;
		}
		break;

	case MMC_GET_SDSTAT :	/* Receive SD statsu as a data block (64 bytes) */
		if ((CardType & CT_SD2) && send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
			WriteSPI_(0xFF);
			if (rcvr_datablock(buff, 64))
				res = RES_OK;
		}
		break;

	default:
		res = RES_PARERR;
	}

	deselect();

	return res;
}
#endif


/*-----------------------------------------------------------------------*/
/* Device Timer Driven Procedure                                         */
/*-----------------------------------------------------------------------*/
/* This function must be called by timer interrupt in period of 1ms      */

void disk_timerproc (void)
{
	BYTE s;
	UINT n;


	n = Timer1;					/* 1000Hz decrement timer with zero stopped */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;


	/* Update socket status */

	s = Stat;

	if (WP) s |= STA_PROTECT;
	else		s &= ~STA_PROTECT;

	if (INS) s &= ~STA_NODISK;
	else		 s |= (STA_NODISK | STA_NOINIT);

	Stat = s;
}


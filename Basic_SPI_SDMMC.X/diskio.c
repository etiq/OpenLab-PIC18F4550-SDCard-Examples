/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"

extern  void WriteSPI_();
extern  void SPI_cmd();
extern  void ReadSPI_();
extern  void dummy_clocks();
extern  void response();
extern  void proceed();

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

void reset()
{
    int i = 0, count = 0;
    unsigned char buff;
    unsigned char sd_cmd0[]={0X40,0X00,0X00,0X00,0X00,0X95};
    /*SOFTWARE RESET COMMAND*/
    do{
    dummy_clocks(8);    
    SPI_cmd(sd_cmd0);
    proceed();
    do{   
        buff = response();
        count++;
      }while((buff!=0X01) && (count<10) );
      count = 0;
    }while(buff!=0X01);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      putsUART("\n\rSD Card Inserted\n\r");
      Delay_s(2);
    return;
}



DSTATUS disk_initialize (void)
{
	DSTATUS stat;

    int i = 0, count1 = 0, count2 = 0;
    unsigned char buff;
    unsigned char sd_cmd1[]={0X41,0X00,0X00,0X00,0X00,0XFF};
    unsigned char sd_cmd55[]={0X77,0X00,0X00,0X00,0X00,0X95};
    unsigned char sd_acmd41[]={0X69,0X40,0X00,0X00,0X00,0X95};
    unsigned char sd_cmd8[]={0X48,0X00,0X00,0X01,0XAA,0X87}; //Required Only for Initializing High Capacity Cards
    unsigned char sd_cmd58[]={0X7A,0X00,0X00,0X00,0X00,0XFF}; //Required Only for Initializing High Capacity Cards
    unsigned char block_len[]={0X50,0X00,0X00,0X02,0X00,0XFF};
    reset(); //RESET THE SD CARD

    //SEND CMD1
    dummy_clocks(8);    
    SPI_cmd(sd_cmd1);
    proceed();
    do{   
        buff = response();
      }while(buff!=0x01);
    //SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)
//    dummy_clocks(8);
//      putsUART("COMMAND1");
      Delay_s(1);
//      WriteUART("\n\r");
      
if (buff == 0x01)
{                    
    //SEND CMD55 + ACMD41     
    delay_ms(1);
    count1 = 0;    
    dummy_clocks(8);    
      do{
        WriteUART("\n\r");
        count2 = 0;
        SPI_cmd(sd_cmd55);
        buff = 0XFF;
        //CHECK THE BUFFER FOR A 0X00 RESPONSE BIT
        do{
        buff = response();
        count2++;
        }while((buff!=0X01)&&(count2<10));
        
        delay_ms(1);
        count2 = 0;
        dummy_clocks(8);
        SPI_cmd(sd_acmd41);
        buff = 0XFF;
        //CHECK THE BUFFER FOR A 0X00 RESPONSE BIT
        do{
        buff = response();
        count2++;
        }while((buff!=0X00)&&(count2<10));
     }while(buff != 0X00);
       //Send CMD58
  //Reset counter 1
  count1 = 0;
  //Delay before sending command
  delay_ms(1);
  
putsUART("SUCCESS\n\r");
stat = 0;
Delay_s(2);     
}

else if(buff == 0x05)
{
    putsUART("Error!!!\n\r");
    Delay_s(3);
}
      Delay_s(1);
//SETTING BLOCK LENGTH TO 512 Bytes
    dummy_clocks(8);    
    SPI_cmd(block_len);
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
    //SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)
      putsUART("512 Bytes Set\n\r");
      Delay_s(2);
  

     
	// Put your code here

	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* buff,		/* Pointer to the destination object */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Offset in the sector */
	UINT count		/* Byte count (bit15:destination) */
)
{
	DRESULT res;

	// Put your code here

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
	BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res;


	if (!buff) {
		if (sc) {

			// Initiate write process

		} else {

			// Finalize write process

		}
	} else {

		// Send data to the disk

	}

	return res;
}


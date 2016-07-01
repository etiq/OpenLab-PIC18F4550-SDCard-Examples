#include <p18cxxx.h>
#include <plib\spi.h>
#include "spi_1.h"
#define SPI_IO_V3
#define SPI_V1
/********************************************************************
*   Function Name:  OpenSPI                                         *
*   Return Value:   void                                            *
*   Parameters:     SSP peripheral setup bytes                      *
*   Description:    This function sets up the SSP module on a       *
*                   PIC18Cxxx device for use with a Microchip SPI   *
*                   EEPROM device or SPI bus device.                *
********************************************************************/
extern unsigned char readdata;

void ReadBUF(void)
{
    unsigned char u;
u = SSPBUF;
u = SSPBUF;
}

void spi_read(void)
{
    SSPBUF = 0xff;
    while (BF == 0);
    readdata = SSPBUF;
}


 /*__________________________________XC8 library functions_____________________________________*/

void spi_init(void)
{
    TRIS_SDI = 1;       // define SDI input
    TRIS_SCK = 0;       // define clock pin as output
    TRIS_CS = 0;        // CS - RB4 output
    TRIS_SDO = 0;       //SD0 as output
    CS = 1;
    SCK = 0;
    SDO = 0;
    SSPCON1 = 0b00100010;
    SMP = 1;
    CKE = 1;
    CKP = 0;
    SSPEN = 1;
}

void OpenSPI_( unsigned char sync_mode, unsigned char bus_mode, unsigned char smp_phase)
{
  SSPSTAT &= 0x3F;                // power on state
  SSPCON1 = 0x00;                 // power on state
  SSPCON1 |= sync_mode;           // select serial mode       (0b00000010 - SPI Master mode, clock = Fosc/64)
  SSPSTAT |= smp_phase;           // select data input sample phase

  SSPSTATbits.CKE = 1;        // data transmitted on rising edge
  SSPCON1bits.CKP = 0;
TRIS_SDI = 1;       // define SDI input
TRIS_SCK = 0;       // define clock pin as output
TRIS_CS = 0;       // CS - RA5 output
TRIS_SDO = 0;       //SD0 as output        MOSI
SSPCON1 |= SSPENB;          // enable synchronous serial port,  0b00100000  Enable serial port and configures SCK, SDO, SDI
}
signed char WriteSPI_( unsigned char data_out )
{
  unsigned char TempVar;
  TempVar = SSPBUF;           // Clears BF
  PIR1bits.SSPIF = 0;         // Clear interrupt flag
  SSPCON1bits.WCOL = 0;			//Clear any previous write collision
  SSPBUF = data_out;           // write byte to SSPBUF register
  if ( SSPCON1 & 0x80 )        // test if write collision occurred
   return ( -1 );              // if WCOL bit is set return negative #
  else
    while( !PIR1bits.SSPIF );  // wait until bus cycle complete
    return ( 0 );                // if WCOL bit is not set return non-negative#
}

unsigned char ReadSPI_( void )
{
  unsigned char TempVar;
  TempVar = SSPBUF;        // Clear BF
  PIR1bits.SSPIF = 0;      // Clear interrupt flag
  SSPBUF = 0x00;           // initiate bus cycle
  while(!PIR1bits.SSPIF);  // wait until cycle complete
  return ( SSPBUF );       // return with byte read
}

unsigned char DataRdySPI_( void )
{
  if ( SSPSTATbits.BF )
    return ( +1 );                // data in SSPBUF register
  else
    return ( 0 );                 // no data in SSPBUF register
}
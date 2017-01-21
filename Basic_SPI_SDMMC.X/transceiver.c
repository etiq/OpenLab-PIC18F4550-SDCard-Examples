/*
 * File:   transceiver.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 20, 2017, 4:44 PM
 */


#include <xc.h>
#include "my_sw_uart.h"
#include "my_openuart.h"

unsigned char ReadSPI__( void )
{
  unsigned char TempVar;
  TempVar = SSPBUF;        // Clear BF
  PIR1bits.SSPIF = 0;      // Clear interrupt flag
  SSPBUF = 0xFF;           // initiate bus cycle. SEND 0XFF instead of 0X00
  //while ( !SSPSTATbits.BF );                  // wait until cycle complete
  while(!PIR1bits.SSPIF);  // wait until cycle complete
  return ( SSPBUF );       // return with byte read 
}

signed char WriteSPI_( unsigned char data_out )
{
  unsigned char TempVar;  
  
  //LATB4 = 0; //CS Low
  TempVar = SSPBUF;           // Clears BF
  PIR1bits.SSPIF = 0;         // Clear interrupt flag
  SSPCON1bits.WCOL = 0;			//Clear any previous write collision
  SSPBUF = data_out;           // write byte to SSPBUF register
  if ( SSPCON1 & 0x80 )        // test if write collision occurred
  {
      return ( -1 );              // if WCOL bit is set return negative #
  }
  else
   // while( !SSPSTATbits.BF );  // wait until bus cycle complete 
    while( !PIR1bits.SSPIF ); // wait until bus cycle complete   
    //LATB4 = 1; //CS High
    return ( 0 );                // if WCOL bit is not set return non-negative#
}

void Command(char cmd, unsigned long int arg, char CRCbits)
{
    unsigned char temp;
    WriteSPI_(0xff);
    WriteSPI_(cmd);
    WriteSPI_((unsigned char) (arg >> 24));
    WriteSPI_((unsigned char) (arg >> 16));
    WriteSPI_((unsigned char) (arg >> 8));
    WriteSPI_((unsigned char)  arg);
    WriteSPI_(CRCbits);
}

/*SOFTWARE RESET FUNCTION FOR SD_CARD*/
 unsigned char response()
{
    unsigned char buff;
    LATB4 = 0;//CS low   
    buff=ReadSPI__();   //read buffer (R1) should be 0x01 = idle mode   
    LATB4 = 1;//CS high
    return buff;
}

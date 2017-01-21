/*
 * File:   my_sw_uart.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 20, 2017, 4:44 PM
 */


#include <p18cxxx.h>
#include "delay.h"
// Half Bit Delay = ((((2*20Mhz)/(8*9600))+1)/2)-9 cycles = 251.91
void DelayRXHalfBitUART_( void )
{
	Delay100TCYx(2); 
    Delay10TCYx(5); 
    Delay1TCY(); Delay1TCY();
}

// Full Bit Delay = ((((2*20Mhz)/(4*9600))+1)/2)-14 cycles = 507.33
void DelayRXBitUART_( void )
{
	Delay100TCYx( 5 );
	Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY();
	Delay1TCY(); Delay1TCY();
}

// Full TX Bit Delay = ((((2*10Mhz)/(4*9600))+1)/2)-12 cycles = 248.92
//20MHz
void DelayTXBitUART_( void )
{
	Delay100TCYx( 5 ); //500 Cycles
    //Delay10TCYx( 4 );
	Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY();
	Delay1TCY(); Delay1TCY(); Delay1TCY(); Delay1TCY(); //9 Cycles
}

/* **********************************************************************
 *      Function Name:  WriteUART                                       *
 *      Return Value:   void                                            *
 *      Parameters:     data: byte to send out the UART                 *
 *      Description:    This routine sends a byte out the TXD pin.      *
 *      Special Note:   The user must provide a routine:                * 
 *                      DelayTXBit():                                   *
 *                        DelayTXBit should have:                       *
 *                              8 Tcy for overhead                      *
 *                              2 Tcy call to DelayTXBit                *
 *                              ? Tcy                                   *
 *                              2 Tcy for return from DelayTXBit        *
 *                      = (((2*OSC_FREQ)/(4*BAUDRATE))+1)/2  Tcy        *
 *********************************************************************** */
void WriteUART_(unsigned char uartdata)
{
	unsigned char bitcount = 8;
	 
	//start
    PORTDbits.RD4 = 0;
    DelayTXBitUART_();

	while (bitcount--){
        
		PORTDbits.RD4 = (uartdata&0x01);
		DelayTXBitUART_();
		uartdata >>= 1;
	}
	
	//stop
	PORTDbits.RD4 = 1;
	DelayTXBitUART_();
}

void putsUART_(char *data)
{
	do
	{    // Transmit a byte
		WriteUART_(*data);
	} while( *data++ );
}
/* **********************************************************************
 *      Function Name:  ReadUART                                        *
 *      Return Value:   char: received data                             *
 *      Parameters:     void                                            *
 *      Description:    This routine waits for a start bit, and then    *
 *                      reads all 8-bits.                               *
 *      Special Note:   The user must provide two routines:             *
 *                      DelayRXHalfBit():                               *
 *                        DelayRXHalfBit should have:                   *
 *                              5 Tcy for overhead                      *
 *                              2 Tcy call to DelayRXHalfBit            *
 *                              ? Tcy                                   *
 *                              2 Tcy for return from DelayRXHalfBit    *
 *                              = (((2*OSC_FREQ)/(8*BAUDRATE))+1)/2 Tcy *
 *                      DelayRXBit():                                   *
 *                        DelayRXBit should have:                       *
 *                              10 Tcy for overhead                     *
 *                              2 Tcy call to DelayRXBit                *
 *                              ? Tcy                                   *
 *                              2 Tcy for return from DelayRXBit        *
 *                              = (((2*OSC_FREQ)/(4*BAUDRATE))+1)/2 Tcy *
 *********************************************************************** */

unsigned char ReadUART_(void)
{
	unsigned char bitcount=8;
	unsigned char uartdata,datauart = 0, c, d = 0X01;
    int i;
	while (PORTDbits.RD5){
		while (PORTDbits.RD5);
		DelayRXHalfBitUART_();
	}

	while (bitcount--){
		DelayRXBitUART_();
		c = ((PORTDbits.RD5)?1:0);
//        c = c&d;
//        d = d<<1;
		uartdata = ((uartdata<<1)|(c));
	} //uartdata obtained here will be in the reversed order

        datauart |= (((uartdata<<7)&0X80) | ((uartdata>>7)&0X01));
        datauart |= (((uartdata<<5)&0X40) | ((uartdata>>5)&0X02));
        datauart |= (((uartdata<<3)&0X20) | ((uartdata>>3)&0X04));
        datauart |= (((uartdata<<1)&0X10) | ((uartdata>>1)&0X08));
     //datauart is the reverse of uartdata
        return datauart;
}

/********************************************************************
 *    Function Name:  getsUART                                       *
 *    Return Value:   void                                           *
 *    Parameters:     buffer: pointer to string                      *
 *                    len: length of characters to receive           *
 *    Description:    This routine receives a string of characters   *
 *                    from the SW UART of length specified by len.   *
 ********************************************************************/
void getsUART_(char *buffer, unsigned char len)
{
	char i;    // Length counter

	for(i=0;i<len;i++)   // Only retrieve len characters
	{
		*buffer = ReadUART_(); // Get a character from the USART
		// and save in the string
		buffer++;          // Increment the string pointer
	}
}

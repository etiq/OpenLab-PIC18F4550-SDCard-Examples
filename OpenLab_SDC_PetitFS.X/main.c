/*
 * File:   main.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 27, 2017, 4:44 PM
 */


#include "pic_18f4550.h"
#include <spi.h>
#include <usart.h>
#include <sw_uart.h>
#include "config.h"
#include "delay.h"
#include "pff.h"
#include "diskio.h"


#define FOSC 20000000
#define Baud 9600
#define spbrg ((FOSC/Baud)/64)-1                                 /*
                                      ((FOSC/Desired Baud Rate)/64) ? 1
                                       = ((16000000/9600)/64) ? 1        */
                                       /*void Open1USART ( unsigned char config,  unsigned int spbrg);*/
BYTE sector_buffer[512];
unsigned char *rd;
unsigned char Result;
static unsigned char str[512];
BYTE s;
DWORD fileSize;
BYTE txt[20];
BYTE data_buffer_32[32];
extern void readover(int);

void soft_hard_init()
{
    unsigned char sync_mode=0;
    unsigned char bus_mode=0;
    unsigned char smp_phase=0;
    int i = 0;

    CloseSPI();

    ADCON1 = 0X0F;   //Make RB4, RB1, RB0 pins digital
    CMCON |= 7;
    
    TRISA5 = 0; //WORK AROUND FOR A HARDWARE ISSUE
    LATA5 = 0;
    TRISB4 = 0; //CS
    
    sync_mode = SPI_FOSC_64;
    bus_mode = MODE_00;
    smp_phase = SMPMID;
    OpenSPI(sync_mode, bus_mode, smp_phase);
}


signed char WriteSPI_( unsigned char data_out )
{
  unsigned char TempVar;  
  
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
    return ( 0 );                // if WCOL bit is not set return non-negative#
}

void Command(char cmd, unsigned long int arg, char CRCbits)
{
    WriteSPI_(0xff);
    WriteSPI_(0b01000000 | cmd);
    WriteSPI_((unsigned char) (arg >> 24));
    WriteSPI_((unsigned char) (arg >> 16));
    WriteSPI_((unsigned char) (arg >> 8));
    WriteSPI_((unsigned char)  arg);
    WriteSPI_(CRCbits);
}

void dummy_clocks(int n)
{
    int i = 0;
    delay_ms(1);
    LATB0 = 1;
    for(i=0;i<n;i++)
    {
        LATB4 = 1; //CS High
        WriteSPI(0XFF);
        LATB4 = 0; //CS High        
    }
}

void proceed()
{
    LATB4 = 0; //CS Low
    WriteSPI(0XFF); // Give Time For SD_CARD To Proceed
    LATB4 = 1; //CS High
}

unsigned char ReadSPI_( void )
{
  unsigned char TempVar;
  TempVar = SSPBUF;        // Clear BF
  PIR1bits.SSPIF = 0;      // Clear interrupt flag
  SSPBUF = 0xFF;           // initiate bus cycle
  //while ( !SSPSTATbits.BF );                  // wait until cycle complete
  while(!PIR1bits.SSPIF);  // wait until cycle complete
  return ( SSPBUF );       // return with byte read 
}
/*SOFTWARE RESET FUNCTION FOR SD_CARD*/
BYTE response()
{
    BYTE buff;
    LATB4 = 0;//CS low   
    buff=ReadSPI_();   //read buffer (R1) should be 0x01 = idle mode   
    LATB4 = 1;//CS high
    return buff;
}

// File to read 
BYTE fileName[10] = {"check.txt"}; //USE SMALLER ARRAY SIZE /testmapp/testtext 
BYTE folder[48] = {""}; 

void main(void) 
{
    FRESULT FResult;
    FATFS fs;
    WORD br;
    soft_hard_init(); // SOFTWARE AND HARWARE INITIALISE FUNCTION
    OpenUART();       // SOFTWARE UART INITIALIZATION

    /*READ FUNCTION*/
    
      	putsUART("\r\nAttempting to mount file system.\r\n");
        proceed();
	if( (FResult = pf_mount(&fs)) == FR_OK )
	{
		putsUART("\r\n\r\nAttempting to open file ");
		putsUART(fileName);
		putsUART(".\r\n");
        putsUART("OPENING THE FILE");
		// open file
		FResult = pf_open("check.txt"/*fileName*/);
        
		if( FResult == FR_OK )
		{
			putsUART("\r\n\r\nStarting to write the file.\r\n");

				// Read 31 bytes from the file                        
            if( (FResult = pf_write("SD_Card", 5, &br)) == FR_OK )
				{
					putsUART("\r\nSuccessfully written");
				} 
				else
				{
					putsUART("\r\nError trying to write to file; ");
					WriteUART(FResult + 0x30);
					putsUART(".\r\n");
					
					while( 1 );
				}

            putsUART("\r\n\r\nStarting to read the file.\r\n");
				
			// read file and print it until it ends
			do
			{
                readover(1); //Set Flag=1 in diskio.c before reading Card Data
				// Read 31 bytes from the file
				if( (FResult = pf_read(data_buffer_32, 31, &br)) == FR_OK )
				{
					// putsUSART needs a C-string (NULL terminated)
					data_buffer_32[br] = 0;
                    break;
					//putsUART(data_buffer_32);
				}
				else
				{
					putsUART("\r\nError trying to read file; ");
					WriteUART(FResult + 0x30);
					putsUART(".\r\n");
					
					while( 1 );
				}
			} while( br == 31 );	// if the pf_Read reads less then 31 bytes the file has ended
		}
		else 
		{
			putsUART("\r\nError trying to open file; ");
			WriteUART(FResult + 0x30);
			putsUART(".\r\n");
			
			while( 1 );
		}
	}
	else
	{
		putsUART("\r\nError trying to mount filesystem; ");
		WriteUART(FResult + 0x30);
		putsUART(".\r\n");
		
		while( 1 );
	}
	
	putsUART("\r\n\r\n");

  	// do a directory listing and list all files on the SD-card
	//scan_files(folder);
		
	// unmount drive
	putsUART("\r\nAttempting to UNmount file system.\r\n");
	
	//FResult = pf_mount(NULL);
	
	if( FResult != FR_OK )
	{
		putsUART("\r\nError trying to UNmount filesystem; ");
		WriteUART(FResult + 0x30);
		putsUART(".\r\n");
		
		while( 1 );
	}	

	putsUART("\r\File system succesfully unmounted.\r\n");
	while(1);
/*WRITE FUNCTION*/
}		

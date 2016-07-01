/*
 * File name            : main.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_17.1 SD card_1 Sector read/write
 *                      : Created on February 19, 2014, 10:20 AM
 *                      : Example code implements SD card File system; file read/write/delete operations.
 */
#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File      */
    #include <plib\usart.h>
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File   */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File      */
	#include <usart.h>
#endif

#if defined(__XC) || defined(HI_TECH_C)
#include <stdint.h>        /* For uint8_t definition        */
#include <stdbool.h>       /* For true/false definition     */
#endif

#if defined(__XC) || defined(__18CXX)
#include <plib\spi.h>
#include <pic18f4620.h>
#include <stdio.h>
#include "config.h"
#include "delay.h"
#include "spi_1.h"
#include "uart.h"
#include "fat_string.h"
#include "fat_filelib.h"
#include "diskio.h"
#include "delay.h"
#endif


#define Fosc 20000000
#define baud 9600
#define config_2 ((Fosc/baud/64)-1)
#define _XTAL_FREQ 20000000

#define FATFS_INC_WRITE_SUPPORT
#define FILE_READ

unsigned char config_1 = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;
unsigned char str[120] = "\n\r and supporting power devices.";
unsigned char str_1[200] = "\0";
unsigned char str_2[200] = "\n\rPakistan Prime Minister Nawaz Sharif calls Narendra Modi and congratulates him on his resounding win in the polls: PTI";

/*------------------------------------Created functions------------------------------------------------*/
//#define media_write_1
#define media_write_2
//#define media_read_1
#define media_read_2

unsigned char readdata;
unsigned char array[41];
int count,i, n;

void command(char command, unsigned long int fourbyte_arg, char CRCbits)
{
    WriteSPI_(0xff);
    ReadBUF();
    WriteSPI_(0b01000000 | command);
    ReadBUF();
    WriteSPI_((unsigned char) (fourbyte_arg >> 24));
    ReadBUF();
    WriteSPI_((unsigned char) (fourbyte_arg >> 16));
    ReadBUF();
    WriteSPI_((unsigned char) (fourbyte_arg >> 8));
    ReadBUF();
    WriteSPI_((unsigned char) fourbyte_arg);
    ReadBUF();
    WriteSPI_(CRCbits);
    spi_read();
}
unsigned char mmc_init(void)
{
    unsigned char u,i;
    LATD = 0;
    CS = 1;
    SDO =0;
    for (u = 0; u <10; u++)
    {
    WriteSPI_(0xFF);
    }
    CS = 0;
    SDO = 0;
    readdata = 0;
/*_____________________      CMD0          ______________________*/
 command(0, 0, 0x95);
do{
   spi_read();
  }while(readdata!= 0x01);
  count = 0;
   __delay_ms(1);
  command(1,  0 , 0xFF);
do{
   spi_read();
   count++;
  }while((readdata!= 0x00)&&(readdata!= 0x01));
   i=0;
  do{
command(55,  0 , 0xFF);
      do{
         spi_read();
        }while((readdata!=0x00)&&(readdata!=0x01)&&(readdata!=0x05));
        command(1,  0 , 0xFF);
        do{
            spi_read();
            }while((readdata!= 0x00)&&(readdata!= 0x01));
  }while(readdata!=00);
   if(readdata != 0x00)
     return(1);
}

#ifdef media_read_1
/*----------------------------------Read function fron LIBRARY--------------------------------------*/

int media_read(unsigned long sector, unsigned char *buffer, unsigned long sector_count)
{

//DRESULT disk_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
/* Physical drive nmuber (0),  Pointer to the data buffer to store read data Start sector number (LBA), Sector count (1..128) */

disk_read (0, buffer, sector, sector_count);
}

/*---------------------------------------------------------------------------------------------------*/
#endif


#ifdef media_read_2
int media_read(unsigned long sector, unsigned char *buffer, unsigned long sector_count)
{
    unsigned long i, Start_Addr;
     
    Start_Addr = sector * 512;
    command(18, Start_Addr, 0xff);
        while (readdata != 0)
        {
        spi_read();
        }
      while (readdata != 0xfe)
        {
        spi_read();
        }                                                               // Add platform specific sector (512 bytes) read code here
        for (i=0;i<sector_count;i++)
        {                                                                        // Add platform specific sector (512 bytes) write code here
            for (n = 0; n < 512; n++)
            {
            spi_read();
            *buffer = readdata;
            buffer++;
            }
        sector ++;
        }
        WriteSPI_(0xff);
        WriteSPI_(0xff);

            command(12, 0, 0xff);
            spi_read();
            while (readdata != 0)
            {
                spi_read();
            }
            while (readdata != 0xff)
            {
                spi_read();
            }
    return 1;
}


#endif
#ifdef media_write_1
int media_write(unsigned long sector, unsigned char *buffer, unsigned long sector_count)
{

 /*   DRESULT disk_write (BYTE pdrv,const BYTE *buff, DWORD sector, UINT count ) Physical drive nmuber (0) , Pointer to the data to be written, Start sector number (LBA), Sector count (1..128)*/

disk_write (0, sector,buffer, sector_count);

}
#endif
/*__________________________________________________________________________________________________________________*/

#ifdef media_write_2

int media_write(unsigned long sector, unsigned char *buffer, unsigned long sector_count)
{
    unsigned long i, Start_Addr, End_Addr;
    Start_Addr = sector * 512;
    command(25, Start_Addr, 0xff);
    while (readdata != 0)
    {
    spi_read();
    }
         WriteSPI_(0xff);
         WriteSPI_(0xff);
         WriteSPI_(0b11111100);
    for (i=0;i<sector_count;i++)
    {                                                                        // Add platform specific sector (512 bytes) write code here
       for ( n = 0; n <512; n++)
        {
        WriteSPI_(*buffer);
        buffer++;
        }
        sector ++;
    }

         WriteSPI_(0xff);
         WriteSPI_(0xff);
         spi_read();
        while ((readdata & 0b00011111) != 0x05)
        {
        spi_read();
        }
        while (readdata != 0xff)
        {
        spi_read();
        }
            WriteSPI_(0xff);
            WriteSPI_(0xff);
            WriteSPI_(0b11111101);                   //stop token
            spi_read();
            spi_read();
            while (readdata != 0xff)
            {
            spi_read();
            }
    return 1;
}

#endif


void Clear_str(unsigned char *buffer)
    {
    while(*buffer)
        {
        *buffer = ' ';
        buffer++;
        }
    }
void main()
{
    unsigned char c;
    ADCON1 = 0x0F;
    CMCON |=0X07;
    TRISD = 0XF0;
    LATD0 = 0;                                                         //  OpenSPI_(SPI_FOSC_64, MODE_01, SMPMID);
    LATD1 = 0;
    LATD2 = 0;
    ConfigUSART(config_1, config_2);
    spi_init();
  __delay_ms(1);
   FL_FILE *file;                                                      // Initialise media
   if(!mmc_init())
   {
    Write_str("\n\rcard initialized successfully...!\r\n");
    Delay_s(2);
   }
   else
    Write_str("\ncard initialization failed...!");                                                                            // Initialise File IO Library
   fl_init();                                                          // Attach media access functions to library
   if (fl_attach_media(media_read, media_write) != FAT_INIT_OK)
    {
     Write_str("ERROR: Media attach failed\n");
     return;
    }                                                                  // List root directory
    fl_listdirectory("/");                                             // Create File
/*****************************           File write mode            ************************************/

 delay_ms(10);
 file = fl_fopen("/START.bin", "w");
  if(file)
    {
    fl_fwrite(str_2,1, sizeof(str_2), file );
    }
 fl_fclose(file);

/************************            File open in Read mode              ******************************/

 delay_ms(10);
 while(1)
  {
    file = fl_fopen("/START", "r");
  if( file)
    {
    fl_fread(str_1,1, sizeof(str_1), file );
    }
  else
      Write_str("file 'START' was not found..!");
      fl_fclose(file);
      Write_str(str_1);
      delay_ms(200);
      Write_str("\n\r");
      Clear_str(str_1);
      }

/********************************************************************************************************/
    fl_listdirectory("/");
    fl_shutdown();
}
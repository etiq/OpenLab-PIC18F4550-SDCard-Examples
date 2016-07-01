/*
 * File name            : main.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_17.2 SD card_2 File system
 *                      : Created on February 19, 2014, 10:20 AM
 *                      : Example code implements SD card File system; file read/write/delete operations.
 * Controller           : PIC18F4620
 */
#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File      */
    #include <plib\usart.h>
    #include <plib\spi.h>
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File   */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File      */
    #include <usart.h>
    #include <plib\spi.h>
#endif

#if defined(__XC) || defined(HI_TECH_C)
#include <stdint.h>        /* For uint8_t definition        */
#include <stdbool.h>       /* For true/false definition     */
#endif

#if defined(__XC) || defined(__18CXX)
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"
#include "delay.h"
#include "spi_1.h"

#include "fat_string.h"
#include "fat_filelib.h"
#include "diskio.h"
#include "delay.h"
#endif
#include "uart.h"
#define Fosc 20000000
#define baud 9600
#define config_2 ((Fosc/baud/64)-1)
#define _XTAL_FREQ 20000000

unsigned char config_1 = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;
unsigned char str[240] = "\0", str_0[] = "                         ";
static unsigned char string[30], s[17] = "\0", m[30] = "\0", str_1[240] = "\0";
unsigned char readdata, x, data = ' ', d;
unsigned char array[41], z, t;
static unsigned char w = 'y';
int count, i, n, j, v, res;
unsigned char c, flag = 0, flag_1=0, f=0;
FL_FILE *file, *fptr;
FL_DIR dptr;
//-----------------------------------------------------------------------------
// fopen: Open or Create a file for reading or writing
//-----------------------------------------------------------------------------

    // Supported Modes:
    // "r" Open a file for reading.
    //        The file must exist.
    // "w" Create an empty file for writing.
    //        If a file with the same name already exists its content is erased and the file is treated as a new empty file.
    // "a" Append to a file.
    //        Writing operations append data at the end of the file.
    //        The file is created if it does not exist.
    // "r+" Open a file for update both reading and writing.
    //        The file must exist.
    // "w+" Create an empty file for both reading and writing.
    //        If a file with the same name already exists its content is erased and the file is treated as a new empty file.
    // "a+" Open a file for reading and appending.
    //        All writing operations are performed at the end of the file, protecting the previous content to be overwritten.
    //        You can reposition (fseek, rewind) the internal pointer to anywhere in the file for reading, but writing operations
    //        will move it back to the end of file.
    //        The file is created if it does not exist.

/*------------------------------------Created functions------------------------------------------------*/

//#define media_write_1
#define media_write_2
//#define media_read_1
#define media_read_2


void File_write(void);


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
    CS  = 1;
    SDO = 0;
    for (u = 0; u <10; u++)
    {
    WriteSPI_(0xFF);
    }
    CS  = 0;
    readdata = 0;
/*_______________________________      CMD0    ___________________________________*/
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


int media_read(unsigned long sector, unsigned char *buffer, unsigned long sector_count)
{

//DRESULT disk_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
/* Physical drive nmuber (0),  Pointer to the data buffer to store read data Start sector number (LBA), Sector count (1..128) */

disk_read (0, buffer, sector, sector_count);
}

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

void Clr_str(unsigned char *buffer)
    {
    while(*buffer)
        {
        *buffer = ' ';
        buffer++;
        }
    }

void Draw_Line(char line, char length)
{
    switch(line)
    {
        case 'b':  for(i=0;i<length;i++)
                   Write('-');
                   break;
        default :  for(i=0;i<length;i++)
                   Write('_');
                   break;
    }
   Write('\r');
}

void Name_copy(unsigned char *buf_1, unsigned char *buf_2, unsigned char e)
{
strncpy(buf_1, buf_2, e);
buf_1 = buf_1 + e;
*buf_1 = '\0';
}

unsigned char Check_extension(unsigned char *xtn, unsigned char str_1)
{
    unsigned char s_1[4]= "bin", s_2[4]="txt", j;
    if(!(strncmp(xtn, s_1, 3)) || !(strncmp(xtn, s_2, 3)))
    {
       for(j=0;j<3;j++)
                xtn++;
       *xtn = '\0';
        return(1);
    }
    else
      Write_str("\n\rExtension Failed");
      return(0);
}

void Format_string(unsigned char *buf_1, unsigned char *buf_2, unsigned char c)
    {
       *buf_1 = '/';
        buf_1++;                                       //       folde/bindu.bin
     for(i=0;*buf_2!='\0';i++)
        {
         if(*buf_2=='.')
         {
            if((c == 'r') || (c == 'd') || (c=='n'))
            {
            *buf_1='\0';
            break;
            }
         }
        *buf_1 = *buf_2;
        buf_1++;
        buf_2++;
        }
        *buf_1 = '\0';
     }

unsigned char Switch(unsigned char c)
{
    unsigned char exit[5]="exit";
    i=0;
    if(!(strcmp(string, exit)))
    {
        Write_str(string);
        return(2);
    }
    else if(c=='w')
    {
    while((string[i] != '.')  && (string[i] != '\0'))
    i++;                                                   /* increament */
    if(string[i] == '.')
    {
        i++;
        if(Check_extension(string+i, string))
        {
         Format_string(m, string, 'w');
         return (1);
        }
        else
        {
         Write_str("\n\rFile extension error!");
         return(0);
        }
    }
    else
    {
      Write_str("\n\rFile extension error!");
      return(0);
    }
    }
else
{
 Format_string(m, string, 'r');
 return (1);
}
}

/*__________________________________________   Write  ___________________________________________*/

void File_write(void)
{
     flag_1 = 0;
     do
     {
     Write_str("\n\rEnter the file name/ path?\n\r5 characters with file extension .txt or .bin\n\r");
     Clr_str(string);
     Read_str(string);
     if(Switch('w')==2)
     {
     flag_1 = 0;
     break;
     }
     else if(Switch('w')==1)
     {
     flag_1 = 1;
     break;
     }
     }while(flag_1==0);
                        /*_________________________   Check whether file exists or not    _________________________*/

 if(flag_1)
  {
     Switch('r');
     file = fl_fopen(m,"r");
 if( file)
    {
    fl_fclose(file);
    Write_str("\n\rFile already exists..!\n\rDo you want to replace? y/n");
    do
    {
       c = ReadUART();
       if(c== 'y')
        {                                                /*_________________DELETE EXISTING FILE  ______________________*/
        do{
        if (!(fl_remove(m) < 0))
            {
             Write_str("\n\rFile replaced..!\n\r");
            }
        file = fl_fopen(m, "r");
        if( file)
        {
        fl_fclose(file);
        }
        }while(file);
        flag_1 = 1;
       }
    else if(c=='n')
    {
    flag_1 = 0;
    break;
    }
    else
       Write_str("\n\rPlease enter y/n?");
  }while((c!= 'n') && (c!='y'));
 }
    Switch('w');
    file = fl_fopen(m,"w");
    flag_1 = 0;
    Write_str("\n\rEnter the data..(ctrl+s to save)\n\r");
/*___________________________________    File writing starts    ____________________________________________*/
  if(file)
    {
// while(fl_feof(file) != EOF )
    do{
    data = ReadUART();
    Write(data);
//    if(data == 0x08)
//        {
//           Write('s');                                                      /* long fl_ftell(void *f)                           */
//           fl_fseek(file, -1, (fl_ftell(file)));                 /* int fl_fseek( void *f, long offset, int origin ) */
//           fl_fwrite(' ', 1, 1, file);
//           fl_fseek(file, -1, (fl_ftell(file)));
//        }
    if(data==0x13)
    {
    Write_str("\n\rSave data? y/n?");
    data = ReadUART();
    if(data=='y')
        break;
    else
        continue;
    }
    fl_fwrite(&data, 1, 1, file);
    }while(1);
    Write_str("\n\r\n\rFile write completed..!");
    }
  else
    Write_str("\n\rFile write failed/ Invalid Directory");
  fl_fclose(file);
  }
}

/*________________________________________   File Append   ________________________________________*/

void File_append(void)
 {
 Write_str("\n\rEnter the file Name? 5 characters\n\r");
 Clr_str(string);
 Read_str(string);
 Switch('w');
 file = fl_fopen(s,"a");
 fptr = file;
 if(file)
    {
    Write_str("\n\rEnter the data to be appended to the file..\n\r");
  do{
    data = ReadUART();
    if(data == '#')
    {
    Write_str("\n\rEnter the line No. to Delete\n\r");
    z = ReadUART();
    t=0;
      do{
        fl_fread(&data, 1, 1, file);
        if(data=='\r')
        {
        Write('S');
        t = t+1;
  //    x = fl_ftell(file);
        }
        }while(t!= z);

      do{
        fl_fread(&data, 1, 1, file);
        if(data=='\r')
        break;
        else
        {
        fl_fwrite(' ', 1, 1, file);
        }
        }while(1);
        break;
    }
    else if(data == 0x7F)
        {
           Write('s');                                           /* long fl_ftell(void *f)                           */
           fl_fseek(file, -1, (fl_ftell(file)));                 /* int fl_fseek( void *f, long offset, int origin ) */
           fl_fwrite(' ', 1, 1, file);
           fl_fseek(file, -1, (fl_ftell(file)));
        }
    else if(data==0x13)
    {
    Write_str("\n\rSave the data? y/n?");
    data = ReadUART();
    if(data=='y')
    break;
    else
    continue;
    }
    fl_fwrite(&data, 1, 1, file);
    }while(1);
    Write_str("\n\rFile write completed..!");
    }
    else
     Write_str("\n\rFile open failed");
     fl_fclose(file);
 }
/* ___________________________________  File reading with Line No. Delete capability   ____________________*/


void File_read_(void)
    {
     Write_str("\n\rEnter the file Name? 5 characters\n\r");
     Read_str(string);
  Switch('r');
  file = fl_fopen(m,"r");
  fptr = file;
 if(file)
    {
    Write_str("\n\rFile open success..!\n\r");
    Draw_Line('s', 80);
    Write_str("File name\t:\t");
    Write_str(string);
    Write('\r');
    Draw_Line('s',80);
      do{
         data = fl_fgetc(file);
         Write(data);
        }while(fl_feof(file) != EOF );
        Write('\r');
        Draw_Line('s',80);
    for(i=0;i<20;i++)
       {
       fl_fwrite((void*)str_0,1, sizeof(str_0), file );
  //     fl_fwrite(&w, 1, 1, file);
    //   Write(w);
       }
//    fl_fseek(fptr, 0, SEEK_SET);
//       for(i=0;i<13;i++)
//       {
//       fl_fwrite((void*)str_0,1, sizeof(str_0), file );
//  //     fl_fwrite(&w, 1, 1, file);
//    //   Write(w);
//       }
//       fl_fseek(fptr, 0, SEEK_SET);
//       for(i=0;i<20;i++)
//       {
//       fl_fread(&data, 1, 1, file);
//       Write(data);
//       }



   data = ReadUART();
   d = 'y';
   if(data == '#')
    {
    Write_str("\n\rEnter the line No. to Delete\n\r");
    z = ReadUART();
    z = z-'0';
    z--;
    t=0;
    i=0;
    w=' ';
    fl_fseek(file, 0, SEEK_SET);
     do{
        fl_fread(&data, 1, 1, file);
        i++;
        Write('i');
        if(data=='\r')
        {
        Write('S');
        t = t+1;
        }
        }while((t!=z) && (fl_feof(file) != EOF));
        t=0;
        j=i;
      do{
         fl_fread(&data, 1, 1, file);
         j++;                                                                 /* int fl_fseek( void *f, long offset, int origin ) */
        }while( (data != '\r')  &&  (fl_feof(file) != EOF) );
        fl_fseek(file, 1, SEEK_SET);
        for(i=0;i<13;i++)
        {
        fl_fwrite(&w, 1, 1, file);
        }
        while((fl_feof(file) != EOF))
        {
        fl_fseek(file, j++, SEEK_SET);
        fl_fread(&data, 1, 1, file);
        Write(data);
        fl_fseek(file, i++, SEEK_SET);
        fl_fwrite(&w, 1, 1, file);
        }

//      do{
//        fl_fread(&data, 1, 1, file);
//        if(data=='\r')
//        {
//        Write('S');
//        t = t+1;
//        break;
//  //    x = fl_ftell(file);
//        }
//        }while(t!= z);
//
//      do{
//        fl_fread(&data, 1, 1, file);
//        if(data=='\r')
//        break;
//        else
//        {
//           fl_fseek(file, -1, (fl_ftell(file)));                 /* int fl_fseek( void *f, long offset, int origin ) */
//           fl_fwrite(' ', 1, 1, file);
//        }
//        }while(1);
    }
    }
 else
      Write_str("\n\rfile not found..!");
      fl_fclose(file);
      Write(0x0B);                                               /* Vertical tab                    */
      Write_str(str_1);
      delay_ms(200);
      Write_str("\n\r");
      Clr_str(str_1);
  }

/*_______________________________________      File Read         ___________________________________________*/

void File_read(void)
    {
     Write_str("\n\rEnter the file Name? 5 characters\n\r");
     Clr_str(string);
     Read_str(string);
  Switch('r');
  file = fl_fopen(m,"r");
  fptr = file;
 if(file)
    {
    Write_str("\n\rFile open success..!\n\r");
    Draw_Line('s', 80);
    Write_str("File name\t:\t");
    Write_str(string);
    Write('\r');
    Draw_Line('s',80);
      do{
         data = fl_fgetc(file);
         Write(data);
        }while(fl_feof(file) != EOF );
        Write('\r');
        Draw_Line('s',80);

    }
 else
      Write_str("\n\rfile not found..!");
      fl_fclose(file);
  }

/*________________________________________Delete file ______________________________________________*/

void File_delete(void)
{
    {
    Write_str("\n\rEnter the file Name/path? 5 characters\n\r");
    Clr_str(string);
    Clr_str(m);
    Read_str(string);
    Switch('r');
    if (fl_remove(m) < 0)
        {
        Write_str("\n\rERROR: Delete file failed");
        flag = 1;
        }
        else
        {
        Write_str("\n\rDelete file was successful..!\n");
        }
    }
}
void Create_folder(void)
{
    Write_str("\n\rEnter a name/ path\n\r");
    Clr_str(string);
    Clr_str(m);
    Read_str(string);
    Switch('r');
    Write_str("\n\r");
    Write_str(m);
    if(fl_createdirectory(m))
    Write_str("\n\rNew folder created..!");
    else
        Write_str("\n\rFolder already exists/ error..!");
}

void Open_dir(void)
{
    Write_str("\n\rEnter the name of the directory\n\r");
    Clr_str(string);
    Read_str(string);
    Switch('r');
    if (fl_opendir(m, &dptr))
    {
        printf("\n\r%s",m);
        fl_listdirectory(m);
        fl_closedir(&dptr);
    }
}

File_format(uint32 volume, char *name)                   //int                 fl_format(uint32 volume_sectors, const char *name);
{
if(fl_format(volume,name))
    Write_str("\n\rFormat complete..!");
else
   Write_str("\n\rFormat failed..!");
}

void Format_drive(void)
{
  Write_str("\n\rAll data will be lost..!\n\rAre you sure? y/n\n\r");
  switch(ReadUART())
  {
      case 'y' : Write_str("\n\rEnter the name of the Disk\n\r");
                 Clr_str(string);
                 Read_str(string);
                 File_format(1048576, "DISK_");
                 break;
      case 'n' : break;
  }
}
void putch(unsigned char byte)
{
Write(byte);
}

void main()
{
   ADCON1 = 0x0F;
   CMCON |=0X07;
   TRISA5 = 0x00;
//  TRISE = 0x00;
   LATA5 = 0x00;                    /* Keep bit RA5 (SS) to logic low because we have defined pin RB4 instead of hardware SS (slave select) pin */
//  LATE = 0x00;                                                        //  OpenSPI_(SPI_FOSC_64, MODE_01, SMPMID);

    ConfigUSART(config_1, config_2);
    spi_init();
    __delay_ms(1);                                                      // Initialise media
   if(!mmc_init())
    {
    Write_str("\n\rcard initialized..!\r\n");
    }
   else
    Write_str("\ncard initialization failed...!");                                                                            // Initialise File IO Library
   fl_init();                                                          // Attach media access functions to library
   if (fl_attach_media(media_read, media_write) != FAT_INIT_OK)
    {
     Write_str("ERROR: Media attach failed\n");
     return;
    }
   fl_listdirectory("/");                                          // List root directory
do{
 do{
 Write_str("\n\rPlease select an operation?\n\rFile : \r\tWrite    - w\n\r\tRead     - r\n\r\tDelete   - d\n\r\tAppend   - a\n\r\tNew Dir  - n\n\r\tFormat   - f\n\r\tOpen Dir - x\n\r");
 c = ReadUART();
 /*________________________________________  If write selected   ___________________________________________*/

 if(c=='w')
 {
  File_write();
  break;
 }
 else if(c=='a')
 {
  File_append();
  break;
 }
 else if(c=='r')
 {
  File_read();
  break;
 }
 else if(c=='d')
 {
  File_delete();
  break;
 }
 else if(c == 'n')
 {
 Create_folder();
 break;
 }
 else if (c=='x')
 {
 Open_dir();
 break;
 }
 else if(c=='f')
 {
  Format_drive();
  break;
 }
 else
   Write_str("\n\rInvalid Entry..!");

}while((c != 'w') && (c != 'r') && (c != 'd') && (c != 'n') && (c != 'x'));

 fl_listdirectory("/");
}while(1);
 fl_shutdown();
}
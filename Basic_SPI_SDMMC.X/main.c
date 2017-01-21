/*
 * File:   main.c
 * Author: Etiq Technologies
 *
 * Created on January 20, 2017, 4:44 PM
 */


#include <xc.h>
#include <spi.h>
#include <usart.h>
#include <pic18f4550.h>
#include "my_openuart.h"
#include "my_sw_uart.h"
#include "config.h"
#include "delay.h"

#define FOSC 20000000
#define Baud 9600
#define spbrg ((FOSC/Baud)/64)-1                                 /*
                                      ((FOSC/Desired Baud Rate)/64) ? 1
                                       = ((16000000/9600)/64) ? 1        */
                                       /*void Open1USART ( unsigned char config,  unsigned int spbrg);*/


void File_IO(void)
{
    unsigned char c;
 do{
 putsUART_("\n\rPlease select a file operation?\n\rWrite    - w\n\rRead     - r\n\rMulti_Write   - a\n\rMulti_Read   - d\n\r");
 c = ReadUART_();
 switch(c)
    {
         case 'w' :
                    write_block();
                    break;
         case 'r':
                    read_block();
                    break;
         case 'a':
                    multi_write();
                    break;
         case 'd':
                    multi_read();
                    break;
         default  :
                    putsUART_("\n\rInvalid Entry..!");
                    break;
    }
}while((c != 'w') && (c != 'r') && (c != 'd') && (c != 'a'));
}



void main() 
{
 Soft_Hard_Init(); //SPI Initialization
 OpenUART_(); //Software UART
 putsUART_("Insert SD Card");
 init();
 while(1)
 {
     File_IO();
 
 }

    return;
}

/*
 * File name            : uart.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_10.1 Keypad
 *                      : Created on November 28, 2013, 12:50 PM
 *                      : uart functions source file
 */
#if defined(__XC)
    #include <plib\usart.h>
#include <stdio.h>
#elif defined(__18CXX)
    #include <usart.h>
#endif

/*_____________________________________________configure USART____________________________________________________________*/

void ConfigUSART(unsigned char config_1, unsigned char config_2)
{
OpenUSART(config_1, config_2);
}
unsigned char ReadUART(void)
{
     unsigned char data;
     while(BusyUSART());
     while(!(DataRdyUSART()));                                       /* Reading a data byte                                        */
     data = ReadUSART();
     if(data == '\r')
        {
         WriteUSART('\n');
         while(BusyUSART());
         WriteUSART('\r');
         while(BusyUSART());
        }
     else if(data == 0x7F)
        {
         WriteUSART(0x7F);
         while(BusyUSART());
         WriteUSART(' ');
         while(BusyUSART());
        }
     else
     {
     WriteUSART(data);
     while(BusyUSART());
     }
     return(data);
}

void Write_str(unsigned char* str)
{
putsUSART((char *)str);                                         /*Passing the address of the String to the USART write function */
    while(BusyUSART());                                         /*Wait until USART goes to idle state                           */
}

void Read_str(unsigned char *buf)      /* Reads a string data from UART of having specific length*/
  {
  unsigned char data;
    WriteUSART('\n');
    while(BusyUSART());
    WriteUSART('\r');
    while(BusyUSART());
 while(1)
    {
    while(!DataRdyUSART());                                          /* Wait for data to be received                           */
    data = getcUSART();                                              /* Get a character from the USART                         */
    if(data!=0x0D)
    *buf = data;
    else
    break;                                             /* save data in a string                                  */
    WriteUSART(data);
    while(BusyUSART());
    buf++;                                                        /* Increment the string pointer                           */
    }
  }

void Write(char data)
{
    if(data== '\r')
    {
         WriteUSART('\n');
         while(BusyUSART());
         WriteUSART('\r');
         while(BusyUSART());
    }

    else
    {
      WriteUSART(data);                                               /* Write a byte through USART module                    */
      while(BusyUSART());
    }
}

//int printf(const char* ctrl1, char* var1)
//{
//unsigned char str[] = "\0";
//     printf( str, ctrl1, var1);
//     Write_str(str);
//     return(0);
//}
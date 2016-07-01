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
while(!(DataRdyUSART()));                                       /* Reading a data byte                                        */
     return(ReadUSART());
}

void Write_str(unsigned char* str)
{
putsUSART((char *)str);                                         /*Passing the address of the String to the USART write function */
    while(BusyUSART());                                         /*Wait until USART goes to idle state                           */

}

void Write(char data)
{
    if(data!='\r')
    {
     WriteUSART(data);                                           /* Write a byte through USART module                    */
    while(BusyUSART());
    }
    else
    {
     WriteUSART('\n');                                           /* Write a byte through USART module                    */
    while(BusyUSART());
     WriteUSART('\r');                                              /* Write a byte through USART module                    */
    while(BusyUSART());
    }                                                               /* Wait until the write complete                        */
}
void Read_string(unsigned char *buffer, unsigned char len)          /* Reads a string data from UART of having specific length*/
  {
  char i;
  unsigned char data;
      Write(0x0D);
      Write('\n');
  for(i=0;i<len;i++)
    {
    while(!DataRdyUSART());                                          /* Wait for data to be received                           */
    data = getcUSART();                                              /* Get a character from the USART                         */
    *buffer = data;                                                  /* save data in a string                                  */
    WriteUSART(data);
    while(BusyUSART());
    buffer++;                                                        /* Increment the string pointer                           */
    }
  }
void Read_str(unsigned char *buffer)                                /* Reads a string data from UART of having specific length*/
  {
  char i;
  unsigned char data;
  for(i=0;data!=0x0D;i++)
    {
    while(!DataRdyUSART());                                           /* Wait for data to be received                           */
    data = ReadUSART();
    if(data!=0x0D)                                                    /* Get a character from the USART                         */
    *buffer = data;                                                   /* save data in a string                                  */
    WriteUSART(data);
    while(BusyUSART());
    buffer++;                                                         /* Increment the string pointer                           */
    }
    WriteUSART(0x0D);
    while(BusyUSART());
  }
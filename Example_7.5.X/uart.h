/*
 * File name            : uart.h
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_10.1 Keypad
 *                      : Created on November 28, 2013, 12:50 PM
 *                      : Uart functions header file
 */

#ifndef UART_H
#define	UART_H

/*____________________UART configuration function header_________________________________*/

void ConfigUSART(unsigned char config_1, unsigned char config_2);

/*
 * Include          :       uart.h
 * Description      :       Configures UART module 
 * Arguments        :       Byte, Byte
 * Returns          :       None
 */

/*______________________UART Read byte function header_________________________________*/

unsigned char ReadUART(void);

/*
 * Include          :       uart.h
 * Description      :       Reading a single byte through UART 
 * Arguments        :       None
 * Returns          :       Byte
 */

/*____________________UART Write string function header_________________________________*/

void Write_str(unsigned char* str);

/*
 * Include          :       uart.h
 * Description      :       Writing a string through UART module 
 * Arguments        :       Address of a string
 * Returns          :       None
 */

/*____________________UART Write string function header_________________________________*/

void Read_str(unsigned char* str );

/*
 * Include          :       uart.h
 * Description      :       Writing a string through UART module
 * Arguments        :       Address of a string
 * Returns          :       None
 */

/*______________________UART Write byte function header_________________________________*/

void Write(char data);

/*
 * Include          :       uart.h
 * Description      :       Writing a single byte through UART 
 * Arguments        :       Byte
 * Returns          :       None
 */

/*______________________UART Write byte function header_________________________________*/

void Read_string(unsigned char *buffer, unsigned char len);

/*
 * Include          :       uart.h
 * Description      :       Writing a single byte through UART
 * Arguments        :       Byte
 * Returns          :       None
 */


#endif	/* UART_H */


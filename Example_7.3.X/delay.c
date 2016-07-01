/*
 * File name            : delay.c
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_7.5 External Character LCD
 *                      : Created on October 30, 2013, 1:36 PM
 *                      : Delay functions declaration source file
 */

#if defined(__18CXX)
#include <delays.h>
#elif defined(__XC)
#include <plib\delays.h>
#endif

void delay_ms(unsigned char t)
{
    unsigned char i;
    for (i=0;i<=t;i++)
       Delay1KTCYx(5);                                          /* Delay of 1ms                                                     */
                                                                /* Cycles = (TimeDelay * Fosc) / 4                                  */
                                                                /* Cycles = (1ms * 20MHz) / 4                                       */
                                                                /* Cycles = 5,000                                                   */
  return;
}
void delay_us(unsigned char t)
{
    unsigned char i;                                            /* Delay of 1us                                                     */
    for (i=0;i<=t;i++)                                          /* Delay multiples of 10 Tcy                                        */
        Delay1KTCYx(1);                                          /* Cycles = (TimeDelay * Fosc) / 4                                  */
                                                                /* Cycles = (1ms * 20MHz) / 4                                       */
                                                                /* Cycles = 5                                                       */
    return;
}
void Delay_s(unsigned char t)                                   /* Delay of t seconds                                               */
    {
    unsigned char i,j;                                          /* 10 * 100msec = 1000msec (1second) for 10 cycles of inner loop    */
    for(i=0;i<t;i++)                                            /* Delay by t cycles = t seconds                                    */
        for(j=0;j<10;j++)
            delay_ms(100);                                      /* 100msec delay                                                    */
    }


void DelayFor18TCY( void )                                                          /* Delay of 10ms                         */
{                                                                                   /* Cycles = (TimeDelay * Fosc) / 4       */
     unsigned char i;                                                               /* Cycles = (5ms * 20MHz) / 4            */
     for(i=0;i<10;i++)                                                              /* Cycles = 50,000                       */
        {
        Delay10TCYx(50);
        }
}
void DelayPORXLCD (void)
{
     Delay1KTCYx(75);                                                               /* Delay of 15ms                          */
                                                                                    /* Cycles = (TimeDelay * Fosc) / 4        */
                                                                                    /* Cycles = (15ms * 20MHz) / 4            */                                                                                   /* Cycles = 75,000                        */
return;
}

void DelayXLCD (void)                                                               /* Delay of 5ms                           */
{                                                                                   /* Cycles = (TimeDelay * Fosc) / 4        */
    unsigned char i;                                                                /* Cycles = (5ms * 20MHz) / 4             */
    for(i=0;i<20;i++)                                                               /* Cycles = 25,000                        */
    Delay1KTCYx(25);
return;
}

void Delay_s_(void)
{
Delay10KTCYx(1);                                   /* Cycles = (TimeDelay * Fosc) / 4                               */
                                                   /* (10ms * 20MHz) / 4 = 50000                                    */
}                                                  /* Passing argument 5 to the function will result in 10ms delay  */

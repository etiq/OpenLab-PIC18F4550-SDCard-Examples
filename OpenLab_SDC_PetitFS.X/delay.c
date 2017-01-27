
#if defined(__18CXX)
//#include <delays.h>
#elif defined(__XC)
#include <plib\delays.h>
#endif

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
                                                                                    /* Cycles = (15ms * 20MHz) / 4            */
                                                                                    /* Cycles = 75,000                        */
return;
}

void DelayXLCD (void)                                                               /* Delay of 5ms                           */
{                                                                                   /* Cycles = (TimeDelay * Fosc) / 4        */
    unsigned char i;                                                                /* Cycles = (5ms * 20MHz) / 4             */
    for(i=0;i<20;i++)                                                               /* Cycles = 25,000                        */
    Delay1KTCYx(25);
return;
}

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

void Delay_s(unsigned char t)                                   /* Delay of t seconds                                               */
    {
    unsigned char i,j;                                          /* 10 * 100msec = 1000msec (1second) for 10 cycles of inner loop    */
    for(i=0;i<t;i++)                                            /* Delay by t cycles = t seconds                                    */
        for(j=0;j<10;j++)
            delay_ms(100);                                      /* 100msec delay                                                    */
    }


void Delay_s_(void)
{
Delay10KTCYx(2);                                   /* Cycles = (TimeDelay * Fosc) / 4                               */
                                                   /* (10ms * 20MHz) / 4 = 50000                                    */
}                                                  /* Passing argument 5 to the function will result in 10ms delay  */
                                                   /* Passing argument 2 to the function will result in 4ms delay   */
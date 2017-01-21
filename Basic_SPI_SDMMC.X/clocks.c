/*
 * File:   clocks.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 7, 2017, 10:15 AM
 */


#include <xc.h>
#include <spi.h>
#include "delay.h"

void dummy_clocks(int n)
{
    int i = 0;
    delay_ms(1);
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

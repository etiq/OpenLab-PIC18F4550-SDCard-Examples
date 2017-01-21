/*
 * File:   initialization.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 20, 2017, 4:44 PM
 */


#include <xc.h>
#include "my_openuart.h"
#include "my_sw_uart.h"
#include "delay.h"
#include "transceiver.h"
#include "clocks.h"

void Soft_Hard_Init()
{
 unsigned char sync_mode=0;
 unsigned char bus_mode=0;
 unsigned char smp_phase=0;
 int i = 0;

 CloseSPI();
 
 ADCON1 = 0X0F;   
 CMCON |= 7;
 
 TRISA5 = 0;
 LATA5 = 0;
 
 TRISB4 = 0; //CS
 TRISC7 = 0; //SDO
 TRISB1 = 0; //SCK
 TRISB0 = 1; //SDI
 
 sync_mode = SPI_FOSC_64;
 bus_mode = MODE_00;
 smp_phase = SMPMID;
 OpenSPI(sync_mode, bus_mode, smp_phase);
 SSPSTAT = 0XC0;
 SSPCON1 = 0X22;

}

/*SOFTWARE RESET PROCESS*/
void reset()
{
    int i = 0, count = 0;
    unsigned char buff;
    do{
    dummy_clocks(8);        
    Command(0X40, 0X00000000, 0X95); //CMD0
    proceed(1);
    do{   
        buff = response();
        count++;
      }while((buff!=0X01) && (count<10));
      count = 0;
    }while(buff!=0X01); //Wait Till SD Card is Inserted
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      putsUART_("\n\rSD Card Inserted\n\r");
      Delay_s(2);
    return;
}

void init()
{
    int i = 0, count = 0, count1 = 0, count2 = 0;
    unsigned char buff;
    reset(); //RESET THE SD CARD
    delay_ms(500);

    //SEND CMD1
    do{
    dummy_clocks(8);    
    Command(0X41, 0X00000000, 0X00); //CMD1
    proceed();
    do{
        buff = response();
        count++;
    }while((buff!=0X00) && (count<10));
    count = 0;
    }while(buff!=0x00);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/

    Delay_s(1);
    proceed();
    if (buff == 0x00)
    {                    
        //SEND CMD55 + ACMD41     
        delay_ms(1);
        count1 = 0;        
          do{
            count2 = 0;
            dummy_clocks(8);
            Command(0X77, 0X00000000, 0X95); //CMD55
            buff = 0XFF;
            /*CHECK THE BUFFER FOR A 0X00 RESPONSE BIT*/
            do{
            buff = response();
            count2++;
            }while((buff!=0X01)&&(count2<10));

            delay_ms(1);
            count2 = 0;
            dummy_clocks(8);

            Command(0X69,0X40000000,0X95); //CMD41
            buff = 0XFF;
            /*CHECK THE BUFFER FOR A 0X00 RESPONSE BIT*/
        proceed();
            do{
            buff = response();
            count2++;
            }while((buff!=0X00)&&(count2<10));
         }while(buff != 0X00);
           //Send CMD58
      //Reset counter 1
      count1 = 0;
      //Delay before sending command
      delay_ms(1);
    putsUART_("\n\r");
    putsUART_("SUCCESS\n\r");
    Delay_s(2);     
    }

    else if(buff == 0x05)
    {
        putsUART_("Error!!!\n\r");
        Delay_s(3);
    }
          Delay_s(1);
    
        /*SETTING BLOCK LENGTH TO 512 Bytes*/
        dummy_clocks(8);    
        Command(0X50,0X00000200,0XFF);
        proceed();
        do{   
            buff = response();
          }while(buff!=0x00);
        /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
          putsUART_("512 Bytes Set\n\r");
          Delay_s(2);
    return;    
    }

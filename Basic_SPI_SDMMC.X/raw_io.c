/*
 * File:   raw_io.c
 * Author: Etiq Lab Desktop
 *
 * Created on January 20, 2017, 4:44 PM
 */


#include <xc.h>
#include "my_sw_uart.h"
#include "my_openuart.h"
#include "delay.h"
#include "transceiver.h"
#include "clocks.h"

static unsigned char str[512],ctr[512];

void write_block()  
{
    unsigned char buff; 
    int i=0;

    dummy_clocks(8);    
    Command(0X58, 0X00000A00, 0X00); //CMD24
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);

      putsUART_("CMD24 Accepted");

      Delay_s(1);
      dummy_clocks(8);    
      WriteSPI_(0XFE); //START TOKEN
      
      for(i=0;i<(512*2);i++) //DATA BLOCK
      {
          WriteSPI_(0X41);
          i++;
      }
      
      WriteSPI_(0XFF); //CRC
      WriteSPI_(0XFF); //CRC
      
    dummy_clocks(1);
      
 
      Delay_s(1);
      dummy_clocks(8);    
      Command(0X4D,0X00000000,0XFF);
    proceed();
      do{   
        buff = response();
        }while(buff!=0x00);
      putsUART_("BLOCK WRITE OVER");
return;      
}

void multi_write()
{
    unsigned char data = 0X41,buff; 
    int i=0,j;

    dummy_clocks(8);    

    Command(0X59, 0X00000A00, 0X00); //CMD25
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      putsUART_("CMD25 Accepted\n\r");
      Delay_s(2);

      dummy_clocks(8);
      while(i!=4)
      {
      WriteSPI_(0XFC); //START TOKEN
      i++;      
      for(j=0;j<1024;j++) //DATA BLOCK
      {
          WriteSPI_(data);
          j++;
      }
      data++;
      WriteSPI_(0XFF); // CRC 2 BYTES
      WriteSPI_(0XFF);
    dummy_clocks(1);
      Delay_s(1);
      dummy_clocks(8);
      }


      WriteSPI_(0XFD); //STOP TOKEN
    dummy_clocks(1);
      Delay_s(1);
      dummy_clocks(8);    
      Command(0X4D,0X00000000,0X00); //CMD13
    proceed();
      do{   
        buff = response();
        }while(buff!=0x00);
      putsUART_("MULTI WRITE OVER\n\r");
      Delay_s(2);
return;      
}

void multi_read()
{
    unsigned char ptr=0X00,buff;
    unsigned long int start_add;
    int length,count;
    /*Read Sector*/
    Delay_s(1);
    dummy_clocks(8);    

    Command(0X52,0X00000A00,0X00); //CMD18
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);

    dummy_clocks(1);
      do{
        buff = response();
      }while(buff!=0xFE);
      
      count = 2;
      length = 0;
            
      while(count){
      while ( length < 512 )               
        {
            ctr[length] = response();
            length++;                   
        }
      count--;
      length = 0;
      while ( length < 512 )               
        {
            str[length] = response(); /* A different array is used to store the read data due to memory constraints
                                       * Please use same array, if memory is not an issue*/
            length++;                   
        }
      count--;
      }
    length = 0;
    
    
    Delay_s(1);
    dummy_clocks(8);    
    Command(0X4C,0X00000600,0X00); //CMD12
    proceed();
    do{   
        buff = response();
      }while(buff!=0xFF);

    while(length < 512)
    {
          WriteUART_(ctr[length]);
          length++;
    }
    
    Delay_s(1);
    putsUART_("\r\n");
    length = 0;
    
    while(length < 512)
    {
          WriteUART_(str[length]);
          length++;
    }

    Delay_s(1);
      putsUART_("\r\n\r\nMulti Read Over\n\r");
}


void read_block()
{
    unsigned char buff, readdata;
    int length,count,i=0;
    Delay_s(1);
    dummy_clocks(8);    
    count = 6;
    Command(0X51,0X00000000,0XFF);

    do{   
        buff = response();
      }while(buff!=0x00);
      do{   
        buff = response();
      }while(buff!=0xFE);

          length = 0;
          LATB4 = 0; // CS
          
            while(length<512)
            {
                str[length]=response();  //read buffer (R1) should be 0x01 = idle mode   
                length++;
            }
          length = 0;

          WriteUART_(0XFF);
          WriteUART_(0XFF);
          
            Delay_s(1);
            dummy_clocks(8);    
            Command(0X4C,0X00000000,0X00); //COMMAND12 MANDATORY
            proceed();
            do{   
                buff = response();
              }while(buff!=0xFF);

          putsUART_("BLOCK READ OVER\n\r");
      Delay_s(2);
      length = 0;
      i = 0;
      
      while(length<512)
      {
          WriteUART_(str[length]);
          length++;
      }
return;
}

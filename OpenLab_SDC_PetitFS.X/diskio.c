/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "delay.h"
#include "sw_uart.h"

extern  signed char WriteSPI_(unsigned char);
extern  BYTE ReadSPI_();
extern  void dummy_clocks(int);
extern  BYTE response();
extern  void proceed();
extern  void check();
extern  void Command(char,unsigned long int, char);

int flag;

void readover(int a)    /*Set Global Variable, Flag when reading SD Card content*/
{
    flag = a;
}

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

    void reset()
    {
    int i = 0, count = 0;
    unsigned char buff;
    /*SOFTWARE RESET COMMAND*/
    do{
    dummy_clocks(8);    
    Command(0X40, 0X00000000, 0X95);    //CMD0
    proceed();
    do{   
        buff = response();
        count++;
      }while((buff!=0X01) && (count<10) );
      count = 0;
    }while(buff!=0X01);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      putsUART("\n\rSD Card Inserted\n\r");
      Delay_s(2);
    return; //CHECK FOR A STA_NODISK return
}

DSTATUS disk_initialize (void)
{
	DSTATUS stat;
    int i = 0, count1 = 0, count2 = 0;
    unsigned char buff;
    reset(); //RESET THE SD CARD
    delay_ms(500);
    dummy_clocks(8);    
    Command(0X41, 0X00000000, 0XFF);    //CMD1
    proceed();
    do{
        buff = response();
      }while(buff!=0x01);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      Delay_s(1);
      proceed();
if (buff == 0x01)
{                    
    //SEND CMD55 + ACMD41     
    delay_ms(1);
    count1 = 0;        
      do{
        count2 = 0;
        dummy_clocks(8);
        Command(0X77, 0X00000000, 0X95);    //CMD55
        buff = 0XFF;
        /*CHECK THE BUFFER FOR A 0X00 RESPONSE BIT*/
        do{
        buff = response();
        count2++;
        }while((buff!=0X01)&&(count2<10));
        
        delay_ms(1);
        count2 = 0;
        dummy_clocks(8);

        Command(0X69,0X40000000,0X95);    //CMD41
        buff = 0XFF;
        /*CHECK THE BUFFER FOR A 0X00 RESPONSE BIT*/
        proceed();
        do{
        buff = response();
        count2++;
        }while((buff!=0X00)&&(count2<10));
     }while(buff != 0X00);

      count1 = 0;
  //Delay before sending command
      delay_ms(1);
      stat = 0X00;
      putsUART("\n\r");
      putsUART("Card Accepted\n\r");
      Delay_s(2);     
      }

      else if(buff == 0x05)
      {
        stat = STA_NOINIT;
        putsUART("Error!!!\n\r");
        Delay_s(3);
      }
      Delay_s(1);
/*SETTING BLOCK LENGTH TO 512 Bytes*/
    dummy_clocks(8);    
    Command(0X50,0X00000200,0XFF);    //CMD16
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/
      putsUART("\n\rSetting Block Size to 512 Bytes\n\r");
      Delay_s(2);
      putsUART("\n\rCOMPLETING INITIALIZATION");
	return stat;
}


/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* rd,		/* Pointer to the destination object */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Offset in the sector */
	UINT count		/* Byte count (bit15:destination) */
)
  {
	DRESULT res;
    unsigned char ptr=0X00,buff;
    unsigned long int start_add;
    static unsigned char arr[512];
    int length,i;
    /*Read Sector*/
    if(offset == 0){
    start_add = ((sector*512));
    
    Delay_s(1);
    dummy_clocks(8);    
    Command(0X52,start_add,0X00);    //CMD18
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
      Delay_s(1);
      proceed();
      do{
        buff = response();
      }while(buff!=0xFE);
      length = 0;
      while ( length < count )               
        {
            arr[length] = response();
            length++;                   
        }
      
    Delay_s(1);
    dummy_clocks(8);    
    Command(0X4C,0X00000000,0X00);    //CMD12
    proceed();
    do{   
        buff = response();
      }while(buff!=0xFF);
 
      length = 0;
      
      while(arr[length]!='\0')
      {
          //WriteUART(arr[length]);
          length++;
      }
      
      *rd = length;
	return RES_OK;
  }
    else
    {
    start_add = (sector*512);
    
    length = 0;
    while(length<512)           //CLEAR ARRAY
    {
        arr[length] = 0;                
        length++;
    }

    Delay_s(1);
    dummy_clocks(8);    
    //SPI_cmd(sd_cmd17);
    Command(0X51,start_add,0X00);
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
      do{   
        buff = response();
      }while(buff!=0xFE);

          length = 0;
            while ( length < 512 )               
            {
                while(offset--)             //RUN DOWN TILL THE OFFSET VALUE
                {
                arr[length] = response();
                length++;
                }
                while(count--)              //RUN DOWN TILL THE COUNT VALUE
                {
                *rd = response();
                arr[length] = *rd;
                rd++;
                length++;
                }
                while(length<512)           //FOR THE TRAILING BYTES
                {
                    arr[length] = response();                
                    length++;
                }
            }
            Delay_s(1);
//            dummy_clocks(8);    
            //SPI_cmd(sd_cmd12);
            Command(0X4C,0X00000000,0X00); //COMMAND12 MANDATORY
            proceed();
            do{   
                buff = response();
              }while(buff!=0xFF);
              
              length = 0;

              if(flag == 1){
              while(arr[length]!='\0')
              {
                WriteUART(arr[length]);
                length++;
              }
              }
              else
                putsUART("..");
              
      Delay_s(2);

return RES_OK;
}

}
/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
    const BYTE* wr,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res;
    
    unsigned char buff; 
    int i=0,j;
    
    Delay_s(1);
    
    dummy_clocks(8);    
    Command(0X58, sc*512, 0X00); // CMD24
    proceed();
    do{   
        buff = response();
      }while(buff!=0x00);
    /*SOFTWARE RESET RESPONSE BIT OBTAINED (0X01)*/

      Delay_s(2);

      dummy_clocks(8);

      WriteSPI_(0XFE); //START TOKEN
      
      for(j=0;j<512;j++) //DATA BLOCK
      {
          if(*wr!='\0')
          {
              WriteSPI_(*wr);
              wr++;
          }
          else
          WriteSPI_(0x00);
      }
      WriteSPI_(0XFF); // CRC 2 BYTES
      WriteSPI_(0XFF);

      proceed();

      Delay_s(1);
      dummy_clocks(8);    

      Command(0X4D,0X00000000,0X00);    //CMD13
      proceed();
      do{   
        buff = response();
        }while(buff!=0x00);
      
	return RES_OK;
}


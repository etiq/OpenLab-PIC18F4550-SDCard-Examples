/* 
 * File:   spi_1.h
 * Author: tbi
 *
 * Created on February 8, 2014, 4:46 PM
 */

#ifndef SPI_1_H
#define	SPI_1_H


#define TRIS_SDI TRISCbits.TRISC4       // DIRECTION define SDI input
#define TRIS_SCK TRISCbits.TRISC3      // DIRECTION define clock pin as output
#define TRIS_CS TRISBbits.TRISB4       // DIRECTION CS - RA5
#define TRIS_SDO TRISCbits.TRISC5      //DIRECTION SD0 as output        MOSI

#define SDI LATCbits.LATC4
#define SCK LATCbits.LATC3
#define CS LATBbits.LATB4
#define SDO LATCbits.LATC5


void ReadBUF(void);
void spi_read(void);
void spi_init(void);
void OpenSPI_( unsigned char sync_mode, unsigned char bus_mode, unsigned char smp_phase);
signed char WriteSPI_( unsigned char data_out );
unsigned char ReadSPI_( void );
unsigned char DataRdySPI_( void );


#endif	/* SPI_1_H */


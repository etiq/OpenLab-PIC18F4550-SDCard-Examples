#include <p18cxxx.h>

#define SWTXD         PORTDbits           // Transmit pin port and pin
#define SWTXDpin      RD4
#define TRIS_SWTXD    TRISDbits           // Transmit pin tris and pin
#define TRISbit_SWTXD TRISD4
#define SWRXD         PORTDbits           // Receive pin port and pin
#define SWRXDpin      RD5
#define TRIS_SWRXD    TRISDbits           // Receive pin tris and pin
#define TRISbit_SWRXD TRISD5

/********************************************************************
;*      Function Name:  OpenUART                                    *
;*      Return Value:   void                                        *
;*      Parameters:     void                                        *
;*      Description:    This routine configures the I/O pins for    *
;*                      software UART.                              *
;*******************************************************************/

void OpenUART_(void)
{ 
    TRISDbits.RD4 = 0; //CONFIGURE AS OUTPUT
    RD4           = 1; //SET HIGH

    TRISDbits.RD5 = 1; //CONFIGURE AS INPUT
    RD5           = 1; //SET HIGH
}
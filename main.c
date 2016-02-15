 //*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp432.h"
#include "driverlib.h"

#include "string.h"

#define BUFFER_MEMORY_START 0x000200000

char memoryOffset = 0;

void port_init()			//	port initialization function
{
	P1OUT &= ~BIT0;			//turn off RED LED
	P2OUT &= ~BIT1;			//turn off GREEN LED
	P1DIR |= BIT0;			// make P1.0 an output (RED LED)
	P1DIR &= ~BIT4;			// make P1.4 and input
	P1REN |= BIT4;			// enable pull resistor on P1.4
	P1OUT |= BIT4;			// make it a pull-up resistor
	P2DIR |= BIT1;			// make P2.1 an output (GREEN LED)

//	P1OUT &= ~BIT0;			//turn off RED LED
//	P2OUT &= ~BIT1;			//turn off GREEN LED

}
void delay_1sec()      	// 1 second delay for 1.5 MHz clock
{
	int  dcntr;			// delay counter variable

	for (dcntr=0;dcntr<57692;dcntr++);		//~1 second delay loop
	return;
}

void main(void)
{
	port_init();
	memoryOffset = 0;					//making sure my offset is set to 0
	WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;	// Watchdog timer set to expire every second
    PCM_setCoreVoltageLevel(PCM_VCORE1);
	MAP_FlashCtl_setWaitState(FLASH_BANK0,2);
	MAP_FlashCtl_setWaitState(FLASH_BANK1,2);
	while(1){
		WDTCTL = WDTPW | WDTCNTCL;		//clear watchdog each loop of the almighty while
	if (!(P1IN & BIT4)){				//check if button is pushed and initiate functions if true
		P1OUT |= BIT0;					//turn on RED LED
		delay_1sec();					//tie up the processor for roughly one second
		WDTCTL = (WDTPW-1);				//force a reset by the watchdog not getting the correct password when passed information or attempting changes
	} //outside of button push

	uint8_t buffer[4096];
	memset(buffer,0xA5,4096);
	WDTCTL = WDTPW | WDTCNTCL;
	MAP_FlashCtl_unprotectSector(FLASH_INFO_MEMORY_SPACE_BANK0,FLASH_SECTOR0<<memoryOffset);
	WDTCTL = WDTPW | WDTCNTCL;
	MAP_FlashCtl_eraseSector(BUFFER_MEMORY_START+memoryOffset*4096);
    WDTCTL = WDTPW | WDTCNTCL;
    MAP_FlashCtl_programMemory(buffer,(void*) (BUFFER_MEMORY_START+memoryOffset*4096), 4096 );
    WDTCTL = WDTPW | WDTCNTCL;
    MAP_FlashCtl_protectSector(FLASH_INFO_MEMORY_SPACE_BANK0,FLASH_SECTOR0<<memoryOffset);
    WDTCTL = WDTPW | WDTCNTCL;
    memoryOffset++;
    if (memoryOffset>=32){
    	P2OUT |= BIT1;
    	delay_1sec();
    	WDTCTL = (WDTPW-1);
    }
	} //end of almighty while
} // end of main

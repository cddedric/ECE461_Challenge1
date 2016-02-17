 //*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp432.h"
#include "driverlib.h"
#include "string.h"

#define BUFFER_MEMORY_START 0x020000
#define BUFFER_MEMORY_1		0x021000
#define BUFFER_MEMORY_2		0x022000
#define BUFFER_MEMORY_3		0x023000
#define BUFFER_MEMORY_4		0x024000
#define BUFFER_MEMORY_5		0x025000
#define BUFFER_MEMORY_6		0x026000
#define BUFFER_MEMORY_7		0x027000
#define BUFFER_MEMORY_8		0x028000
#define BUFFER_MEMORY_9		0x029000
#define BUFFER_MEMORY_10	0x02A000
#define BUFFER_MEMORY_11	0x02B000
#define BUFFER_MEMORY_12	0x02C000
#define BUFFER_MEMORY_13	0x02D000
#define BUFFER_MEMORY_14	0x02E000
#define BUFFER_MEMORY_15	0x02F000
#define BUFFER_MEMORY_16	0x030000
#define BUFFER_MEMORY_17	0x031000
#define BUFFER_MEMORY_18	0x032000
#define BUFFER_MEMORY_19	0x033000
#define BUFFER_MEMORY_20	0x034000
#define BUFFER_MEMORY_21	0x035000
#define BUFFER_MEMORY_22	0x036000
#define BUFFER_MEMORY_23	0x037000
#define BUFFER_MEMORY_24	0x038000
#define BUFFER_MEMORY_25	0x039000
#define BUFFER_MEMORY_26	0x03A000
#define BUFFER_MEMORY_27	0x03B000
#define BUFFER_MEMORY_28	0x03C000
#define BUFFER_MEMORY_29	0x03D000
#define BUFFER_MEMORY_30	0x03E000
#define BUFFER_MEMORY_31	0x03F000

/*
 * for some reason, the program would wander off into verification if I did not use defines.
 * Wandering off during either erase or program
 * This was my fix.
 */


void port_init()			//	port initialization function
{
	P1DIR &= ~BIT4;			// make P1.4 and input
	P1REN |= BIT4;			// enable pull resistor on P1.4
	P1OUT |= BIT4;			// make it a pull-up resistor
	P2DIR |= BIT0;			//make P2.1 an output (RED LED)
	P2DIR |= BIT1;			//make P2.1 an output (GREEN LED)
	P2OUT &= ~BIT0;			//turn off RED LED
	P2OUT &= ~BIT1;			//turn off GREEN LED
}
void delay_1sec()      	// 1 second delay for 1.5 MHz clock
{
	int  dcntr;			// delay counter variable

	for (dcntr=0;dcntr<57692;dcntr++);		//~1 second delay loop
	return;
}

void button_check()
{
	WDTCTL = WDTPW | WDTCNTCL;		//clear watchdog
	if (!(P1IN & BIT4)){				//check if button is pushed and initiate functions if true
		P2OUT |= BIT0;					//turn on RED LED
		delay_1sec();					//tie up the processor for roughly one second
		WDTCTL = (WDTPW-1);				//force a reset by the watchdog not getting the correct password when passed information or attempting changes
	} //outside of button push
}

void main(void)
{
	WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;	// Watchdog timer set to expire every second
	port_init();

//	PCM_setCoreVoltageLevel(PCM_VCORE1);
//	MAP_FlashCtl_setWaitState(FLASH_BANK0,2);
//	MAP_FlashCtl_setWaitState(FLASH_BANK1,2);

	while(1){
		WDTCTL = WDTPW | WDTCNTCL;		//clear watchdog each loop of the almighty while

	uint8_t buffer[4096];
	memset(buffer,0xA5,4096);
	button_check();

	MAP_FlashCtl_unprotectSector(FLASH_INFO_MEMORY_SPACE_BANK1,FLASH_SECTOR0|FLASH_SECTOR1|FLASH_SECTOR2|FLASH_SECTOR3|FLASH_SECTOR4|FLASH_SECTOR5
			|FLASH_SECTOR6|FLASH_SECTOR7|FLASH_SECTOR8|FLASH_SECTOR9|FLASH_SECTOR10|FLASH_SECTOR11|FLASH_SECTOR12|FLASH_SECTOR13|FLASH_SECTOR14
			|FLASH_SECTOR15|FLASH_SECTOR16|FLASH_SECTOR17|FLASH_SECTOR18|FLASH_SECTOR19|FLASH_SECTOR20|FLASH_SECTOR21|FLASH_SECTOR22|FLASH_SECTOR23
			|FLASH_SECTOR24|FLASH_SECTOR25|FLASH_SECTOR26|FLASH_SECTOR27|FLASH_SECTOR28|FLASH_SECTOR29|FLASH_SECTOR30|FLASH_SECTOR31);
	WDTCTL = WDTPW | WDTCNTCL;

	button_check();
	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_START));
	WDTCTL = WDTPW | WDTCNTCL;
    while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_START, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_1));
	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_1, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_2));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_2, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_3));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_3, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_4));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_4, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_5));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_5, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_6));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_6, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_7));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_7, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_8));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_8, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_9));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_9, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_10));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_10, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_11));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_11, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_12));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_12, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_13));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_13, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_14));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_14, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_15));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_15, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_16));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_16, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_17));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_17, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_18));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_18, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_19));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_19, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_20));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_20, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_21));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_21, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_22));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_22, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_23));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_23, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_24));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_24, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_25));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_25, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_26));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_26, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_27));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_27, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_28));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_28, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_29));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_29, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_30));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_30, 4096 ));

   	button_check();
 	while(!MAP_FlashCtl_eraseSector(BUFFER_MEMORY_31));
   	WDTCTL = WDTPW | WDTCNTCL;
   	while(!MAP_FlashCtl_programMemory(buffer,(void*) BUFFER_MEMORY_31, 4096 ));


    MAP_FlashCtl_protectSector(FLASH_INFO_MEMORY_SPACE_BANK1,FLASH_SECTOR0|FLASH_SECTOR1|FLASH_SECTOR2|FLASH_SECTOR3|FLASH_SECTOR4|FLASH_SECTOR5
			|FLASH_SECTOR6|FLASH_SECTOR7|FLASH_SECTOR8|FLASH_SECTOR9|FLASH_SECTOR10|FLASH_SECTOR11|FLASH_SECTOR12|FLASH_SECTOR13|FLASH_SECTOR14
			|FLASH_SECTOR15|FLASH_SECTOR16|FLASH_SECTOR17|FLASH_SECTOR18|FLASH_SECTOR19|FLASH_SECTOR20|FLASH_SECTOR21|FLASH_SECTOR22|FLASH_SECTOR23
			|FLASH_SECTOR24|FLASH_SECTOR25|FLASH_SECTOR26|FLASH_SECTOR27|FLASH_SECTOR28|FLASH_SECTOR29|FLASH_SECTOR30|FLASH_SECTOR31);


    							//COMPLETE
    WDTCTL = WDTPW | WDTCNTCL;	// CLEAR WATCHDOG
    P2OUT |= BIT1;				//TURN ON GREEN LED
    delay_1sec();				//LEAVE ON ONE SECOND
    WDTCTL = (WDTPW-1);			//RESET WITH WATCHDOG
	} //end of almighty while
} // end of main

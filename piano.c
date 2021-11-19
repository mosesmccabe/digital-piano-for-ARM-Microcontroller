// Piano.c
// This software configures the off-board piano keys
// Runs on TM4C123
// Program written Moses M.
// 
// Lab number: 4
// Hardware connections

#include "tm4c123gh6pm.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){ 
  unsigned int delay;
		SYSCTL_RCGC2_R  |= 0x10;       // Turn on PORTE clock
		delay = SYSCTL_RCGC2_R;        // allow clock to turn on
		GPIO_PORTE_DIR_R &= ~0x0F;      /* The direction register specifies bit for bit whether the 
																			corresponding pins are input or output 1-output 0-input */													
		GPIO_PORTE_DEN_R |= 0x0F;      //  enable the corresponding I/O pins by writing ones
		GPIO_PORTE_AMSEL_R  &= ~0xFF;  //  disable the analog funct PF7-0
		GPIO_PORTE_AFSEL_R &= ~0xFF;   // disable alt funct on PF7-0
    GPIO_PORTE_IS_R &= ~0x0F;                          // (d) PF4 is edge-sensitive
    GPIO_PORTE_IBE_R |= 0x0F;                         //     PF4 is ON both edges
    GPIO_PORTE_IEV_R &= ~0x0F;                         //   PF4 falling edge event
    GPIO_PORTE_ICR_R = 0x0F;                           // (e) clear flag4
    GPIO_PORTE_IM_R |= 0x0F;                           // (f) arm interrupt on PE4
	  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x000000E0; // port e
    NVIC_EN0_R = 0x00000010;                           // (h) enable interrupt 30 in NVIC	
}
// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2 and 0x08 is just key3
int Key = 0;
unsigned long Piano_In(void){ 
   if((GPIO_PORTE_DATA_R & 0x0F) == 0x01)      // true if SW0 is pressed
			 Key = 0x01;                             // set Key
	 else if((GPIO_PORTE_DATA_R & 0x0F) == 0x02) // true if SW1 is pressed
			Key = 0x02;                              // set Key
	 else if((GPIO_PORTE_DATA_R & 0x0F) == 0x04) // true if SW2 is pressed
			Key = 0x04;                              // set Key
	 else if((GPIO_PORTE_DATA_R & 0x0F) == 0x08) // true if SW3 is pressed
			Key =  0x05;                             // set Key
	 else if((GPIO_PORTE_DATA_R & 0x0F) == 0x00) // true if no SW are pressed
		 Key = 0;                                  // set Key to zero
	 return Key;									// return Key 
}


// Insert the Handler for key input according to your output choice
// refer to start.s for ISR names

// set up a pin to check heart wave
void PortF_Init(void)
{
	  unsigned int delay;
		SYSCTL_RCGC2_R  |= 0x20;                           // Turn on PORTF clock
		delay = SYSCTL_RCGC2_R;                            // allow clock to turn on
	  GPIO_PORTF_LOCK_R = 0x4C4F434B;										 // unlock PortF
	  GPIO_PORTF_DIR_R |= 0x02;                         /* The direction register specifies bit for bit whether the 
																	                  		   corresponding pins are input or output 1-output 0-input */
		GPIO_PORTF_DEN_R |= 0x02;                          //  enable the corresponding I/O pins by writing ones
		GPIO_PORTF_AMSEL_R  &= ~0x02;                       //  disable the analog funct PF7-0
		GPIO_PORTF_AFSEL_R &= ~0x02;                        // disable alt funct on PF7-0	
		
}

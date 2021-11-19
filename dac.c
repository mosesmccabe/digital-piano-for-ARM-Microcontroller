// dac.c
// This software configures DAC output
// Runs on TM4C123
// Program written by: put your names here
// Date Created: 
// Last Modified: 
// Lab number: 4
// Hardware connections

#include "tm4c123gh6pm.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************DAC_Init*********************
// Initialize 5-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
		unsigned int delay;
	  SYSCTL_RCGC2_R  |= 0x02;       // Turn on PORTB clock
		delay = SYSCTL_RCGC2_R;        // allow clock to turn on
		GPIO_PORTB_DIR_R |= 0x7C;      /* The direction register specifies bit for bit whether the 
																			corresponding pins are input or output 1-output 0-input */													
		GPIO_PORTB_DEN_R |= 0x7C;      //  enable the corresponding I/O pins by writing ones
		GPIO_PORTB_AMSEL_R  &= ~0xFF;  //  disable the analog funct PF7-0
		GPIO_PORTB_AFSEL_R &= ~0xFF;   // disable alt funct on PF7-0	
}

// **************DAC_Out*********************
// output to DAC
// Input: 5-bit data, 0 to 31 
// Output: none
void DAC_Out(unsigned long data){
	GPIO_PORTB_DATA_R = data << 2;    // set DAC value. shift it by 2 becuase we're using PB2,PB3,PB4,PB5,PB6
}

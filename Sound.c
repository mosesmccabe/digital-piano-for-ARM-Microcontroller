// Sound.c, 
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: Moses
// Lab number: 4
// Hardware connections
#include "tm4c123gh6pm.h"
#include "dac.h"
#include "Piano.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

/*    Sound Wave
0x10,0x14,0x19,0x1c,0x1e,0x1f,0x1e,0x1c,0x19,0x14,
0x10,0xb,0x6,0x3,0x1,0x0,0x1,0x3,0x6,0xb, */
int soundWave[20] = {0x10,0x14,0x19,0x1c,0x1e,0x1f,0x1e,0x1c,0x19,
										 0x14,0x10,0xb,0x6,0x3,0x1,0x0,0x1,0x3,0x6,0xb};



// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Input: Initial interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(unsigned long period){
	DAC_Init();
	NVIC_ST_CTRL_R = 0;         // disable SysTick 
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1
  NVIC_ST_CTRL_R = 0x0007; // enable SysTick with interrupts

}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disables sound output
// Output: none
int ind = 0;
void Sound_Play(unsigned long period){
	DAC_Out(soundWave[ind]);  //pass a value from array "soundWave" into PORTE_DATA_R
	ind++;                    // increment array index by one
	if (ind == 19)            // if index is equal to array size - 1. set index to zero
		ind = 0;
	
	NVIC_ST_RELOAD_R =(80000000)/(20*(period)) - 1;   // set sysTick reload value
	NVIC_ST_CURRENT_R = 0;														// and write to current clear it
}



// Interrupt service routine
// Executed periodically, the actual period
// determined by the current Reload.
void SysTick_Handler(void){
 GPIO_PORTF_DATA_R = 0x02;                // set PF1 to high
 if((Piano_In() & 0x01) )                  // true Piano_In() return value is the same as 0x01. meaning SW0 is press
		Sound_Play(440);                       // set call Sound_Play and pass the frequency 440
	else if((Piano_In() & 0x02) ) 					 // true if SW2 is pressed 
		Sound_Play(494);											 // set call Sound_Play and pass the frequency 494
	else if((Piano_In() & 0x04) )						 // true if SW3 is pressed
		Sound_Play(262);											 // set call Sound_Play and pass the frequency 262
	else if((Piano_In() & 0x08) )						 // true if SW4 is pressed
		Sound_Play(294);											 // set call Sound_Play and pass the frequency 494
  else if((Piano_In() & 0x00))						 // true if no SW are pressed
		NVIC_ST_RELOAD_R = 0;									 // set sysTick Reload value to low
	GPIO_PORTF_DATA_R = 0x00;								// set PF1 to low
}

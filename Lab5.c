// Lab4.c
// Runs on TM4C123
// Program written Moses Mccabe
// Date Created: 
// Last Modified:  
// Lab number: 4
// Brief description of the program
//  
// Hardware connections




#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
	
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);
void PortE_Init(void);   
void PortF_Init(void);



int main(void){
// call Initialization functions
PLL_Init();       
DAC_Init();
Piano_Init();
Sound_Init(0x00FFFFFF);
PortF_Init();

EnableInterrupts();   // enable global Interrupts
while(1){
	WaitForInterrupt();	 // was for interrupt. wait for SW to be pressed.
}

}

#include <stdio.h>
#include <stdint.h>

int main(void){
	uint32_t *pClockControlRegister = (uint32_t *)0x40023830;
	uint32_t *pPortDmodeRegister = (uint32_t *)0x40020C00;
	uint32_t *pGPIOoutputDataRegister = (uint32_t *)0x40020C14;

	// 1. enable clock for GPIOD peripheral in AHB1ENR
	// looking at the RCC AHB1ENR peripheral clock enable register we see we must only set the fourth bit (index 3!!)
	// the mask to change the fourth bit is 0x00000008
	*pClockControlRegister |= 0x08; // dereference and set
	// RCC > AHB1ENR > GPIODEN

	// 2. configure the GPIO mode of the IO pin as output
	// each pin consumes two bits. we need pin with index 12 (bits 24 and 25). must write 01 there (see under table in reference manual) but first
	// a. CLEAR bits on position 24 and 25
	*pPortDmodeRegister &= 0XFCFFFFFF;
	// b. SET 01 on position 24 and 25
	*pPortDmodeRegister |= 0x01000000;
	// GPIOD > MODER > MODER12

	// 3. set 12th bit of the output data register to make I/O pin 12 as HIGH
	// the mask is 0x00001000
	*pGPIOoutputDataRegister |= 0x1000;
	// GPIOD > ODR > ODR12

	while(1);
}

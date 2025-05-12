#include <stdio.h>
#include <stdint.h>

int main(void){
    uint32_t *pClockControlRegister = (uint32_t *)0x40023830;
    uint32_t *pPortDmodeRegister = (uint32_t *)0x40020C00;
    uint32_t *pPortAmodeRegister = (uint32_t *)0x40020000;
    uint32_t *pGPIOinputDataRegister = (uint32_t *)0x40020010;
    uint32_t *pGPIOoutputDataRegister = (uint32_t *)0x40020C14;

    // 1. enable RCC clock for GPIOD and GPIOA peripherals on AHB1ENR
    // bit 0 corresponds to GPIOA and bit 3 corresponds to GPIOD
    *pClockControlRegister |= ( 9 << 0 ); // dereference and set
    // RCC > AHB1ENR > GPIODEN
    // RCC > AHB1ENR > GPIOAEN


    // 2. configure the GPIO mode of port D, pin 12 as output
    // each pin consumes two bits. we need pin with index 12 (bits 24 and 25). must write 01 there (see under table in reference manual) but first
    // a. CLEAR bits on position 24 and 25
    *pPortDmodeRegister &= ~( 3 << 24 );
    // shifts binary 3 (0011) to the left on indexes 24 and 25, then performs NOT operator, dereferences and performs AND operator
    // b. SET 01 (output) on position 24 and 25
    *pPortDmodeRegister |= ( 1 << 24 );
    // GPIOD > MODER > MODER12


    // 3. input mode configuration of GPIOA, pin 0: although offset mode is 0x00 and bits of input mode are also 00, the bits at indexes 0 and 1 still need to be cleared for safety
    *pPortAmodeRegister &= ~( 3 << 0);
    // GPIOA > MODER > MODER0


    while(1){
    	// if port A, pin 0 reads 1 (3.3V) at bit index 0 of data input register, then turn on LED
    	if((*pGPIOinputDataRegister & 0x01) == 0x01){	// GPIOA > IDR > IDR0
    	    *pGPIOoutputDataRegister |= ( 1 << 12 );	// GPIOD > ODR > ODR12
    	// else, if port A, pin 0 reads 0 (0V meaning pin 0 is connected to GND or wire is disconnected and pin floats) at index bit 0 of data input register, then turn off LED
    	}else{
    		*pGPIOoutputDataRegister &= ~( 1 << 12 );
    	}
    }
}

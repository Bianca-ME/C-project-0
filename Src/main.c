#include <stdio.h>
#include <stdint.h>
#include "main.h"

int main(void){
    RCC_AGB1ENR_typedef *pClockControlRegister = (RCC_AGB1ENR_typedef*)0x40023830;
    GPIOx_MODE_typedef *pPortAmodeRegister = (GPIOx_MODE_typedef*)0x40020000;
    GPIOx_MODE_typedef *pPortDmodeRegister = (GPIOx_MODE_typedef*)0x40020C00;
    GPIOx_ODR_typedef *pGPIOoutputDataRegister = (GPIOx_ODR_typedef*)0x40020C14;
    GPIOx_IDR_typedef *pGPIOinputDataRegister = (GPIOx_IDR_typedef*)0x40020010;

    // 1. enable RCC clock for GPIOA and GPIOD peripherals on AHB1ENR
    pClockControlRegister->gpioa_en = 1;
    pClockControlRegister->gpiod_en = 1;
    // RCC > AHB1ENR > GPIODEN
    // RCC > AHB1ENR > GPIOAEN


    // 2. configure GPIO mode of port D, pin 12 as output (01)
    pPortDmodeRegister->pin_12 = 1;
    // GPIOD > MODER > MODER12


    // 3. configure GPIOA mode of port A, pin 0 as output (00)
    pPortAmodeRegister->pin_0 = 0;
    // GPIOA > MODER > MODER0


    while(1){
    	// if port A, pin 0 reads 1 (3.3V) at bit index 0 of data input register, then turn on LED
    	if(pGPIOinputDataRegister->pin_0){			// GPIOA > IDR > IDR0
    	    pGPIOoutputDataRegister->pin_12 = 1;	// GPIOD > ODR > ODR12
    	// else, if port A, pin 0 reads 0 (0V meaning pin 0 is connected to GND or wire is disconnected and pin floats) at index bit 0 of data input register, then turn off LED
    	}else{
    		pGPIOoutputDataRegister->pin_12 = 0;
    	}
    }
}

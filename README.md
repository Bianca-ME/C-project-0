# C project 0 (ongoing)

My first C project for an STM32F407 DISCOVERY board with a 32-bit Arm Cortex-M4 processor.
Main functionality: turning on a LED.

## Overview
The focus is on the file `main.c` which contains the practice I did during an embedded systems course for complete beginners (in C).
The commits are thought as stages of the progress, so with each commit there is a small improvement or change of how the board works.

## Stages of the project
1. Hard-coded memory addresses and manipulating registers using bitwise operations and masks (no bit shifting). [link to commit](https://github.com/Bianca-ME/C-project-0/commit/692966c2cd17504de6c5be6e0eabd40623fe4ac8)

   Registers used:
   - RCC_AHB1ENR for clock enable
   - GPIOx_MODER for mode
   - GPIOx_ODR for data output
3. Implementation of bit shifting. [link to commit](https://github.com/Bianca-ME/C-project-0/commit/99c8e5077f1c169965f5991ff58d6ac133c172aa)
4. Implementation of loop and delays to toggle LED. [link to commit](https://github.com/Bianca-ME/C-project-0/commit/dc57f67ec9aafcae4667c767508b83f1d0e85029)
5. LED toggle based on input reading. The input read checks if there is current or not. [link to commit](https://github.com/Bianca-ME/C-project-0/commit/c113a7f659858b262f5d985114416343a7a1375e)

   Register added:
   - GPIOx_IDR for input
  
## IDE used:
STM32CubeIDE

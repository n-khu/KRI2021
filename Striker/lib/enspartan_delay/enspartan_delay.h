/*==============================================================================================
								      PROJECT ENSPARTAN Ver.1.0
								      SYSTICK DELAY LIBRARY
==============================================================================================*/

#include "stm32f4xx.h"
#ifndef __ENSPARTAN_DELAY_H
#define __ENSPARTAN_DELAY_H

//SYSTICK DELAY PROTOTYPE

void SysTick_Init(void);
void TimeTick_Decrement(void);
void delay_us(u32 n);
void delay_1ms(void);
void delay_ms(u32 n);

#endif

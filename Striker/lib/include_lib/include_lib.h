/*==============================================================================================
								 PROJECT ENSPARTAN Ver.1.0
								  	 MAIN LIBRARY
==============================================================================================*/

#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

/*============================== STM LIBRARY ======================================*/
#include <stm32f4xx.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

// #include <stm32f4xx_spi.h>
// #include <stm32f4xx_dac.h>
/*============================== C library ======================================*/
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "stdbool.h"

/*============================== ENSPARTAN LIBRARY ======================================*/
#include <enspartan_inisialisasi.h>
#include <enspartan_pushbutton.h>
#include <enspartan_algorithm.h>
#include <enspartan_variabel.h>
#include <enspartan_delay.h>
#include <enspartan_motor.h>
#include <bw_i2c_lcd.h>
#include <usart_com.h>


// void *_sbrk(int incr) { return (void *)-1; }

//Global Typedef
GPIO_InitTypeDef  			GPIO_InitStructure, GPIO_I2C,GPIO_InitStructure;
I2C_InitTypeDef  			I2C_InitStructure;
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_OCInitTypeDef           TIM_OCInitStructure;

// GPIO TYPEDEF
GPIO_InitTypeDef          	GPIO_InitStructure;

// TIMER & INTERRUPT TYPEDEF
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_OCInitTypeDef           TIM_OCInitStructure;
NVIC_InitTypeDef 			NVIC_InitStructure;

//I2C COMMUNICATION TYPEDEF
I2C_InitTypeDef  			I2C_InitStructure;
 
#endif
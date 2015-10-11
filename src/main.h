/*
 * main.h
 *
 *  Created on: Sep 22, 2015
 *      Author: Azizou Ogbone
 */

#ifndef _MAIN_H
#define _MAIN_H

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <math.h>
#include "pins.h"
#include "init.h"
#include "led_io.h"
#include "pitch.h"
#include "stm32f4xx_it.h"


/* Private macro */
// #define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
// #define TIMER_CLOCK			84E6  TIM6 runs at 84MHz 

#define TIMER_FREQUENCY 100000

// void UART_Configuration(void);
// void DAC_Configuration(void);
void delay_ms(uint32_t milli);
void TIM3_IRQHandler(void);

#endif /* MAIN_H_ */

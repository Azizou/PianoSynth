/*
 * main.h
 *
 *  Created on: Sep 22, 2015
 *      Author: Azizou Ogbone
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Includes */
#include <math.h>

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "init.h"
#include "pitch.h"
#include "wavetable.h"
#include "lcd.h"


/* Private macro */
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */

float pitch = 880; //default frequency
uint16_t numWaves = 4;
uint32_t buttonVal = 0;

//uint32_t dma_mode = DMA_Mode_Circular;
uint16_t volume = 10;

// void EXTILines_Config(void);
void EXTILine_Config(uint32_t GPIO_Pin, uint32_t EXTI_Lin, uint32_t EXTI_PinSource, uint32_t EXTI_IRQn);
void delay_ms(uint32_t milli);
uint16_t UpdateTimerPeriod(uint16_t tickRate,uint16_t freqTimer);
uint32_t UpdateTimerFrequency();

#endif /* MAIN_H_ */

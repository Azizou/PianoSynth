/*
 * main.h
 *
 *  Created on: Sep 22, 2015
 *      Author: Azizou Ogbone
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <math.h>
#include "pitch.h"
#include "lcd.h"

/* Private macro */
#define DACBUFFERSIZE 		250
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */

float pitch = 880; //default frequency
uint16_t numWaves = 4;
uint32_t buttonVal = 0;

//uint32_t dma_mode = DMA_Mode_Circular;
uint16_t volume = 10;
uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];
uint8_t * lcdLine1;				/* The first line to be displayed on the LCD */
uint8_t lcdLine2[16];				/* The second line to be displayed on the LCD */

void RCC_Configuration(void);
void DMA_Configuration( uint16_t* wavBuffer );
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuration(void);
void Timer_Configuration(uint16_t wavPeriod, uint16_t preScaler);
void DAC_Configuration(void);
void delay_ms(uint32_t milli);
uint16_t UpdateTimerPeriod(uint16_t tickRate,uint16_t freqTimer);
uint32_t UpdateTimerFrequency();

#endif /* MAIN_H_ */

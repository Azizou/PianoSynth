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
#include "pins.h"

/* Private macro */
#define DACBUFFERSIZE 		250
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */

int button_index;
int note_index;
int key_index;

uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];

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

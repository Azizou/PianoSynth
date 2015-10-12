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

/*** CODE FOR TIMER 6 ****/
#define DACBUFFERSIZE 		250
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */
#define TIMERFREQ			42E6

 int button_index;
int note_index;
int key_index;

uint16_t timerFreq;
uint16_t timerPeriod;

uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];

 /******************/

#define TIMER_FREQUENCY 100000

uint8_t *lcdLine1;	/* The first line to be displayed on the LCD */
uint8_t lcdLine2[16];	/* The second line to be displayed on the LCD */

// void UART_Configuration(void);
// void DAC_Configuration(void);
void delay_ms(uint32_t milli);
void TIM3_IRQHandler(void);

#endif /* MAIN_H_ */

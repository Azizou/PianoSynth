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
#include "init.h"

/* Private macro */

int button_index;
int note_index;
int key_index;

static int pressed = 0;
uint16_t timerFreq;
uint16_t timerPeriod;

uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];

void RCC_Configuration(void);
void DMA_Configuration( uint16_t* wavBuffer );
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuration(void);
//void Timer_Configuration(uint16_t wavPeriod, uint16_t preScaler);
void DAC_Configuration(void);
void delay_ms(uint32_t milli);
void UpdateTimerPeriod();
void setWave(int waveform);
//void UpdateTimerFrequency();

#endif /* MAIN_H_ */

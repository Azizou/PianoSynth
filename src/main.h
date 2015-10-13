/**
 *    PianoSynth
 **** Main Global Definitions ***
 */

#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <math.h>
#include "pins.h"
#include "init.h"
#include "led_io.h"
#include "pitch.h"

#define TIMER_FREQUENCY 100000	// Carrier wave for audio generation

uint8_t *lcdLine1;	/* The first line to be displayed on the LCD */
uint8_t lcdLine2[16];	/* The second line to be displayed on the LCD */

/* Waveform generation variables */
uint32_t sampleCounter;
uint8_t numButtonsPressed;
uint32_t currentSample;
uint8_t i;

/* LED variables */
uint8_t led_flag;
uint8_t ledd_flag;

void TIM3_IRQHandler(void);

#endif /* MAIN_H_ */

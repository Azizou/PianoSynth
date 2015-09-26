/*
 * wavetable.h
 *
 *  Created on: Sep 22, 2015
 *      Author: Poon Donohoe
 */

 #include "stm32f4xx.h"
 #include <math.h>

#ifndef WAVETABLE_H_
#define WAVETABLE_H_
#define DACBUFFERSIZE 		250

uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];

void initWaveforms(void);

#endif /* WAVETABLE_H_ */

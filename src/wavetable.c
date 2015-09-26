/*
 * wavetable.c
 *
 *  Created on: Sep 22, 2015
 *      Author: Poon Donohoe
 */

 #include "wavetable.h"
 

 void initWaveforms(void){
 	uint16_t n;
	uint16_t m;
	/* Create wave table for sinewave */
	// malloc(uint16_t *) SineWaveBuffer
	for (n = 0; n<DACBUFFERSIZE; n++)
	{
		SineWaveBuffer[n] = (uint16_t)((4095)/2.0)*( sin( M_TWOPI*n/DACBUFFERSIZE) + 1.0 );
	}
	for (n = 0; n<DACBUFFERSIZE; n++)
	{
		SawtoothBuffer[n] = (uint16_t)(m*n);
	}
	for (n = 0; n<DACBUFFERSIZE/2; n++)
	{
		PulseWaveTable[n] = 4095;
		PulseWaveTable[DACBUFFERSIZE - n] = 0;
	}
	uint16_t result = 0;
	m = 2*m-1;
	for (n = 0; n<DACBUFFERSIZE/2; n++)
	{
		result = (uint16_t)m*n;
		TriangleWaveTable[n] = result;
		TriangleWaveTable[DACBUFFERSIZE - n-1] = result;
	}
 }



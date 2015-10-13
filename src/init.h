/**
 *    PianoSynth
 **** Initialization function definitions ***
 */

#ifndef _INIT_H
#define _INIT_H
#include "main.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void Timer_Configuration(void);
void DAC_Configuration(void);

#endif /* _INIT_H */
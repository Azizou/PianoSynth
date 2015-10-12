/**
  *	Contain all intialisations code
  *
  */


#ifndef _INIT_H
#define _INIT_H
  
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define DACBUFFERSIZE 		250
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */
#define TIMERFREQ			42E6
void RCC_Configuration(void);
void DMA_Configuration( uint16_t* wavBuffer );
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuration(void);
void Timer_Configuration();
void DAC_Configuration(void);
void EXTI_Line_Config(void);

#endif

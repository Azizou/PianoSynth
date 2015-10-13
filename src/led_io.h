/**
 *    PianoSynth
 **** LED Interface Definitions ***
 */

#ifndef _LED_IO_H
#define _LED_IO_H
#include "main.h"


#define LED00_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED01_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED02_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED03_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED04_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED05_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED06_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED07_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED08_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LED09_GPIO_CLK         RCC_AHB1Periph_GPIOE

#define LED0n 							   10
#define LED00_PIN						   GPIO_Pin_4
#define LED01_PIN						   GPIO_Pin_5
#define LED02_PIN              GPIO_Pin_6
#define LED03_PIN              GPIO_Pin_7
#define LED04_PIN              GPIO_Pin_8
#define LED05_PIN              GPIO_Pin_9
#define LED06_PIN              GPIO_Pin_10
#define LED07_PIN              GPIO_Pin_11
#define LED08_PIN              GPIO_Pin_12
#define LED09_PIN              GPIO_Pin_13

#define LED00_GPIO_PORT  			GPIOE
#define LED01_GPIO_PORT  			GPIOE
#define LED02_GPIO_PORT  			GPIOE
#define LED03_GPIO_PORT  			GPIOE
#define LED04_GPIO_PORT  			GPIOE
#define LED05_GPIO_PORT  			GPIOE
#define LED06_GPIO_PORT  			GPIOE
#define LED07_GPIO_PORT  			GPIOE
#define LED08_GPIO_PORT  			GPIOE
#define LED09_GPIO_PORT  			GPIOE

typedef enum {
  LED00 = 0,
  LED01 = 1, 
  LED02 = 2, 
  LED03 = 3, 
  LED04 = 4, 
  LED05 = 5, 
  LED06 = 6,
  LED07 = 7,
  LED08 = 8,
  LED09 = 9
} LED_TypDef;

void LED_Init(); 
void LED_Init(LED_TypDef Led);                                 
void LEDToggle(LED_TypDef Led);
void LEDOff(LED_TypDef Led);
void LEDOn(LED_TypDef Led);

#endif
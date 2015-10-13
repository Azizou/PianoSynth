/**
 *    PianoSynth
 **** Offboard LED Interface ***
 */

#include "led_io.h"

GPIO_TypeDef* GPIO_00_PORT[LED0n] = {LED01_GPIO_PORT, LED02_GPIO_PORT, LED03_GPIO_PORT, LED04_GPIO_PORT, LED05_GPIO_PORT, LED06_GPIO_PORT,LED07_GPIO_PORT, LED08_GPIO_PORT, LED09_GPIO_PORT};

const uint16_t GPIO_00_PIN[LED0n] = {LED00_PIN,LED01_PIN,LED02_PIN,LED03_PIN,LED04_PIN,LED05_PIN,LED06_PIN,LED07_PIN, LED08_PIN,LED09_PIN};

const uint32_t GPIO_00_CLK[LED0n] = {LED00_GPIO_CLK, LED01_GPIO_CLK,LED02_GPIO_CLK, LED03_GPIO_CLK, LED04_GPIO_CLK, LED05_GPIO_CLK, LED06_GPIO_CLK, LED07_GPIO_CLK, LED08_GPIO_CLK, LED09_GPIO_CLK};

void LEDOn(LED_TypDef Led)
{
  GPIO_00_PORT[Led]->BSRRL = GPIO_00_PIN[Led];  
}

void LEDOff(LED_TypDef Led)
{
  GPIO_00_PORT[Led]->BSRRH = GPIO_00_PIN[Led];  
}

void LEDToggle(LED_TypDef Led)
{
  GPIO_00_PORT[Led]->ODR ^= GPIO_00_PIN[Led];
}

void LED_Init(){
  LED_Init(LED00);
  LED_Init(LED01);
  LED_Init(LED02);
  LED_Init(LED03);
  LED_Init(LED04);
  LED_Init(LED05);
  LED_Init(LED06);
  LED_Init(LED07);
  LED_Init(LED08);
  LED_Init(LED09);
}
void LED_Init(LED_TypDef Led){
  GPIO_InitTypeDef  GPIO_InitStructure;  
  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(GPIO_00_CLK[Led], ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_00_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_00_PORT[Led], &GPIO_InitStructure);
}


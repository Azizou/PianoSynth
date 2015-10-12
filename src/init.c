#include "init.h"

// TODO: REMOVE EXTI CODE

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
  /* Enable GPIOE, GPIOD clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOD | , ENABLE);
  /* Enable TIM3 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* Enable DAC clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Enable Buttons */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_InitStructure.GPIO_Pin = BUTTON0_PIN;
  GPIO_Init(BUTTON0_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON1_PIN;
  GPIO_Init(BUTTON1_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON2_PIN;
  GPIO_Init(BUTTON2_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON3_PIN;
  GPIO_Init(BUTTON3_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON4_PIN;
  GPIO_Init(BUTTON4_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON5_PIN;
  GPIO_Init(BUTTON5_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON6_PIN;
  GPIO_Init(BUTTON6_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON7_PIN;
  GPIO_Init(BUTTON7_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON8_PIN;
  GPIO_Init(BUTTON8_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON9_PIN;
  GPIO_Init(BUTTON9_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON10_PIN;
  GPIO_Init(BUTTON10_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON11_PIN;
  GPIO_Init(BUTTON11_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON12_PIN;
  GPIO_Init(BUTTON12_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BUTTON13_PIN;
  GPIO_Init(BUTTON13_PORT, &GPIO_InitStructure);

}

/**
  * @brief  Configures the Nested Vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//set up the interrupt handler for TIM3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

/** 
  * Configure TIM3 to run at 100kHz OR 10kHz
  * TODO: TEST THIS!!!!!
  */
void Timer_Configuration(void){
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

  TIM_TimeBaseInitStruct.TIM_Period = 10-1; //TIM3 has a frequency of 10000Hz
  TIM_TimeBaseInitStruct.TIM_Prescaler = 840-1;
  TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  /* TIM interrupt enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

/**
 * Set up the DAC in Trigger_None mode
 */

void DAC_Configuration(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  DAC_InitTypeDef DAC_InitStructure;

  /* GPIO CONFIGURATION of DAC speaker Pin */

  GPIO_InitStruct.GPIO_Pin = SPEAKER_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SPEAKER_PORT, &GPIO_InitStruct);

  /* DAC channel 2 Configuration */ 
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None; 
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None; 
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; 
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* Enable DAC Channel2 */ 
  DAC_Cmd(DAC_Channel_2, ENABLE);

  // TODO: TRY SOFTWARE TRIGGER IF THIS GIVES PROBLEMS
  // DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
  // Then, fire trigger using:
  // DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}
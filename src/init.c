#include "init.h"

// TODO: REMOVE EXTI CODE

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure, GPIO_InitStruct;

  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
  						RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
  /* Enable TIM3 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM6, ENABLE);
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

  /* Enable Toggle Switches */
  GPIO_InitStruct.GPIO_Pin = SPEAKER_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(SPEAKER_PORT, &GPIO_InitStruct);
  //toggle switch 0
  GPIO_InitStruct.GPIO_Pin = TOGGLE_SWITCH0;
  GPIO_Init(CUSTOMTOGGLE_PORT0, &GPIO_InitStruct);
  //toggle switch 1
  GPIO_InitStruct.GPIO_Pin = TOGGLE_SWITCH1;
  GPIO_Init(CUSTOMTOGGLE_PORT1, &GPIO_InitStruct);
  //toggle switch 2
  GPIO_InitStruct.GPIO_Pin = TOGGLE_SWITCH2;
  GPIO_Init(CUSTOMTOGGLE_PORT2, &GPIO_InitStruct);
  //toggle switch 3
  GPIO_InitStruct.GPIO_Pin = TOGGLE_SWITCH3;
  GPIO_Init(CUSTOMTOGGLE_PORT3, &GPIO_InitStruct);

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

  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

  TIM_TimeBaseInitStruct.TIM_Period = 840; //TIM3 has a frequency of 100000Hz
  TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
  TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  /* TIM interrupt enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);



  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
  /* pack Timer struct */
  TIM_TimeBaseStruct.TIM_Period = timerPeriod-1;
  TIM_TimeBaseStruct.TIM_Prescaler = TIMER6_PRESCALER-1;
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x0000;
  /* Call init function */
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStruct);
  /* Select Timer to trigger DAC */
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, DISABLE);
}

// /**
//  * Set up the DAC in Trigger_None mode
//  */

// void DAC_Configuration(void){
//   GPIO_InitTypeDef GPIO_InitStruct;
//   DAC_InitTypeDef DAC_InitStructure;

//   /* GPIO CONFIGURATION of DAC speaker Pin */

//   GPIO_InitStruct.GPIO_Pin = SPEAKER_PIN;
//   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//   GPIO_Init(SPEAKER_PORT, &GPIO_InitStruct);

//   /* DAC channel 2 Configuration */ 
//   DAC_InitStructure.DAC_Trigger = DAC_Trigger_None; 
//   DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None; 
//   DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; 
//   DAC_Init(DAC_Channel_2, &DAC_InitStructure);

//   /* Enable DAC Channel2 */ 
//   DAC_Cmd(DAC_Channel_2, ENABLE);

//   // TODO: TRY SOFTWARE TRIGGER IF THIS GIVES PROBLEMS
//   // DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
//   // Then, fire trigger using:
//   // DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
// }

void DMA_Configuration(uint16_t* wavBuffer)
{
	DMA_InitTypeDef DMA_InitStructure;
	//Initialize the structure to default values
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(DAC_BASE + 0x08);  //DAC channel1 12-bit right-aligned data holding register (ref manual pg. 264)
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)wavBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = DACBUFFERSIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	/* Call Init function */
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	/* Enable DMA */
	DMA_Cmd(DMA1_Stream5, ENABLE);
}

void DAC_Configuration(void)
{
	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	DAC_DMACmd(DAC_Channel_1, ENABLE);
	/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter. */
	DAC_Cmd(DAC_Channel_1, ENABLE);
}
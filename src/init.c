#include "init.h"
#include "pins.h"
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)

void RCC_Configuration(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init (&NVIC_InitStructure);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = SPEAKER_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* Call Init function */
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

void Timer_Configuration()
{
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
	TIM_Cmd(TIM6, ENABLE);
}
/**
  * @brief  Configures the DAC
  * @param  None
  * @retval : None
  */
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

void EXTI_Line_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;// | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);// | EXTI_PinSource1 | EXTI_PinSource2 | EXTI_PinSource3);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource12);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3| EXTI_Line4| EXTI_Line5| EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9 | EXTI_Line10 | EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}

//
//void ADC3_CH12_DMA_Config(void)
//{
//	static int ADC3ConvertedValue = 0;
//  ADC_InitTypeDef       ADC_InitStructure;
//  ADC_CommonInitTypeDef ADC_CommonInitStructure;
//  DMA_InitTypeDef       DMA_InitStructure;
//  GPIO_InitTypeDef      GPIO_InitStructure;
//
//  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
//
//  /* DMA2 Stream0 channel0 configuration **************************************/
//  DMA_InitStructure.DMA_Channel = DMA_Channel_2;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//  DMA_InitStructure.DMA_BufferSize = 1;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
//  DMA_Cmd(DMA2_Stream0, ENABLE);
//
//  /* Configure ADC3 Channel12 pin as analog input ******************************/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//  /* ADC Common Init **********************************************************/
//  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
//  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
//  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
//  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
//  ADC_CommonInit(&ADC_CommonInitStructure);
//
//  /* ADC3 Init ****************************************************************/
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
//  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//  ADC_InitStructure.ADC_NbrOfConversion = 1;
//  ADC_Init(ADC3, &ADC_InitStructure);
//
//  /* ADC3 regular channel12 configuration *************************************/
//  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
//
// /* Enable DMA request after last transfer (Single-ADC mode) */
//  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
//
//  /* Enable ADC3 DMA */
//  ADC_DMACmd(ADC3, ENABLE);
//
//  /* Enable ADC3 */
//  ADC_Cmd(ADC3, ENABLE);
//}

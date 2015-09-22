/**

*****************************************************************************

**

**  File        : ECSA ELO PRAC - DAY 1

**

**  Abstract    : main function.

**

**  Functions   : main

**

**  Environment : Atollic TrueSTUDIO(R)

**                STMicroelectronics STM32F4xx Standard Peripherals Library

**

**  Distribution: The file is distributed as is, without any warranty

**                of any kind.

**

**  (c)Copyright Atollic AB.

**  You may use this file as-is or modify it according to the needs of your

**  project. Distribution of this file (unmodified or modified) is not

**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the

**  rights to distribute the assembled, compiled & linked contents of this

**  file as part of an application binary file, provided that it is built

**  using the Atollic TrueSTUDIO(R) toolchain.

**

**

*****************************************************************************

*/



/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <math.h>
#include "pitch.h"


/* Private macro */
#define DACBUFFERSIZE 		250
#define WAVEFREQ			1000 /* 1KHz */
#define TIMER6_PRESCALER	2 	/* produces a 42MHz tick */
#define TIMER_CLOCK			84E6 /* TIM6 runs at 84MHz */

//extern uint16_t pitch_index;
//extern float pitch_table[];
float pitch = 880;
/* Private variables */
uint16_t SineWaveBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 1*/
uint16_t SawtoothBuffer[DACBUFFERSIZE]; 	/* Array for  waveform 2*/
uint16_t PulseWaveTable[DACBUFFERSIZE];
uint16_t TriangleWaveTable[DACBUFFERSIZE];



/* Private function prototypes */

void RCC_Configuration(void);
void DMA_Configuration( uint16_t* wavBuffer );
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuration(void);
void Timer_Configuration(uint16_t wavPeriod, uint16_t preScaler);
void DAC_Configuration(void);
void delay_ms(uint32_t milli);
uint16_t UpdateTimerPeriod(uint16_t tickRate,uint16_t freqTimer);
uint32_t UpdateTimerFrequency();


uint8_t flag = 0;
uint8_t pitch_flag = 0;
uint8_t timer_flag = 0;


/*******************************************************************************

* Function Name  : TIM2_IRQHandler

* Description    : This function handles TIM2 global interrupt request.

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void TIM2_IRQHandler(void)

{

  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)

  {

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    //Do stuff here
  }

}





/**

**===========================================================================

**

**  Abstract: main program

**

**===========================================================================

*/

int main(void)

{

	uint32_t fTimer;

	uint32_t timerFreq;

	uint16_t timerPeriod;

	uint16_t n;

	uint16_t m;

	uint16_t numWaves = 4;

	uint32_t buttonVal = 0;

	/* Calculate the gradient of the Sawtooth */

	m = (uint16_t) ( 4096 / DACBUFFERSIZE);



	/* Create wave table for sinewave */

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



	/* Calculate frequency of timer */
//	fTimer = WAVEFREQ * DACBUFFERSIZE;
	fTimer = UpdateTimerFrequency();


	timerFreq = TIMER_CLOCK / TIMER6_PRESCALER; /* Timer tick is in Hz */



	/* Calculate period of Timer */

	timerPeriod = (uint16_t)( timerFreq / fTimer );



	/* System Clocks Configuration */

	RCC_Configuration();



	/* NVIC configuration */

	NVIC_Configuration();



	/* Configure the GPIO ports */

	GPIO_Configuration();



	/* Timer Configuration */

	Timer_Configuration( timerPeriod, TIMER6_PRESCALER );



	/* DAC Configuration */

	DAC_Configuration();


	/* Configure button */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	/* DMA Config --> Takes in a pointer to the waveform buffer */

	DMA_Configuration ( TriangleWaveTable );
	/* Infinite loop */

	while (1)

	{

	  /* Do stuff here... */
		if(0){//STM_EVAL_PBGetState(BUTTON_USER)== SET){
			buttonVal++;
			buttonVal %= numWaves;
			DMA_Cmd(DMA1_Stream5, DISABLE);	/* Disable the DMA */

			if(buttonVal== 0){
				DMA_Configuration ( SawtoothBuffer );
				//flag = 1;
			}
			else if (buttonVal== 1)
			{
				DMA_Configuration ( SineWaveBuffer );
			}
			else if (buttonVal== 2)
			{
				DMA_Configuration ( PulseWaveTable);
			}
			else if (buttonVal== 3)
			{
				DMA_Configuration ( TriangleWaveTable);
			}
			while(STM_EVAL_PBGetState(BUTTON_USER)== SET);   //Do nothing while the button is still pressed
			delay_ms(20); //debounce wait for 20ms
		}
		if(STM_EVAL_PBGetState(BUTTON_USER)== SET){//pitch_flag){//zero by default
			//reset the timer frequency
			pitch_index++;
			pitch_index %= 88;
			fTimer = UpdateTimerFrequency();
			timerPeriod = UpdateTimerPeriod(timerFreq ,fTimer);
			TIM_Cmd(TIM6, DISABLE);
			Timer_Configuration( timerPeriod, TIMER6_PRESCALER );
		}
	}

}

uint16_t UpdateTimerPeriod(uint16_t tickRate,uint16_t freqTimer){
	return (uint16_t)( tickRate / freqTimer );
}
uint32_t UpdateTimerFrequency(){
	return (uint32_t)pitch_table[pitch_index]*DACBUFFERSIZE;
}


/**

  * @brief  Configures the different system clocks.

  * @param  None

  * @retval : None

  */

void RCC_Configuration(void)

{

	/* Enable DMA and GPIOA Clocks */

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);



	/* Enable DAC1 and TIM6 clocks */

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6, ENABLE);

}



/**

  * @brief  Configures the nested vectored interrupt controller.

  * @param  None

  * @retval : None

  */

void NVIC_Configuration(void)

{

	NVIC_InitTypeDef NVIC_InitStructure;



}





/**

  * @brief  Configures the different GPIO ports.

  * @param  None

  * @retval : None

  */

void GPIO_Configuration(void)

{

	GPIO_InitTypeDef GPIO_InitStruct;



	/* Pack the struct */

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;

	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;

	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;



	/* Call Init function */

	GPIO_Init(GPIOA, &GPIO_InitStruct);



}



/**

  * @brief  Configures the DMA.

  * @param  None

  * @retval : None

  */

void DMA_Configuration( uint16_t* wavBuffer )

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



/**

  * @brief  Configures the Timers.

  * @param  wavePeriod (period of timer), preScaler (prescaler for timer)

  * @retval : None

  */

void Timer_Configuration(uint16_t wavPeriod, uint16_t preScaler)

{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;



	/* pack Timer struct */

	TIM_TimeBaseStruct.TIM_Period = wavPeriod-1;

	TIM_TimeBaseStruct.TIM_Prescaler = preScaler-1;

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



	/* Initialize the DAC_Trigger member */

	DAC_InitStruct.DAC_Trigger = DAC_Trigger_T6_TRGO;

	/* Initialize the DAC_WaveGeneration member */

	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;

	/* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */

	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;

	/* Initialize the DAC_OutputBuffer member */

	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;



	/* Init DAC */

	DAC_Init(DAC_Channel_1, &DAC_InitStruct);



	/* Enable DMA request */

	DAC_DMACmd(DAC_Channel_1, ENABLE);



	/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter. */

	DAC_Cmd(DAC_Channel_1, ENABLE);



}



/*

 * Callback used by stm32f4_discovery_audio_codec.c.

 * Refer to stm32f4_discovery_audio_codec.h for more info.

 */

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){

  /* TODO, implement your code here */

  return;

}



/*

 * Callback used by stm324xg_eval_audio_codec.c.

 * Refer to stm324xg_eval_audio_codec.h for more info.

 */

uint16_t EVAL_AUDIO_GetSampleCallBack(void){

  /* TODO, implement your code here */

  return -1;

}





/**

  * @brief  Simple delay in ms --> Maybe use for debouncing?

  * @param  integer amount of milliseconds

  * @retval None

  */

void delay_ms(uint32_t milli)

{

	uint32_t delay = milli * 17612;              // approximate loops per ms at 168 MHz, Debug config

	for(; delay != 0; delay--);

}


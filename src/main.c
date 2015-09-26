#include "main.h"

int main(void)
{
	uint32_t fTimer;
	uint32_t timerFreq;
	uint16_t timerPeriod;
	// uint16_t n;
	// uint16_t m;
	/* Calculate the gradient of the Sawtooth */
	// m = (uint16_t) ( 4096 / DACBUFFERSIZE);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	/* Create wave table for sinewave */


	// for (n = 0; n<DACBUFFERSIZE; n++)
	// {
	// 	SineWaveBuffer[n] = (uint16_t)((4095)/2.0)*( sin( M_TWOPI*n/DACBUFFERSIZE) + 1.0 );
	// }
	// for (n = 0; n<DACBUFFERSIZE; n++)
	// {
	// 	SawtoothBuffer[n] = (uint16_t)(m*n);
	// }
	// for (n = 0; n<DACBUFFERSIZE/2; n++)
	// {
	// 	PulseWaveTable[n] = 4095;
	// 	PulseWaveTable[DACBUFFERSIZE - n] = 0;
	// }
	// uint16_t result = 0;
	// m = 2*m-1;
	// for (n = 0; n<DACBUFFERSIZE/2; n++)
	// {
	// 	result = (uint16_t)m*n;
	// 	TriangleWaveTable[n] = result;
	// 	TriangleWaveTable[DACBUFFERSIZE - n-1] = result;
	// }


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

	// EXTILines_Config();
	EXTILine_Config(GPIO_Pin_1, EXTI_Line1, EXTI_PinSource1, EXTI1_IRQn);
	/* Infinite loop */
	while (1)
	{
		if(STM_EVAL_PBGetState(BUTTON_USER)== SET){
			buttonVal++;
			buttonVal %= numWaves;
			DMA_Cmd(DMA1_Stream5, DISABLE);	/* Disable the DMA */
			if(buttonVal== 0){
				DMA_Configuration ( SawtoothBuffer );
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
		if(0){//STM_EVAL_PBGetState(BUTTON_USER)== SET){//pitch_flag){//zero by default
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

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
void delay_ms(uint32_t milli)
{
	uint32_t delay = milli * 17612;              // approximate loops per ms at 168 MHz, Debug config
	for(; delay != 0; delay--);
}
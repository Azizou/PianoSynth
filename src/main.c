#include "stm32f4_discovery.h"
#include "led_io.h"
#include "main.h"

//http://tecsploit.com/stm32f4-discovery/stm32f4-discovery-using-gpio-to-control-an-external-led/

int main(void)
{
  EXTI_Line_Config();

  lcd_init();
  lcd_two_line_write("PianoSynth is","ready to shine");

  	uint32_t fTimer;
  	uint32_t timerFreq;
  	uint16_t timerPeriod;
  	uint16_t n;
  	uint16_t m;
  	m = (uint16_t) ( 4096 / DACBUFFERSIZE);
  	for (n = 0; n<DACBUFFERSIZE; n++)
  	{
  		SineWaveBuffer[n] = (uint16_t)((0xfff)/2.0)*( sin( M_TWOPI*n/DACBUFFERSIZE) + 1.0 );
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
  	fTimer = UpdateTimerFrequency();
  	timerFreq = TIMER_CLOCK / TIMER6_PRESCALER; /* Timer tick is in Hz */
  	timerPeriod = (uint16_t)( timerFreq / fTimer );
  	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	Timer_Configuration( timerPeriod, TIMER6_PRESCALER );
	DAC_Configuration();

	DMA_Configuration ( SineWaveBuffer );		// by default.
uint16_t * waveform = SineWaveBuffer;

  while (1)
  {
	  if(GPIO_ReadInputDataBit(TOGGLE_PORT0, TOGGLE_SWITCH0)){//set wave to sinewave
		  waveform = SineWaveBuffer;
	  }
	  if(GPIO_ReadInputDataBit(TOGGLE_PORT1, TOGGLE_SWITCH1)){//set wave to sinewave
		  waveform = SawtoothBuffer;
	  }
	  if(GPIO_ReadInputDataBit(TOGGLE_PORT2, TOGGLE_SWITCH2)){//set wave to sinewave
		  waveform = TriangleWaveTable;
	  }
	  if(GPIO_ReadInputDataBit(TOGGLE_PORT3, TOGGLE_SWITCH3)){//set wave to sinewave
		  waveform = PulseWaveTable;
	  }
	  else{
		  waveform = SineWaveBuffer;
	  }
	  DMA_Cmd(DMA1_Stream5, DISABLE);
	  DMA_Configuration(waveform);
  }
}



uint16_t UpdateTimerPeriod(uint16_t tickRate,uint16_t freqTimer){
	return (uint16_t)( tickRate / freqTimer );
}
uint32_t UpdateTimerFrequency(){
	return (uint32_t)getButtonFrequency(button_index)*DACBUFFERSIZE;
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

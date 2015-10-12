#include "stm32f4_discovery.h"
#include "led_io.h"
#include "main.h"

#define SINE_WAVE		0
#define PULSE_WAVE		1
#define TRIANGULAR_WAVE	2
#define SAWTOOTHWAVE	3

//http://tecsploit.com/stm32f4-discovery/stm32f4-discovery-using-gpio-to-control-an-external-led/

int main(void)
{
  EXTI_Line_Config();

  lcd_init();
  lcd_two_line_write((uint8_t *)"PianoSynth is",(uint8_t *)"ready to shine");
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
	UpdateTimerPeriod();
	//  	timerFreq = TIMER_CLOCK / TIMER6_PRESCALER; /* Timer tick is in Hz */
	//timerPeriod = (uint16_t)( TIMERFREQ / fTimer );
	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	Timer_Configuration();
	DAC_Configuration();

	DMA_Configuration ( SineWaveBuffer );		// by default.
	uint16_t  waveform = 0;

	while (1)
	{
	  if(GPIO_ReadInputDataBit(TOGGLE_PORT0, TOGGLE_SWITCH0)){//set wave to sinewave
		  waveform = SINE_WAVE;
		  setWave(waveform);
	  }
	  else if(GPIO_ReadInputDataBit(TOGGLE_PORT1, TOGGLE_SWITCH1)){//set wave to sinewave
		  waveform = TRIANGULAR_WAVE;
		  setWave(waveform);
	  }
	  else if(GPIO_ReadInputDataBit(TOGGLE_PORT2, TOGGLE_SWITCH2)){//set wave to sinewave
		  waveform = PULSE_WAVE;
		  setWave(waveform);
	  }
	  else if(GPIO_ReadInputDataBit(TOGGLE_PORT3, TOGGLE_SWITCH3)){//set wave to sinewave
		  waveform = SAWTOOTHWAVE;
		  setWave(waveform);
	  }
	  else{
		  waveform = SINE_WAVE;
		  setWave(waveform);
	  }
  }
}

void setWave(int waveform){
	 DMA_Cmd(DMA1_Stream5, DISABLE);
	switch(waveform){
	  case SINE_WAVE :
		  DMA_Configuration(SineWaveBuffer);
		  break;
	  case PULSE_WAVE :
		  DMA_Configuration(PulseWaveTable);
		  break;
	  case TRIANGULAR_WAVE:
		  DMA_Configuration(TriangleWaveTable);
		  break;
	  case SAWTOOTHWAVE:
			 DMA_Configuration(SawtoothBuffer);
			 break;
	  default:
		  DMA_Configuration(SineWaveBuffer);
	}
}



void UpdateTimerPeriod(){
	timerPeriod =  (uint16_t)( TIMERFREQ /(uint32_t)getButtonFrequency(button_index)*DACBUFFERSIZE);
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

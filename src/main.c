/**
 *    PianoSynth
 **** Main Source File ***
 */

#include "main.h"

/* Waveform generation variables */
uint32_t sampleCounter = 0;
uint8_t numButtonsPressed = 0;
uint32_t currentSample = 0;

/* LED variables */
uint8_t led_flag = 0;
uint8_t ledd_flag = 0;

/*****TESTING CODE ****/
#define SINE_WAVE   0
#define PULSE_WAVE    1
#define TRIANGULAR_WAVE 2
#define SAWTOOTHWAVE  3
/***** END TESTING ****/

/******* PROGRAM ENTRY POINT *********/
int main(void)
{
  SystemInit();

  /* Initialize the onboard LEDs */
  //STM_EVAL_LEDInit(LED4);
  //STM_EVAL_LEDInit(LED3);
  //STM_EVAL_LEDInit(LED5);
  //STM_EVAL_LEDInit(LED6);

  /* Initialize the offboard LEDs */
  /*LED_Init(LED00);
  LED_Init(LED01);
  LED_Init(LED02);
  LED_Init(LED03);
  LED_Init(LED04);
  LED_Init(LED05);
  LED_Init(LED06);
  LED_Init(LED07);
  LED_Init(LED08);
  LED_Init(LED09);*/

  

  /*** TESTING CODE ***/

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
  //    timerFreq = TIMER_CLOCK / TIMER6_PRESCALER; /* Timer tick is in Hz */
  //timerPeriod = (uint16_t)( TIMERFREQ / fTimer );
  uint16_t  waveform = 0;

  while (1)
  {
    if(GPIO_ReadInputDataBit(CUSTOMTOGGLE_PORT0, TOGGLE_SWITCH0)){//set wave to sinewave
      waveform = SINE_WAVE;
      setWave(waveform);
    }
    else if(GPIO_ReadInputDataBit(CUSTOMTOGGLE_PORT1, TOGGLE_SWITCH1)){//set wave to sinewave
      waveform = TRIANGULAR_WAVE;
      setWave(waveform);
    }
    else if(GPIO_ReadInputDataBit(CUSTOMTOGGLE_PORT2, TOGGLE_SWITCH2)){//set wave to sinewave
      waveform = PULSE_WAVE;
      setWave(waveform);
    }
    else if(GPIO_ReadInputDataBit(CUSTOMTOGGLE_PORT3, TOGGLE_SWITCH3)){//set wave to sinewave
      waveform = SAWTOOTHWAVE;
      setWave(waveform);
    }
    else{
      waveform = SINE_WAVE;
      setWave(waveform);
    }
  }
  /**** END TESTING CODE ****/

  /* Initialize the keys and potentiometers */
  GPIO_Configuration();
  /* Initialize the NVIC for the timer */
  NVIC_Configuration();
  /* Initialize the timer */
  Timer_Configuration();
  /* Initialize the DAC */
  DAC_Configuration();
  /* Initialize the DMA */
  DMA_Configuration(SineWaveBuffer);

  /* Initialize the LCD screen */
  lcd_init();
  lcd_two_line_write((uint8_t *)"PianoSynth is",(uint8_t *)"ready to shine");

}

/**
 * Main audio synthesizer timer
 * - Runs at 100kHz
 */
void TIM3_IRQHandler(void)
{
  /* Check if interrupt has occured */
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    /* Clear interrupt pending bit */
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

    /*** TESTING CODE ***/
    if(sampleCounter % 100000 == 0){
      //itoa(lcdLine2, (uint8_t)(sampleCounter / 100000), 10);
      //lcd_two_line_write(lcdLine1, lcdLine2);
    }
    /*** END TESTING CODE ***/

    /* Check which keys are pressed and build sample */
    currentSample = 0;
    numButtonsPressed = 0;  // For averaging the sample

    if(GPIO_ReadInputDataBit(BUTTON_PORT[0], BUTTON_PIN[0])){
    //    LEDOn(...);
    //    TODO: Add the sample for this frequency component
    //          -- Test the formula for an 880Hz sinusoid then repeat
    //          -- May be missing a factor of 2pi, but probably not
      currentSample += (uint16_t)(((0xFFF+1)/2) *
        (sin(sampleCounter* 2 *3.1415 
                          * getButtonFrequency(0) / TIMER_FREQUENCY) + 1));
      numButtonsPressed++;
    }
    //else LEDOff(...);

    // TODO: Repeat the above for every key

    sampleCounter++;
    
    /* Average the sample over the number of buttons pressed */
    if(numButtonsPressed > 0)
      currentSample /=  numButtonsPressed;

    /* Set DAC channel2 DHR12RD register */ 
    DAC_SetChannel2Data(DAC_Align_12b_R, currentSample);
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

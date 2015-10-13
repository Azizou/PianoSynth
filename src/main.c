/**
 *    PianoSynth
 **** Main Source File ***
 */

#include "main.h"

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
  LED_Init();

  /* Initialize the peripheral clocks */
  RCC_Configuration();
  /* Initialize the keys and potentiometers */
  GPIO_Configuration();
  /* Initialize the NVIC for the timer */
  NVIC_Configuration();
  /* Initialize the timer */
  Timer_Configuration();
  /* Initialize the DAC */
  DAC_Configuration();

  /* Initialize the LCD screen */
  lcd_init();
  lcd_two_line_write((uint8_t *)"PianoSynth is",(uint8_t *)"ready to shine");

  /* Loop ad infinitum */
  while(1);

}

/**
 * Main audio synthesizer carrier timer
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
    // if(sampleCounter % 100000 == 0){
    //   itoa(lcdLine2, (uint8_t)(sampleCounter / 100000), 10);
    //   lcd_two_line_write((uint_8t*)"Seconds:"), lcdLine2);
    // }
    /*** END TESTING CODE ***/

    /* Check which keys are pressed and build polyphonic sample */
    currentSample = 0;
    numButtonsPressed = 0;  // For averaging the sample

    /* Foreach button, check if pressed and add to wave */
    for(i = 0; i < 14; ++i){
      if(GPIO_ReadInputDataBit(BUTTON_PORT[i], BUTTON_PIN[i])){
      //    LEDOn(...);
        currentSample += (uint16_t)(((0xFFF+1)/2) *
          (sin(sampleCounter* 2 *3.1415 
                            * getButtonFrequency(i) / TIMER_FREQUENCY) + 1));
        numButtonsPressed++;
        itoa(lcdLine2, getButtonFrequency(i), 10);
        lcd_two_line_write((uint8_t *)"Frequency: ", lcdLine2);
      }
      //else LEDOff(...);
    }

    if(numButtonsPressed == 0){
      lcd_two_line_write((uint8_t *)"Idle mode",(uint8_t *)"waiting for event");
      TIM_Cmd(TIM6, DISABLE);
    }

    /* Average the sample over the number of buttons to normalize the volume */
    if(numButtonsPressed > 0)
      currentSample /=  numButtonsPressed;
    sampleCounter++;

    /* Set DAC channel2 DHR12RD output register */ 
    DAC_SetChannel2Data(DAC_Align_12b_R, currentSample);
  }

}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

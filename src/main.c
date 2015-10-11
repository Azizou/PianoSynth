#include "stm32f4_discovery.h"
#include "led_io.h"
#include "main.h"

//http://tecsploit.com/stm32f4-discovery/stm32f4-discovery-using-gpio-to-control-an-external-led/

uint8_t led_flag = 0;
uint8_t ledd_flag = 0;

int main(void)
{
  SystemInit();
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  EXTI_Line_Config();

  lcd_init();
  lcd_two_line_write("PianoSynth is","ready to shine");

  while (1)
  {
  }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

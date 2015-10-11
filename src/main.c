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
//  lcdLine1 = "Pianosythn!";
//
//  itoa(lcdLine2, 8800, 10);
//  lcd_two_line_write(lcdLine1, lcdLine2);

  uint8_t tog = 1;

  while (1)
  {
//    if (tog == 0)
//    {
////      itoa(lcdLine2, 880, 10);
////      lcd_two_line_write(lcdLine1, lcdLine2);
//      lcd_int_write("Kill your heros",880);
//    }
//    else
//    {
//      lcd_int_write("And you shall be heros: ",1000);
//    }

    tog = (++tog)%2;

    delay_ms(20);
  }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}

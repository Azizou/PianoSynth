#include <stdint.h>
#include "stm32f4xx.h"
#include "lcd.h"

int main(void);

extern void lcd_init (void);


int main(void) {
  //int i =0;
  lcd_init(); // set up LCD lines and send initialisation commands
  lcd_command(LCD_CLEAR_DISPLAY);
  lcd_string((unsigned char *)"   EEE3074W");
  lcd_command(LCD_GOTO_LINE_2); // go to lower line
  lcd_string((unsigned char *)"  LCD Testing");
  // set LEDs to outputs
  /*GPIOB->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | 
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);*/
  for(;;) {/*
    for(i=0; i < 65535; i++); // delay for a few hundred microseconds
    GPIOB->ODR += 1; // increment the patten on the LEDs*/
  }
  return 0;
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

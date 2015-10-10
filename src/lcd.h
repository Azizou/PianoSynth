#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "stm32f4xx.h" /* include peripheral declarations */

enum LcdCommand {
  LCD_CLEAR_DISPLAY = 0x01,
  LCD_CURSOR_HOME = 0x02,
  LCD_DISPLAY_ON = 0x0C,
  LCD_DISPLAY_OFF = 0x08,
  LCD_FOUR_BIT_TWO_LINE_MODE = 0x28,
  LCD_FOUR_BIT_MODE = 0x22,
  LCD_EIGHT_BIT_MODE = 0x33,
  LCD_GOTO_LINE_2 = 0xC0
};

void lcd_init(void);
void lcd_command (enum LcdCommand command);
void lcd_string(uint8_t *string_to_print);
void lcd_two_line_write(uint8_t* line1, uint8_t* line2);
void itoa(uint8_t buf[], unsigned int d, int base);

#endif

/*
Copyright (C) Samuel Ginsberg 2004
Porting to STM32F0 dev board by James Gowans, 2014
Porting to STM32F4 dev board by Yumin Park, 2015
LCD lines are as follows:
LCD_RS = PB4
LCD_E = PB5
LCD_D4 = PC6
LCD_D5 = PC7
LCD_D6 = PC8
LCD_D7 = PC9
*/

#include "lcd.h"

enum TypeOfCharacter {
  COMMAND = 0,
  TEXT = 1
};


static void delay (uint32_t microseconds);
static void pulse_strobe (void);
static void lcd_put (uint8_t character, enum TypeOfCharacter ch_type);
static void lcd_write4bits(uint8_t value);

//============================================================================

void lcd_string(uint8_t *string_to_print) {
	while(*string_to_print)
	{
		lcd_put(*string_to_print++,TEXT);
	}

}
void lcd_two_line_write(uint8_t* line1, uint8_t* line2) {
  lcd_command(LCD_CLEAR_DISPLAY);
  lcd_string(line1);
  lcd_command(LCD_GOTO_LINE_2);
  lcd_string(line2);
}
void lcd_int_write(uint8_t* message,int value, uint8_t unit[]){
	uint8_t line2[16];
	itoa2(line2,value,unit);
	lcd_two_line_write(message,line2);
}

void lcd_float_write(uint8_t* message,float value, uint8_t unit[]){
	uint8_t line2[16];
	ftoa(line2,value,unit);
	lcd_two_line_write(message,line2);
}

//void lcd_int_write(uint8_t* message,int value,uint8_t * unit){
//	uint8_t line2[16];
//	itoa(line2,value,10);
//	lcd_two_line_write(message,line2);
//}
//============================================================================

void lcd_init () {
  /*This function sets up the port lines for the LCD and initializes
  the LCD module for use.*/
  // set the relevant pins to outputs
  RCC->CFGR = RCC_CFGR_SW_HSE;
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN;
  RCC->CR |= RCC_CR_HSEON;

  GPIOC->MODER=GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;
  GPIOB->MODER=GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0;

  GPIOC->OSPEEDR = GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1 | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
  GPIOB->OSPEEDR = GPIO_OSPEEDER_OSPEEDR4_1 | GPIO_OSPEEDER_OSPEEDR5_1;

  delay(30000); //allow the LCD 30 ms power up time
  // in case in 2nd nibble of 4 bit tansfer, this goes to 1st nibble
  // if byte in 8-bit mode, keeps in 8-bit mode
  lcd_write4bits(0x03);
  delay(4100);
  lcd_write4bits(0x03);  // garanteed to be byte of 8-bit data for first byte of 4-bit.
  delay(39);
  lcd_write4bits(0x03); // necessary in case this is the 2nd nibble of 4-bit transfer.
  delay(39);
  // switch to 4-bit. This will latch in a byte as it's garanteed to now be in 8-bit
  lcd_write4bits(0x02);
  delay(39);
  lcd_command(LCD_FOUR_BIT_TWO_LINE_MODE); //0x28
  lcd_command(LCD_DISPLAY_OFF); // 0x08
  lcd_command(LCD_CLEAR_DISPLAY); // 0x01
  lcd_command(LCD_DISPLAY_ON); // 0x0C
}

//============================================================================

void lcd_command (enum LcdCommand command) {
  //This function sends a command to the LCD.
  //Care is taken not to interfere with the other lines on the port.
  lcd_put((uint8_t)command, COMMAND);
  delay(1530); // 1.53 ms is the maximum delay we should need for any command.
}

//============================================================================

static void lcd_put (uint8_t character, enum TypeOfCharacter ch_type) {
    //Puts a single character on the LCD at the next position on the screen.
    //The character to be printed is in the input parameter. For numbers, letters
    //and other common characters the ASCII code will produce correct display.
    //Refer to the Hitachi HD44780 datasheet for full character set information.
    if (ch_type == TEXT) {
        GPIOB->BSRRL |= GPIO_BSRR_BS_5;// pull RS (PB5) high
    } else if (ch_type == COMMAND) {
        GPIOB->BSRRH |= GPIO_BSRR_BS_5;// pull RS (PB5) low
    }
    // write upper nibble
    lcd_write4bits(character >> 4);
    // write lower nibble
    lcd_write4bits(character);
}
// This function outputs the lower 4 bits onto the data lines
static void lcd_write4bits(uint8_t character) {
  // lower nibble to data lines
  if ((character & 0x08) != 0) {
    GPIOC->BSRRL |= GPIO_BSRR_BS_9;
  } else {
    GPIOC->BSRRH |= GPIO_BSRR_BS_9;
  }
  if ((character & 0x04) != 0) {
    GPIOC->BSRRL |= GPIO_BSRR_BS_8;
  } else {
    GPIOC->BSRRH |= GPIO_BSRR_BS_8;
  }
  if ((character & 0x02) != 0) {
    GPIOC->BSRRL |= GPIO_BSRR_BS_7;
  } else {
    GPIOC->BSRRH |= GPIO_BSRR_BS_7;
  }
  if ((character & 0x01) != 0) {
    GPIOC->BSRRL |= GPIO_BSRR_BS_6;
  } else {
    GPIOC->BSRRH |= GPIO_BSRR_BS_6;
  }
  pulse_strobe ();
}

//============================================================================


static void delay(uint32_t microseconds) {
  /* Hangs for specified number of microseconds. */
  volatile uint32_t counter = 0;
  microseconds *= 3;
  for(; counter<microseconds; counter++) {
    __asm("nop");
    __asm("nop");
  }
}

static void pulse_strobe (void) {
  //Pulse the strobe line of the LCD to indicate that data is ready.
  delay(1);
  GPIOB->BSRRL |= GPIO_BSRR_BS_4;// pull E (PB4) high
  delay(1);
  GPIOB->BSRRH |= GPIO_BSRR_BS_4;// pull E (PB4) low
  delay(1);
}

void itoa(uint8_t buf[], unsigned int d, int base)
{
  int div = 1;
  while (d/div >= base)
    div *= base;

  int i = 0;
  while (div != 0)
  {
    int num = d/div;
    d = d%div;
    div /= base;
    buf[i++] = num + '0';
  }
  buf[i] = '\0';
}

void itoa2(uint8_t buf[], unsigned int d, uint8_t unit[])
{
  int div = 1;
  int base = 10;
  while (d/div >= base)
    div *= base;

  int i = 0;
  while (div != 0)
  {
    int num = d/div;
    d = d%div;
    div /= base;
    buf[i++] = num + '0';
  }
  //buf[i++] = ' ';
  int j = 0;
  for(;j<sizeof(unit); j++)
  {
	  buf[i+j] = unit[j];
  }
  buf[i+j] = '\0';
}

void ftoa(uint8_t buf[], float f, uint8_t unit[])
{
  int div = 1;
  int base = 10;
  int d = (int)f;
  while (d/div >= base)
    div *= base;

  int i = 0;
  while (div != 0)
  {
    int num = d/div;
    d = d%div;
    div /= base;
    buf[i++] = num + '0';
  }
  buf[i++] = '.';

  // decimal part.
  float d2 = f - (int)f;
  while(1)
  {
	  d2 *= base;
	  int num = (int)d2;
	  buf[i++] = num + '0';
	  if (num == (int)d2) {break;}
	  d2 -= num;
  }

  int j = 0;
  for(;j<sizeof(unit); j++)
  {
	  buf[i+j] = unit[j];
  }
  buf[i+j] = '\0';
}

//============================================================================

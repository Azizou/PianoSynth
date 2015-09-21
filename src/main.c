/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed 밶s is,�without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/


/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private function prototypes -----------------------------------------------*/
void WaitLCDBusy(void);
void LCD_Init(void);
void LCD_DATA(unsigned char data,unsigned char type);
void LCD_NYB(unsigned char nyb,unsigned char type);
void LCD_LINE(char line);
void ShiftDisplay(unsigned char DC,unsigned char RL);
void DelayMS(unsigned int ms);
void LCD_STR(unsigned char *text);
void LCD_CLEAR(unsigned char line);
void initDiscovery(void);


void LCD_Init (void)
{
	/*GPIOD -> MODER = 0x5055;	//Set the mode to output for PD0, PD3, PD6, PD7
	GPIOD -> OTYPER = 0x00;		//Set the TYPE to Push-Pull for all
	GPIOD -> OSPEEDR = 0xA0AA;	//50 MHz Speed on the LCD Port
	GPIOD -> PUPDR = 0x00;		//Pull-up/Pull-down disabled

	GPIOD->BSRRH |= (1<<6);		//clear enable
	GPIOD->BSRRH |= (1<<7);		//going to write command*/

	GPIOA -> ODR &= ~(0x100);
	GPIOA -> ODR &= ~(0x200);

	DelayMS (30);				//delay for lcd to initialise
	LCD_NYB (0x30, 0);			//required for initialisation
	DelayMS (5);				//required delay
	LCD_NYB (0x30, 0);			//required for initialisation
	DelayMS (1);				//required delay
	LCD_DATA (0x02, 0);			//set to 4 bit interface, 1 line and 5*7 font
	LCD_DATA (0x28, 0);			//set to 4 bit interface, 2 line and 5*10 font
	LCD_DATA (0x0c, 0);			//set to 4 bit interface, 2 line and 5*7 font
	LCD_DATA (0x01, 0);			//clear display
	LCD_DATA (0x06, 0);			//move cursor right after write
}


void LCD_DATA (unsigned char data, unsigned char type)
{
	WaitLCDBusy ();

	if (type == 0)
		/*GPIOD -> BSRRH |= (1<<7);		//command mode*/
		GPIOA -> ODR &= ~(0x200);
	else
		/*GPIOD -> BSRRL |= (1<<7);	//character/data mode*/
		GPIOA -> ODR |= 0x200;

	LCD_NYB (data>>4, type);		//write the upper nibble
	LCD_NYB (data, type);			//write the lower nibble
}


void WaitLCDBusy (void)
{
	DelayMS (2);
}


void LCD_NYB (unsigned char nyb, unsigned char type)
{
	/*GPIOD -> BSRRH |= 0x0F;
	GPIOD -> BSRRL |= (nyb & 0x0F);*/

	GPIOC -> ODR &= 0xFFFFFC3F;
	GPIOC -> ODR |= (nyb<<6);
	GPIOA -> ODR &= 0xF0;
	GPIOA -> ODR |= (nyb & 0x0F);

	if (type == 0)
		/*GPIOD->BSRRH |= (1<<7);		//command mode*/
		GPIOA -> ODR &= !(0x200);
	else
		/*GPIOD -> BSRRL |= (1<<7);	//character/data mode*/
		GPIOA -> ODR |= 0x200;

	/*GPIOD -> BSRRL |= (1<<6);		//Enable LCD data line*/
	GPIOA -> ODR |= 0x100;
	DelayMS (1);					//Small delay
	/*GPIOD -> BSRRH |= (1<<7);		//Disable LCD data line*/
	GPIOA -> ODR &= ~(0x100);
}


void LCD_STR(unsigned char *text)
{
    while(*text)
	{
        LCD_DATA(*text++,1);
    }
}
//--------------------------------------------------------------------------------//
void LCD_LINE(char line)
{
    switch(line)
    {
        case 0:
        case 1:
            LCD_DATA(0x80,0);
            break;
        case 2:
            LCD_DATA(0xC0,0);
            break;
    }
}
//--------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------//
void DelayMS(unsigned int ms)
{
    unsigned int x, i;
    for(x = 0; x < ms; x++)
    {
        for(i = 0; i < 600; i++);
    }
}
//--------------------------------------------------------------------------------//
/*void LCD_POS(unsigned char line)
{
	unsigned char myDat;
	unsigned char pos = 18;

    LCD_LINE(line);
    switch(line){
        case 0:
        case 1:
            myDat = 0x80 + pos;
            break;
        case 2:
            myDat = 0xC0 + pos;
            break;
    }

    myDat |= 0x80;
    LCD_DATA(myDat,0);
}*/

void initDiscovery(void)
{
  RCC->CFGR = RCC_CFGR_SW_HSE;
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN;
  RCC->CR |= RCC_CR_HSEON;

  while((RCC->CR & RCC_CR_HSERDY)==0);

  GPIOC->MODER=GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;
  GPIOA->MODER=GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;

  GPIOC->OSPEEDR = GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1 | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
  GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
}

int main(void)
{
  //int temp;

  /*RCC->AHB1ENR = 0xFF; //All GPIO Clock Enabled*/
  initDiscovery();

  LCD_Init();
  DelayMS (3);

  LCD_LINE (1);
  LCD_STR ((unsigned char*)"   Yumin Park   ");
  DelayMS (100);

  LCD_LINE (2);
  LCD_STR ((unsigned char*)"    EEE3074W    ");
  DelayMS (100);

  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /* TODO - Add your application code here */



  /* Infinite loop */
  while (1)
  {
  }
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

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
/**
  ******************************************************************************
  * @file    EXTI/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "lcd.h"
#include "pitch.h"

extern int pitch_index;
//extern float pitch_table;
//extern  float pitch_table[7][7][7];
int debounce_delay = 1;
extern int button_index;
void delay_ms(uint32_t milli)
{
  uint32_t delay = milli * 17612;              // approximate loops per ms at 168 MHz, Debug config
  for(; delay != 0; delay--);
}

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */

//void setMode(int buttonId){
//	mode += buttonId/7;
//}
void default_exti_handler(uint32_t line, char * message, uint8_t buttonID){
  if(EXTI_GetITStatus(line) != RESET)
  {
	/* Toggle LED4 */
	  button_index = buttonID;
//	STM_EVAL_LEDToggle(LED3);
	lcd_float_write((uint8_t *)message, getButtonFrequency(buttonID), (uint8_t *)"Hz");
	delay_ms(debounce_delay);
	EXTI_ClearITPendingBit(line);
  }
}


void EXTI0_IRQHandler(void)
{
	default_exti_handler(EXTI_Line0,"Note frequency:",0);
}

void EXTI1_IRQHandler(void)
{
	default_exti_handler(EXTI_Line1,"Note frequency:",1);
}
void EXTI2_IRQHandler(void)
{
	default_exti_handler(EXTI_Line2,"Note frequency:",2);
}
void EXTI3_IRQHandler(void)
{
	default_exti_handler(EXTI_Line3,"Note frequency:",3);
}
void EXTI4_IRQHandler(void)
{
	default_exti_handler(EXTI_Line4,"Note frequency:",4);
}
void EXTI9_5_IRQHandler(void){
	default_exti_handler(EXTI_Line5,"Note frequency:",5);
	default_exti_handler(EXTI_Line6,"Note frequency:",6);
	default_exti_handler(EXTI_Line7,"Note frequency:",7);
	default_exti_handler(EXTI_Line8,"Note frequency:",8);
	default_exti_handler(EXTI_Line9,"Note frequency:",9);
}

void EXTI15_10_IRQHandler(void){
	default_exti_handler(EXTI_Line10,"Note frequency:",10);
	default_exti_handler(EXTI_Line11,"Note frequency:",11);
	default_exti_handler(EXTI_Line12,"Note frequency:",12);
	default_exti_handler(EXTI_Line13,"Note frequency:",13);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

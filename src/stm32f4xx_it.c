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

extern int pitch_index;
//extern float pitch_table;
extern const float pitch_table[];
int debounce_delay = 1;

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
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Toggle LED4 */
    STM_EVAL_LEDToggle(LED3);
    pitch_index = 7;
    lcd_float_write("B0 note played", pitch_table[pitch_index], "Hz");
     delay_ms(debounce_delay);
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    /* Toggle LED4 */
    STM_EVAL_LEDToggle(LED4);
    pitch_index = 8;
    lcd_float_write("B1 note played", pitch_table[pitch_index], "Hz");
    delay_ms(debounce_delay);
//  GPIO_SetBits(GPIOA, GPIO_Pin_3);

    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    /* Toggle LED4 */
    STM_EVAL_LEDToggle(LED5);
    pitch_index = 9;
    lcd_float_write("B2 note played", pitch_table[pitch_index], "Hz");
//    GPIO_ResetBits(GPIOA, GPIO_Pin_3);

    delay_ms(debounce_delay);
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    /* Toggle LED4 */

    STM_EVAL_LEDToggle(LED6);
    delay_ms(debounce_delay);
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
  else{
	  STM_EVAL_LEDToggle(LED6);
  }
}
void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    /* Toggle LED4 */

    STM_EVAL_LEDToggle(LED3);
    delay_ms(debounce_delay);
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
}
void EXTI9_5_IRQHandler(void){
	 if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
	/* Toggle LED4 */

		STM_EVAL_LEDToggle(LED4);
		delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line5);
	}

	 else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED5);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line6);
	}
	 if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED6);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line7);
	}

	 if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED3);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line8);
	}

	 if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED4);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line9);
	}

	 if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED4);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void EXTI15_10_IRQHandler(void){
	 if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
	/* Toggle LED4 */

		STM_EVAL_LEDToggle(LED4);
		delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line5);
	}

	 else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED5);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line6);
	}
	 if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED6);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line7);
	}

	 if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED3);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line8);
	}

	 if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
	/* Toggle LED4 */

	STM_EVAL_LEDToggle(LED4);
	delay_ms(debounce_delay);
	/* Clear the EXTI line 0 pending bit */
	EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

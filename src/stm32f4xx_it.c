/**
*****************************************************************************
**
**  File        : stm32f4xx_it.c
**
**  Abstract    : Main Interrupt Service Routines.
**                This file provides template for all exceptions handler and
**                peripherals interrupt service routine.
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern uint16_t volume;
extern uint16_t pitch_index;
extern uint16_t buttonVal;
extern uint32_t numWaves;

extern float pitch;
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






void extiAction(uint32_t extiline, uint16_t gpiopin){
	if(EXTI_GetITStatus(extiline) != RESET)
	{
		pitch_index++;
		pitch_index %= 88;

		buttonVal++;
		buttonVal %= numWaves;
		STM_EVAL_LEDToggle(LED4);
		EXTI_ClearITPendingBit(extiline);
	}
	else{
		//		    GPIO_ResetBits(GPIOB,gpiopin);
	}
}
void EXTI0_IRQHandler(void){
	extiAction(EXTI_Line0,GPIO_Pin_0);
}
void EXTI1_IRQHandler(void){
	extiAction(EXTI_Line1,GPIO_Pin_1);
}
void EXTI2_IRQHandler(void){
	extiAction(EXTI_Line2,GPIO_Pin_2);
}
void EXTI3_IRQHandler(void){
	extiAction(EXTI_Line3,GPIO_Pin_3);
}
void EXTI4_IRQHandler(void){
	extiAction(EXTI_Line4,GPIO_Pin_4);
}
void EXTI9_5_IRQHandler(void){
	extiAction(EXTI_Line5,GPIO_Pin_5);
	extiAction(EXTI_Line6,GPIO_Pin_6);
	extiAction(EXTI_Line7,GPIO_Pin_7);
	extiAction(EXTI_Line8,GPIO_Pin_8);
	extiAction(EXTI_Line9,GPIO_Pin_9);
}
void EXTI15_10_IRQHandler(void){
	extiAction(EXTI_Line10,GPIO_Pin_10);
	extiAction(EXTI_Line11,GPIO_Pin_11);
	extiAction(EXTI_Line12,GPIO_Pin_12);
	extiAction(EXTI_Line13,GPIO_Pin_13);
	//handle volume button
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		/* Toggle LED4 */

		volume++;
		if(volume>100)
			volume = 100;
		STM_EVAL_LEDToggle(LED4);//Try to trigger on rising and falling edges.
		//set the frequency offset here
		//		    GPIO_SetBits(GPIOB,gpiopin);

		/* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	else
		EXTI_ClearITPendingBit(EXTI_Line14);

	if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
		volume--;
		if(volume>100)
			volume = 0;
		STM_EVAL_LEDToggle(LED4);//Try to trigger on rising and falling edges.
		//		    GPIO_SetBits(GPIOB,gpiopin);
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	else
		EXTI_ClearITPendingBit(EXTI_Line15);
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


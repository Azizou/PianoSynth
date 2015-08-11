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
**  Distribution: The file is distributed as is, without any warranty
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

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private macro */
#define GREENLED LED4
/* Private variables */
/* Private function prototypes */
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Timer_Configuration(void);
void NVIC_Configuration(void);
uint32_t counter=1;//the new pulse value
uint32_t flag=1;//to determine if you count up or down
/*******************************************************************************
* TIM2_IRQHandler
* @brief    This function handles TIM2 global interrupt request.
* @param    None
* @retval   None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
      /* Check if interrupt has occured */
      if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
      {
            /* Clear interrupt pending bit */
            TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

            /* WHAT EVER YOU NEED TO DO IN THE INTERRUPT HANDLER GOES HERE */
            GPIO_ToggleBits(GPIOD, GPIO_Pin_15);//toggle the light every second
      }

}

/*******************************************************************************
* TIM3_IRQHandler
* @brief    This function handles TIM3 global interrupt request.
* @param    None
* @retval   None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
      /* Check if interrupt has occured */
      if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
      {
            /* Clear interrupt pending bit */
            TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

            /* WHAT EVER YOU NEED TO DO IN THE INTERRUPT HANDLER GOES HERE */
            if(flag==1)//count up
            {
                  counter=counter+1;
                  if(counter>998)
                  {
                        counter=999;
                        flag=0;//toggle the flag to make it start counting down
                  }
            }
            else if(flag==0)//count down
            {
                  counter=counter-1;
                  if(counter<1)
                  {
                        counter=0;
                        flag=1;//toggle the flag to make it start counting up
                  }
            }
            TIM_SetCompare2(TIM4,counter);//change the PWM pulse to the new counter value
      }

}

/**
  * @brief  Main program.
  * @param  None
  * @retval Int
  */
int main(void)
{

      /* System Clocks Configuration */
      RCC_Configuration();

      /* NVIC configuration */
      NVIC_Configuration();

      /* Configure the GPIO ports */
      GPIO_Configuration();

      /* Timer Configuration */
      Timer_Configuration();

      /* Forever loop */
      for (;;)
      {
            /* DOES NOTHING HERE */
      }

      /* Program will never get here... */
      return 0;
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{

      /* TIM2, TIM4, TIM3 clock */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM3 , ENABLE);

      /* LEDs are on GPIOD */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

}

/**
  * @brief  Configures the Nested Vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
      NVIC_InitTypeDef NVIC_InitStructure;

      /* Enable the TIM2 global Interrupt */
      NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//set up the interrupt handler for TIM2
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

      NVIC_Init(&NVIC_InitStructure);

      /* Enable the TIM3 global Interrupt */
      NVIC_InitTypeDef NVIC_InitStructure2;
      NVIC_InitStructure2.NVIC_IRQChannel = TIM3_IRQn;//set up the interrupt handler for TIM3
      NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0;
      NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;
      NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;

      NVIC_Init(&NVIC_InitStructure2);
}


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;

      /* Put your GPIO initialisation here (Hint use 'GPIO_Init function) */
      /* Configure the GPIO_LED pin */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//set up the LED
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

      GPIO_Init(GPIOD, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//set up the orange LED
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//AF=alternating function=PWM
      GPIO_Init(GPIOD, &GPIO_InitStructure);

      GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);//link the AF pin to the timer

//    GPIO_SetBits(GPIOD, GPIO_Pin_12);
}


/**
  * @brief  Configures the Timers
  * @param  None
  * @retval None
  */
void Timer_Configuration(void)
{
      TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
      TIM_OCInitTypeDef TIM_OCInitStruct;

      /* Put your timer initialisation here */
      TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

      TIM_TimeBaseInitStruct.TIM_Period = 10000-1;//TIM2 has a frequency of 1Hz
      TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;
      TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
      TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

      TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

      /* TIM interrupt enable */
      TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

      /* TIM2 enable counter */
      TIM_Cmd(TIM2, ENABLE);
      /*timer 3 setup*/
      TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

      TIM_TimeBaseInitStruct.TIM_Period = 10-1;//TIM3 has a frequency of 1000Hz
      TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;
      TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
      TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

      TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

      /* TIM interrupt enable */
      TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

      /* TIM3 enable counter */
      TIM_Cmd(TIM3, ENABLE);
      /* PWM Timer setup */
      /* Time base configuration */
      TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//TIM4 has a frequency of 1000Hz
      TIM_TimeBaseInitStruct.TIM_Prescaler = 84-1;
      TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
      TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

      /* PWM1 Mode configuration: Channel2 */
      TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStruct.TIM_Pulse = 100;   /* 10% Duty Cycle as the period counts up to 1000*/
      TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

      /* This is needed for initilization of PWM */
      TIM_OC2Init(TIM4, &TIM_OCInitStruct);
      TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
      TIM_ARRPreloadConfig(TIM4, ENABLE);

      /* TIM4 enable counter */
      TIM_Cmd(TIM4, ENABLE);

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
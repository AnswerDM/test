/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
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
#include "stm32f10x_it.h"
#include "pid.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
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
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
u8 hallState_Far = 0;
u8 lastState_Far = 0;

u8 hallState_Near = 0;
u8 lastState_Near = 0;

s32 speedCounter_Far = 0;
s32 speedCounter_Near = 0;

const s16 MOTOR_HALL_SPEED_TABLE[7][7] = 
{
	{0,0,0,0,0,0,0},
	{0,0,0,-1,0,1,0},
	{0,0,0,1,0,0,-1},
	{0,1,-1,0,0,0,0},
	{0,0,0,0,0,-1,1},
	{0,-1,0,0,1,0,0},
	{0,0,1,0,-1,0,0},
};

s16 MORTOR_calculateHallSpeedInc(int state, int lastState)
{
	return MOTOR_HALL_SPEED_TABLE[state][lastState];
}

void EXTI9_5_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearFlag(EXTI_Line5);
	}
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_ClearFlag(EXTI_Line6);
	}
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_ClearFlag(EXTI_Line7);
	}
	//求取电角度
	hallState_Far = (GPIOB->IDR >> 5) & 7;
	//electricalAngleNear =  MORTOR_getElectricalAngleFromState(motorData.hallStateNear);
	
  //用于计算速度
	speedCounter_Far -= MORTOR_calculateHallSpeedInc(hallState_Far,lastState_Far);
  lastState_Far = hallState_Far;
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		EXTI_ClearFlag(EXTI_Line10);
	}
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
		EXTI_ClearFlag(EXTI_Line11);
	}
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
		EXTI_ClearFlag(EXTI_Line12);
	}
	//求取电角度
	hallState_Near = (GPIOC->IDR >> 10) & 7;
	//electricalAngleNear =  MORTOR_getElectricalAngleFromState(motorData.hallStateNear);
	
  //用于计算速度
	speedCounter_Near -= MORTOR_calculateHallSpeedInc(hallState_Near,lastState_Near);
  lastState_Near = hallState_Near;
}

int motor_speed_near_set = 0; //速度设定值
int motor_speed_far_set = 0;  //速度设定值
int motor_speed_near = 0;     //采集到的实际速度值
int motor_speed_far = 0;      //采集到的实际速度值
int motor_speed_near_val = 0; //PID计算出电机值
int motor_speed_far_val = 0;  //PID计算出电机值

u16 tim3Counter2;
void TIM3_IRQHandler(void)//5ms
{
  
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    
		tim3Counter2++;
    if(tim3Counter2 >= 60)//300ms
    {
      tim3Counter2 = 0;
			motor_speed_near = speedCounter_Near;
			motor_speed_far  = speedCounter_Far;
			speedCounter_Near = 0;
      speedCounter_Far = 0;

			sPID_Near.vi_FeedBack = motor_speed_near;
			sPID_Far.vi_FeedBack  = motor_speed_far;
    }
	}
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

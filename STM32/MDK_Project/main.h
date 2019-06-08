#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>
#include "rtc.h" 
#include "SPI.H"
#include "sys.h"
#include "uip.h"
#include "enc28j60.h"
#include "uip_arp.h"
#include "simple_server.h"
#include "tapdev.h"
#include "usart.h"
#include "GPIO_Init.h"
#include "74hc595.h"
#include "timer.h"
#include "math.h"
#include "profibus.h"
#include "timerx.h"


/*----------------------------------------------------------*\
 |从站使能拨码开关定义                                          |
\*----------------------------------------------------------*/
#define EN_1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)
#define EN_2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define EN_3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define EN_4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define EN_5 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)
#define EN_6 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7)
#define EN_7 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)
#define EN_8 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5)
#define EN_9 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)
#define EN_10 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3)
#define EN_11 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)
#define EN_12 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)
#define EN_13 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define EN_14 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)
#define EN_15 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)
#define EN_16 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)
#define EN_17 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)
#define EN_18 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)
#define EN_19 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)
#define EN_20 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)

/*----------------------------------------------------------*\


\*----------------------------------------------------------*\
 |     DP从站选择拨码开关                                          |
\*----------------------------------------------------------*/


#define DP_UNIT1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)   //8
#define DP_UNIT2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)   //4
#define DP_UNIT3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)   //2
#define DP_UNIT4 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)  //1
#define DP_TEN1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)    //8
#define DP_TEN2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)    //4
#define DP_TEN3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)    //2
#define DP_TEN4 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)    //1

#define DP_UNIT_1 ((DP_UNIT1 & 0X01)<<3)
#define DP_UNIT_2 ((DP_UNIT2 & 0X01)<<2)
#define DP_UNIT_3 ((DP_UNIT3 & 0X01)<<1)
#define DP_UNIT_4 ((DP_UNIT4 & 0X01))
#define DP_UNIT_TEM ~(DP_UNIT_1+DP_UNIT_2+DP_UNIT_3+DP_UNIT_4)
#define DP_UNIT (DP_UNIT_TEM & 0X0f)

#define DP_TEN_1 ((DP_TEN1 & 0X01)<<3)
#define DP_TEN_2 ((DP_TEN2 & 0X01)<<2)
#define DP_TEN_3 ((DP_TEN3 & 0X01)<<1)
#define DP_TEN_4 ((DP_TEN4 & 0X01))
#define DP_TEN_TEM ~(DP_TEN_1+DP_TEN_2+DP_TEN_3+DP_TEN_4)
#define DP_TEN (DP_TEN_TEM & 0x0f)

#define DP_NUM (DP_UNIT+DP_TEN*10)

/*----------------------------------------------------------*\

\*----------------------------------------------------------*\
 |     通信信道选择拨码开关                                          |
\*----------------------------------------------------------*/
#define CH_UNIT1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)   //8
#define CH_UNIT2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)   //4
#define CH_UNIT3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)   //2
#define CH_UNIT4 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)   //1
#define CH_TEN1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)    //8
#define CH_TEN2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)    //4
#define CH_TEN3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)   //2
#define CH_TEN4 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)    //1


#define CH_UNIT_1 ((CH_UNIT1 & 0X01)<<3)
#define CH_UNIT_2 ((CH_UNIT2 & 0X01)<<2)
#define CH_UNIT_3 ((CH_UNIT3 & 0X01)<<1)
#define CH_UNIT_4 ((CH_UNIT4 & 0X01))
#define CH_UNIT_TEM ~(CH_UNIT_1+CH_UNIT_2+CH_UNIT_3+CH_UNIT_4)
#define CH_UNIT (CH_UNIT_TEM & 0X0f)

#define CH_TEN_1 ((CH_TEN1 & 0X01)<<3)
#define CH_TEN_2 ((CH_TEN2 & 0X01)<<2)
#define CH_TEN_3 ((CH_TEN3 & 0X01)<<1)
#define CH_TEN_4 ((CH_TEN4 & 0X01))
#define CH_TEN_TEM ~(CH_TEN_1+CH_TEN_2+CH_TEN_3+CH_TEN_4)
#define CH_TEN (CH_TEN_TEM & 0x0f)

#define CH_NUM (CH_UNIT+CH_TEN*10)


#define LED_ON GPIO_ResetBits(GPIOA,GPIO_Pin_2);
#define LED_OFF GPIO_SetBits(GPIOA,GPIO_Pin_2);











#endif
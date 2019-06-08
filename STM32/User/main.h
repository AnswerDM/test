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
#include "stm32f10x_it.h"
#include "timerx.h"
#include "zigbee.h"
#include "parser.h"
#include "function.h"
#include "wdg.h"



#define LED_ON GPIO_ResetBits(GPIOA,GPIO_Pin_1);
#define LED_OFF GPIO_SetBits(GPIOA,GPIO_Pin_1);


#define LED_ODD_RED      0xEF 
#define LED_ODD_GREEN    0xF7 
#define LED_ODD_BLUE     0xFB 
#define LED_EVEN_RED     0x7F 
#define LED_EVEN_GREEN   0xBF 
#define LED_EVEN_BLUE    0xDF 
#define LED_ODD_OFF      0xFF
#define LED_EVEN_OFF     0xFF







#endif



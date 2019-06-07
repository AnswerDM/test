#ifndef _LED_H_
#define _LED_H_

#include <MAIN.h>

#define LED_TIM							TIM2
#define LED_RCC 						RCC_APB1Periph_TIM2
#define LED_TIM_IRQn 				TIM2_IRQn
#define LED_TIM_IRQHandler	TIM2_IRQHandler

extern void LED_Init(void);
extern void LED_SET_STATE(unsigned char LED_Num,unsigned char IsLight);
extern void Beep(void);
extern void StartBeep(void);
extern void StopBeep(void);
extern void LED_TIM_init(u16 arr,u16 psc);

#endif

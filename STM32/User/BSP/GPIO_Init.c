#include "GPIO_Init.h"


extern void HC595G_WriteByte(uint32_t byte,uint8_t Enable);


void gpio_init(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure;
  

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG,ENABLE);
	
	
	/**********LED GPIO************/
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	

	

		/**********74HC595_1 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//PE5->S_CLK PE4->L_CLK PE3->DATA
  HC595G_WriteByte(0xff,0);
	
			/**********74HC595_2 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//PE2->S_CLK PE1->L_CLK PE0->DATA
  HC595G_WriteByte(0xff,2);
	
//			/**********74HC595_3 GPIO************/
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//PB8->S_CLK PB9->L_CLK 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//PA15->DATA
	HC595G_WriteByte(0xff,4);
	
			/**********74HC595_4 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//PB7->S_CLK PB6->L_CLK PB5->DATA
  HC595G_WriteByte(0xff,6);
	
			/**********74HC595_5 GPIO************/
			
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//PB4->S_CLK PB3->L_CLK PG15->DATA
  HC595G_WriteByte(0xff,8);
			/**********74HC595_6 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//PG14->S_CLK PG13->L_CLK PG12->DATA
  HC595G_WriteByte(0xff,10);
			/**********74HC595_7 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);//PG11->S_CLK PG10->L_CLK PG9->DATA
  HC595G_WriteByte(0xff,12);
			/**********74HC595_8 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);//PD7->S_CLK PD6->L_CLK PD5->DATA
  HC595G_WriteByte(0xff,14);
			/**********74HC595_9 GPIO************/
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);//PD4->S_CLK PD3->L_CLK PD2->DATA
  HC595G_WriteByte(0xff,16);
				/**********74HC595_9 GPIO************/
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);//PD1->S_CLK PD0->L_CLK PC12->DATA
  HC595G_WriteByte(0xff,18);
	
	
	      /****************ZigBee¸´Î»IO********/
				
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_8);

	

	
	
}

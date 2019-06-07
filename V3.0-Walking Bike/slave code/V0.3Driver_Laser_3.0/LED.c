#include <LED.h>

u8 IsLighted = 0;

void LED_Init(void)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	
	//PC13 -- State_LED
	//RRC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIO
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;			
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&mGPIO_InitStructure);
  //RRC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//如果不复用端口，可取消
	//GPIO
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;			
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&mGPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//复用jtdo端口 同时关闭SWD端口
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
}

void LED_TIM_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  if(IS_RCC_APB1_PERIPH(LED_RCC))
		RCC_APB1PeriphClockCmd(LED_RCC, ENABLE); //RCC
	else
		RCC_APB2PeriphClockCmd(LED_RCC, ENABLE); //RCC
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(LED_TIM, &TIM_TimeBaseStructure);

	TIM_ITConfig(LED_TIM,TIM_IT_Update,ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel = LED_TIM_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(LED_TIM, ENABLE);
}

void LED_TIM_IRQHandler(void)
{
	if (TIM_GetITStatus(LED_TIM, TIM_IT_Update) != RESET)
		{
		TIM_ClearITPendingBit(LED_TIM, TIM_IT_Update );
		if(IsLighted)
		  LED_SET_STATE(1,0);
		else
			LED_SET_STATE(1,1);
		}
} 

void LED_SET_STATE(unsigned char LED_Num,unsigned char IsLight)
{
	switch(LED_Num)
	{
		case 1:
			if(IsLight == 0)
			{
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
			  IsLighted = 0;
			}
			else 
			{
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
				IsLighted = 1;
			}
		  break;
		default:
			break;
	}
}

void Beep(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET);
	Delay_Ms(1000);
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
}

void StartBeep(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET);
}

void StopBeep(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
}

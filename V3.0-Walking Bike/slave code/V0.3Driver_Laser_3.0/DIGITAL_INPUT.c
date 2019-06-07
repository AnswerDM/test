#include <DIGITAL_INPUT.h>

#define HC165_Q7_Pin	GPIO_Pin_4
#define HC165_CP_Pin	GPIO_Pin_5
#define HC165_CE_Pin	GPIO_Pin_6
#define HC165_PL_Pin	GPIO_Pin_7

#define HC595_Q7_IsHigh	GPIO_ReadInputDataBit(GPIOB,HC165_Q7_Pin)

#define Hc165_CP_HIGH		GPIO_WriteBit(GPIOB,HC165_CP_Pin,Bit_SET)
#define Hc165_CP_LOW		GPIO_WriteBit(GPIOB,HC165_CP_Pin,Bit_RESET)

#define Hc165_CE_HIGH		GPIO_WriteBit(GPIOB,HC165_CE_Pin,Bit_SET)
#define Hc165_CE_LOW		GPIO_WriteBit(GPIOB,HC165_CE_Pin,Bit_RESET)

#define Hc165_PL_HIGH		GPIO_WriteBit(GPIOB,HC165_PL_Pin,Bit_SET)
#define Hc165_PL_LOW		GPIO_WriteBit(GPIOB,HC165_PL_Pin,Bit_RESET)

void DIGITAL_INPUT_Init(void)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	//HC165 Q7		PB4
	//HC165 CP		PB5
	//HC165 CE		PB6
	//HC165 PL		PB7
	
	//RRC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//如果不复用端口，可取消
	//GPIO
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;			
	GPIO_Init(GPIOB,&mGPIO_InitStructure);
	
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;			
	GPIO_Init(GPIOB,&mGPIO_InitStructure);
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable | GPIO_Remap_SWJ_NoJTRST,ENABLE);		//复用JNTRST端口 同时关闭SWD端口
}
//一次读取1个165的数据
unsigned char DIGITAL_READ(unsigned char IcNum)
{
	unsigned char DIGITAL_IO_STATE = 0;
	unsigned char i = 0;
	Hc165_CE_LOW;
	Hc165_PL_LOW;
	Hc165_PL_HIGH;
	Hc165_CP_LOW;
	Delay_Us(10);
	for (i=0;i<8*IcNum;i++)
	{
		DIGITAL_IO_STATE <<= 1;
		if(HC595_Q7_IsHigh)
		{
			DIGITAL_IO_STATE |= 0x01;
		} 
		Hc165_CP_LOW;
		Delay_Us(10);
		Hc165_CP_HIGH;
		Delay_Us(10);
	}
	Hc165_CE_HIGH;
	return DIGITAL_IO_STATE;
}
//一次读取4个165的数据
uint32_t DIGITAL_READ_All(void)
{
	uint32_t DIGITAL_IO_STATE = 0x00000000;
	unsigned char i = 0;
	Hc165_CE_LOW;
	Hc165_PL_LOW;
	Hc165_PL_HIGH;
	Hc165_CP_LOW;
	Delay_Us(10);
	for (i=0;i<32;i++)
	{
		DIGITAL_IO_STATE <<= 1;
		if(HC595_Q7_IsHigh)
		{
			DIGITAL_IO_STATE |= 0x01;
		} 
		Hc165_CP_LOW;
		Delay_Us(100);
		Hc165_CP_HIGH;
		Delay_Us(10);
	}
	Hc165_CE_HIGH;
	return DIGITAL_IO_STATE;
}


#include <RELAY.h>
#define LCLK_HIGH		GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET)
#define LCLK_LOW		GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET)

#define SCLK_HIGH		GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET)
#define SCLK_LOW		GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_RESET)

#define DATA_HIGH		GPIO_WriteBit(GPIOA,GPIO_Pin_15,Bit_SET)
#define DATA_LOW		GPIO_WriteBit(GPIOA,GPIO_Pin_15,Bit_RESET)

void RELAY_Init(void)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	
	//PA12 PA11 PA15 -- LCLK SCLK DATA
	//RRC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//如果不复用端口，可取消
	//GPIO
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_15;	
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);
	//Remap
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//复用JNTRST端口 同时关闭SWD端口
	Relay_Send8BitData(0x00);
}

void Relay_SendData(uint32_t Data)
{
	unsigned char i=0;
	LCLK_HIGH;
	SCLK_LOW;
	for(i=0;i<32;i++)
	{
		if(Data & 1<<i)
			DATA_HIGH;
		else
			DATA_LOW;
		Delay_Us(5);
		SCLK_HIGH;
		Delay_Us(5);
		SCLK_LOW;
	}
	LCLK_LOW;
}

void Relay_Send8BitData(uint8_t Data)
{
	unsigned char i=0;
	LCLK_HIGH;
	SCLK_LOW;
	for(i=0;i<8;i++)
	{
		if(Data & 1<<i)
			DATA_HIGH;
		else
			DATA_LOW;
		Delay_Us(5);
		SCLK_HIGH;
		Delay_Us(5);
		SCLK_LOW;
	}
	LCLK_LOW;
}

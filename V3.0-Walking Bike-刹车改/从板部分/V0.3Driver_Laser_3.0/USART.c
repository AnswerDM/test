#include <USART.h>

void UART1_init(int burt)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef mUSART_InitStructure;    
		
/************************USART 对应的时钟初始化************************/
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
/************************USART 中断接收********************************/
		
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);    
	
/************************USART 对应的端口初始化************************/
    
	//PA9 -- USART1_TX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;				
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);
		
	//PA10 -- USART1_RX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;			
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);

/************************USART 初始化************************/

	mUSART_InitStructure.USART_BaudRate = burt;//波特率设置
	mUSART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	mUSART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	mUSART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	mUSART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	mUSART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
		
	USART_Init(USART1, &mUSART_InitStructure); //初始化串口2
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//初始化串口中断		
	USART_Cmd(USART1, ENABLE);  //使能串口2
}

void USART1_IRQHandler(void)
{  
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)  
	{
		Uartx_SendData(USART2, USART_ReceiveData(USART1));  
		Uartx_SendData(USART1, USART_ReceiveData(USART1));  
	}
}

void UART2_init(int burt)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef mUSART_InitStructure;    
		
/************************USART 对应的时钟初始化************************/
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		
/************************USART 中断接收********************************/
		
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
	
/************************USART 对应的端口初始化************************/
    
	//PA2 -- USART2_TX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;				
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);
	
	//PA3 -- USART2_RX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;			
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);

/************************USART 初始化************************/

	mUSART_InitStructure.USART_BaudRate = burt;//波特率设置
	mUSART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	mUSART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	mUSART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	mUSART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	mUSART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	USART_Init(USART2, &mUSART_InitStructure); //初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//初始化串口中断		
	USART_Cmd(USART2, ENABLE);  //使能串口2
}
int receive_state = 0;
u8 buf_rec_usart_2[10]={0};

void USART2_IRQHandler(void)
{  
	u8 data;
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)  
	{       
		//Uartx_SendData(USART2, USART_ReceiveData(USART2));  

		data = USART_ReceiveData(USART2);
	  //USART_SendData(USART1, data);
		switch(receive_state)
		{
			case 0://start
				if(data==0xFA)
						receive_state=1;
				break;
			case 1://length,,不等于7E和7D，否则需要修改程序
				buf_rec_usart_2[0] = data;
			  receive_state = 2;
				break;
			case 2://data
				buf_rec_usart_2[1] = data;
			  receive_state = 0;
				break;
			default:
				receive_state = 0;
				break;
		}
		           
		
		
		
		
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

void UART3_init(int burt)
{
	GPIO_InitTypeDef mGPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef mUSART_InitStructure;    
		
/************************USART 对应的时钟初始化************************/
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		
/************************USART 中断接收********************************/
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);    
	
/************************USART 对应的端口初始化************************/
    
	//PB10 -- USART3_TX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;				
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&mGPIO_InitStructure);
	
	//PB11 -- USART3_RX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;			
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&mGPIO_InitStructure);

/************************USART 初始化************************/

	mUSART_InitStructure.USART_BaudRate = burt;//波特率设置
	mUSART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	mUSART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	mUSART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	mUSART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	mUSART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	USART_Init(USART3, &mUSART_InitStructure); //初始化串口2
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//初始化串口中断		
	USART_Cmd(USART3, ENABLE);  //使能串口2
}

void USART3_IRQHandler(void)
{  
//	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)  
//	{       
//		Uartx_SendData(USART1, USART_ReceiveData(USART3));
//    Uartx_SendData(USART2, USART_ReceiveData(USART3));		
//	}
}

/* send data */
void Uartx_SendnBuf(USART_TypeDef* USARTx, uint8_t *buf, uint16_t len)
{
    while(len--)
    {
			Uartx_SendData(USARTx,*buf++);
    }
}




/* send data */
void Uartx_SendMessage(USART_TypeDef* USARTx, uint8_t *buf)
{
    while(*buf != '\0')
    {	
		USART_SendData(USARTx,*buf++);
    }
}

/* send data */
void Uartx_SendData(USART_TypeDef* USARTx, uint8_t data)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx,data);
	//while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	//while((USARTx->SR&0X40)==0);
}

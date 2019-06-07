#include "init.h"


//----- (08001614) --------------------------------------------------------
void init_port()
{
	//控制电机PA8 PB13 PA9 PB14 PA10 PB15
	//控制电机PC7 PB0 PB1 PC8 PC6 PA7
	//PC2 PA1 PA5?
	//PA1 开关 PA5 软开关
	//PC2电池ad检测
	//PC0 1 ? 运放 电压
	//PA6 ?
	//PB12 ?
	//PA0 PC3 可能是u v电流检测
	//PC4 PC5 可能是u v电流相
	//PA4 喇叭
  GPIO_InitTypeDef type;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|
						RCC_APB2Periph_GPIOB|
						RCC_APB2Periph_GPIOA|
						RCC_APB2Periph_AFIO, ENABLE);//使能或者失能 APB2 外设时钟
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//改变指定管脚的映射
  
	/**************************/
	//USART PA3 PA2 
	//重电器接口检测 PA12
	type.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6;//PA3 PA6      PA3:USART_Rx  PA6:测VCCR是否高电平
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//PA0 PA1 ad输入
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;// 1924;//PA2、7、8、9、10
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14;//24624;//PA4、5、13、14
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;//0x9800;//PA11 12  15
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_12;//4096;//PA12
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &type);
	/**************************/
	//USART PB10 PB11
	//LED PB2
	//HALL_L PB5 6 7
  type.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;//792;//PB3\4\8\9
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &type);
	
  type.GPIO_Pin = GPIO_Pin_2;//4;//PB2
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &type);
	
  type.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12;//6368;//PB5\6\7\11\12
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &type);
	
  type.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//0xE403;//PB0\1\10\13\14\15
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &type);
	
	/**************************/
	//HALL_R PC10 11 12
  type.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//7168;//PC10\11\12
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &type);
	
	type.GPIO_Pin = GPIO_Pin_9;//7168;//PC10\11\12
  //type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &type);
	
  type.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;// 63;//PC0\1\2\3\4\5
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &type);
	
  type.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;//PC6\7\8\9
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &type);
	
  type.GPIO_Pin = 0xE000;//PC13\14\15
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &type);
	//没用
  type.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//PD0\1
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOD, &type);
}

//----- (08001804) --------------------------------------------------------
void init_time2()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//使能或者失能 APB2 外设时钟
  TIM8->CR1 = 196;
  TIM8->CR2 = 10785;
  TIM8->DIER = 129;
  TIM8->CCMR1 = 26728;
  TIM8->CCMR2 = 14440;
  TIM8->PSC = 3;
  TIM8->ARR = 512;
  TIM8->BDTR = 0x9020;
  TIM8->CCR1 = 0;
  TIM8->CCR2 = 0;
  TIM8->CCR3 = 0;
  TIM8->CCR4 = 510;
  TIM8->CCER = 7645;
  TIM8->EGR = 33;
  TIM8->RCR = 1;
  TIM8->CR1 |= 1;
}

//----- (080018CE) --------------------------------------------------------
void init_time1()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能或者失能 APB2 外设时钟
  TIM1->CR1 = 196;   //0b0000 0000 1100 0100
	/*
	位9:8 00 tDTS = tCK_INT
	位7    1 TIMx_ARR寄存器被装入缓冲器
	位6:5 10 中央对齐模式2。计数器交替地向上和向下计数。配置为输出的通道（TIMx_CCMRx寄存器中CCxS=00）的输出比较中断标志位，只在计数器向上时被设置。
	位4    0 计数器向上计数
	位3    0 在发生更新事件时，计数器不停止。
	位2    1 如果使能了更新中断或DMA请求，则只有计数器溢出/下溢才产生更新中断或DMA请求。
	位1    0 允许UEV
	位0    0 禁止计数器
	*/
  TIM1->CR2 = 10785; //0b 0010 1010 0010 0001
	/*
	位13   1
	位11   1
	位9    1
	位5    1
	位0    1 
	*/
  TIM1->DIER = 129;  //0b1000 0001 使能更新中断
	/*
	位7    1 允许刹车中断
	位0    1 允许更新中断
	*/
  TIM1->CCMR1 = 26728; // 0b 0110 1000 0110 1000
  TIM1->CCMR2 = 104;   // 0b 0000 0000 0110 1000
  TIM1->PSC = 3;       //分频系数 计数器的时钟频率CK_CNT等于f(ck_psc)/(PSC[15:0]+1)
  TIM1->ARR = 512;
  TIM1->CCR4 = 0;
  TIM1->BDTR = 0x9020; //0b1001 0000 0010 0000       //设置死区时间
  TIM1->CCR1 = 0;
  TIM1->CCR2 = 0;
  TIM1->CCR3 = 0;
  TIM1->CCER = 3549;    //0b0000 1101 1101 1101
  TIM1->EGR = 33;
  TIM1->RCR = 1;         //重复计数器，重复计数次数为1
  TIM1->CR1 |= 1;        //使能计数器
}
//----- (0800198E) --------------------------------------------------------
void init_nvic()
{//优先级初始化
  NVIC_InitTypeDef nvic;
  nvic.NVIC_IRQChannel=25;//TIM1_UP_IRQChannel     //#define TIM1_UP_IRQChannel           ((u8)0x19)  /* TIM1 Update Interrupt */
  nvic.NVIC_IRQChannelPreemptionPriority=1;
  nvic.NVIC_IRQChannelSubPriority=1;
  nvic.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&nvic);//根据 NVIC_InitStruct 中指定的参数初始化外设 NVIC 寄存器
	
	
	
	
	
	
	
	
	
//	//  interruct for hall sensor  
//	nvic.NVIC_IRQChannel=23;                        //#define EXTI9_5_IRQChannel           ((u8)0x17)   External Line[9:5] Interrupts 
//	nvic.NVIC_IRQChannelPreemptionPriority=1;
//	nvic.NVIC_IRQChannelSubPriority=0;
//	nvic.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&nvic);
//  
//	//  interruct for hall sensor   
//	nvic.NVIC_IRQChannel=40;                        //#define EXTI15_10_IRQChannel         ((u8)0x28)   External Line[15:10] Interrupts 
//	nvic.NVIC_IRQChannelPreemptionPriority=1;
//	nvic.NVIC_IRQChannelSubPriority=0;
//	nvic.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&nvic);
//	
//	
//	
//	nvic.NVIC_IRQChannel = 29;  //#define TIM3_IRQChannel              ((u8)0x1D)  /* TIM3 global Interrupt */
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	nvic.NVIC_IRQChannelPreemptionPriority = 0;
//	nvic.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&nvic);
}

//----- (080019B0) --------------------------------------------------------
void init_adc()
{//初始化adc
  RCC->APB2ENR |= 0x8600u;//时钟配置
  RCC->APB2RSTR |= 0x600u;
  RCC->APB2RSTR &= 0xFFFFF9FF;
  RCC->CFGR &= 0xFFFF3FFF;//时钟配置
  RCC->CFGR |= 0x8000u;
  ADC1->CR1 = 0;
  ADC2->CR1 = 256;//扫描模式
  ADC3->CR1 = 256;//扫描模式
	//4个转换 ADC3_H13 ADC3_H0  ADC3_H10 ADC3_H12
	//PC3 PA0 PC0 PC2
	//w u相 电池检测
  ADC3->JSQR = 0x36280D;    
	/*0b0011 0110 0010 1000 0000 1101
	位21:20      11  四个转换
	位19:15   01100  第4个转换  ADC3_IN12   PC2  bet_vol_buf_068[get_adc_cnt_058] = ADC3->JDR4;     电池电压采样
	位14:10   01010  第3个转换  ADC3_IN10   PC0  motor2_load_buf_060[get_adc_cnt_058] = ADC3->JDR3; VCCR
	位 9: 5   00000  第2个转换  ADC3_IN0    PA0  motor2_w_cur_05E = ADC3->JDR2;                     VCCR&VCC1(AR输出)
	位 4: 0   01101  第1个转换  ADC3_IN13   PC3  motor2_u_cur_05C = ADC3->JDR1;                     VCCR&VCC2(BR输出)
	*/
	
	//4个转换 ADC2_H14 ADC2_H15 ADC2_H11 ADC2_H1
	//PC4 PC5 PC1 PA1
	//w u相 开关
  ADC2->JSQR = 0x30ADEE;
	/*0b0011 0000 1010 1101 1110 1110
	位21:20      11  四个转换
	位19:15   00001  第4个转换  ADC2_IN1    PA1  boot_vol_buf_07C[get_adc_cnt_058] = ADC2->JDR4;      电源开关检测
	位14:10   01011  第3个转换  ADC2_IN11   PC1  motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;   VCCL
	位 9: 5   01111  第2个转换  ADC2_IN15   PC5  motor1_w_cur_072 = ADC2->JDR2;                       VCCL&VCC3(CL输出)
	位 4: 0   01110  第1个转换  ADC2_IN14   PC4  motor1_u_cur_070 = ADC2->JDR1;                       VCCL&VCC4(BL输出)
	*/
	
	
  ADC2->CR2 = 0x8001;//使能 触发模式 外部时间启动转换 T1的TRGO 事件
  ADC3->CR2 = 0x8001;//0xC001;//使能 触发模式 外部时间启动转换 T3的CC4 事件
  ADC1->CR2 = 9;//使能
  while ( ADC1->CR2 & 8 ){;}  ADC1->CR2 |= 4u;
  while ( ADC1->CR2 & 4 ){;}  ADC2->CR2 |= 8u;
		
  while ( ADC2->CR2 & 8 ){;}	ADC2->CR2 |= 4u;
  while ( ADC2->CR2 & 4 ){;}  ADC3->CR2 |= 8u;
		
  while ( ADC3->CR2 & 8 ){;}  ADC3->CR2 |= 4u;
	while ( ADC3->CR2 & 4 ){;}  //ADC3->CR2 |= 4u;
}

//----- (08001B54) --------------------------------------------------------
void init_rcc()
{//初始化rcc
  RCC_DeInit();//将外设 RCC 寄存器重设为缺省值
  RCC_HSICmd(ENABLE);//使能内部高速晶振HSI
  while ( !RCC_GetFlagStatus(33) )//检查指定的 RCC 标志位设置与否
    ;
  FLASH_PrefetchBufferCmd(16);//使能或者失能预取指缓存
  FLASH_SetLatency(FLASH_Latency_2);//设置代码延时值
  RCC_HCLKConfig(0);//设置 AHB 时钟
  RCC_PCLK2Config(0);//设置高速 AHB 时钟（PCLK2）
  RCC_PCLK1Config(1024);//设置低速 AHB 时钟（PCLK1）
  RCC_PLLConfig(0, RCC_PLLMul_16);//设置 PLL 时钟源及倍频系数
  RCC_PLLCmd(ENABLE);//使能或者失能 PLL
  while ( !RCC_GetFlagStatus(RCC_FLAG_PLLRDY) )//检查指定的 RCC 标志位设置与否
    ;
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while ( RCC_GetSYSCLKSource() != 8 );//设置系统时钟
}
//----- (08001BBA) --------------------------------------------------------
void UART2_init(int burt)
{
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
////  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//  USART2->BRR = 1216;//波特率寄存器 9600
////  USART3->BRR = 1216;//波特率寄存器
//  USART2->CR1 = 12300;//控制寄存器
////	USART3->CR1 = 12300;
	GPIO_InitTypeDef mGPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef mUSART_InitStructure;    
		
/************************USART 对应的时钟初始化************************/
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		
/************************USART 中断接收********************************/
		
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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
			{
				if(data==0xFB)
				{
					if(error_1D1==0)
					{
						count_usart2_rec = 0;
					}
					receive_state=1;
				}
				break;
			}
			case 1://length,,不等于7E和7D，否则需要修改程序
			{
				buf_rec_usart_2[0] = data;
			  receive_state = 0;
				break;
			}
//			case 2://data
//				//buf_rec_usart_2[1] = data;
//			  receive_state = 0;
//				break;
			default:
			{
				receive_state = 0;
				break;
			}
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}


void init_EXIT(void)
{
	EXTI_InitTypeDef  EXTI_InitStruct;
//	GPIO_InitTypeDef  GPIO_InitStruct;
  //霍尔传感器
  //近电池轮  PC10 PC11 PC12
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);

	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
  
  EXTI_InitStruct.EXTI_Line=EXTI_Line10;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line=EXTI_Line11;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line=EXTI_Line12;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
	
	//远电池轮  PB5 PB6 PB7
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
  
	EXTI_InitStruct.EXTI_Line=EXTI_Line5;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line=EXTI_Line6;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line=EXTI_Line7;//EXT1_Line0 GPIO_PinSource0 
	EXTI_Init(&EXTI_InitStruct);
}
void Bsp_timInit(void)
{
	TIM_TimeBaseInitTypeDef tim;
//TIM3 ??????
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 4999;//999;
	tim.TIM_Prescaler = 35;
	tim.TIM_RepetitionCounter = 1;
	TIM_TimeBaseInit(TIM3, &tim);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}
u16 v0; 
//----- (08001BE6) --------------------------------------------------------
void init()
{//初始化
  

	//延时
//  v0 = 20000;
//  while ( v0-- == 0 );//没有用
  init_rcc();
  init_port();
  init_time1();//驱动电机初始化1
  //init_time2();//驱动电机初始化2
  init_adc();
  init_nvic();
  UART2_init(115200);
	//init_EXIT();//霍尔原件外部触发中断初始化
	//Bsp_timInit();
	
	PIDInit();
}

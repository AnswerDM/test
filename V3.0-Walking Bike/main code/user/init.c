#include "init.h"


//----- (08001614) --------------------------------------------------------
void init_port()
{
	//���Ƶ��PA8 PB13 PA9 PB14 PA10 PB15
	//���Ƶ��PC7 PB0 PB1 PC8 PC6 PA7
	//PC2 PA1 PA5?
	//PA1 ���� PA5 ����
	//PC2���ad���
	//PC0 1 ? �˷� ��ѹ
	//PA6 ?
	//PB12 ?
	//PA0 PC3 ������u v�������
	//PC4 PC5 ������u v������
	//PA4 ����
  GPIO_InitTypeDef type;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|
						RCC_APB2Periph_GPIOB|
						RCC_APB2Periph_GPIOA|
						RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܻ���ʧ�� APB2 ����ʱ��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ı�ָ���ܽŵ�ӳ��
  
	/**************************/
	//USART PA3 PA2 
	//�ص����ӿڼ�� PA12
	type.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6;//PA3 PA6      PA3:USART_Rx  PA6:��VCCR�Ƿ�ߵ�ƽ
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//PA0 PA1 ad����
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;// 1924;//PA2��7��8��9��10
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &type);
	
  type.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14;//24624;//PA4��5��13��14
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
	//û��
  type.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//PD0\1
  type.GPIO_Speed = GPIO_Speed_2MHz;
  type.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOD, &type);
}

//----- (08001804) --------------------------------------------------------
void init_time2()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//ʹ�ܻ���ʧ�� APB2 ����ʱ��
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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܻ���ʧ�� APB2 ����ʱ��
  TIM1->CR1 = 196;   //0b0000 0000 1100 0100
	/*
	λ9:8 00 tDTS = tCK_INT
	λ7    1 TIMx_ARR�Ĵ�����װ�뻺����
	λ6:5 10 �������ģʽ2����������������Ϻ����¼���������Ϊ�����ͨ����TIMx_CCMRx�Ĵ�����CCxS=00��������Ƚ��жϱ�־λ��ֻ�ڼ���������ʱ�����á�
	λ4    0 ���������ϼ���
	λ3    0 �ڷ��������¼�ʱ����������ֹͣ��
	λ2    1 ���ʹ���˸����жϻ�DMA������ֻ�м��������/����Ų��������жϻ�DMA����
	λ1    0 ����UEV
	λ0    0 ��ֹ������
	*/
  TIM1->CR2 = 10785; //0b 0010 1010 0010 0001
	/*
	λ13   1
	λ11   1
	λ9    1
	λ5    1
	λ0    1 
	*/
  TIM1->DIER = 129;  //0b1000 0001 ʹ�ܸ����ж�
	/*
	λ7    1 ����ɲ���ж�
	λ0    1 ��������ж�
	*/
  TIM1->CCMR1 = 26728; // 0b 0110 1000 0110 1000
  TIM1->CCMR2 = 104;   // 0b 0000 0000 0110 1000
  TIM1->PSC = 3;       //��Ƶϵ�� ��������ʱ��Ƶ��CK_CNT����f(ck_psc)/(PSC[15:0]+1)
  TIM1->ARR = 512;
  TIM1->CCR4 = 0;
  TIM1->BDTR = 0x9020; //0b1001 0000 0010 0000       //��������ʱ��
  TIM1->CCR1 = 0;
  TIM1->CCR2 = 0;
  TIM1->CCR3 = 0;
  TIM1->CCER = 3549;    //0b0000 1101 1101 1101
  TIM1->EGR = 33;
  TIM1->RCR = 1;         //�ظ����������ظ���������Ϊ1
  TIM1->CR1 |= 1;        //ʹ�ܼ�����
}
//----- (0800198E) --------------------------------------------------------
void init_nvic()
{//���ȼ���ʼ��
  NVIC_InitTypeDef nvic;
  nvic.NVIC_IRQChannel=25;//TIM1_UP_IRQChannel     //#define TIM1_UP_IRQChannel           ((u8)0x19)  /* TIM1 Update Interrupt */
  nvic.NVIC_IRQChannelPreemptionPriority=1;
  nvic.NVIC_IRQChannelSubPriority=1;
  nvic.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&nvic);//���� NVIC_InitStruct ��ָ���Ĳ�����ʼ������ NVIC �Ĵ���
	
	
	
	
	
	
	
	
	
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
{//��ʼ��adc
  RCC->APB2ENR |= 0x8600u;//ʱ������
  RCC->APB2RSTR |= 0x600u;
  RCC->APB2RSTR &= 0xFFFFF9FF;
  RCC->CFGR &= 0xFFFF3FFF;//ʱ������
  RCC->CFGR |= 0x8000u;
  ADC1->CR1 = 0;
  ADC2->CR1 = 256;//ɨ��ģʽ
  ADC3->CR1 = 256;//ɨ��ģʽ
	//4��ת�� ADC3_H13 ADC3_H0  ADC3_H10 ADC3_H12
	//PC3 PA0 PC0 PC2
	//w u�� ��ؼ��
  ADC3->JSQR = 0x36280D;    
	/*0b0011 0110 0010 1000 0000 1101
	λ21:20      11  �ĸ�ת��
	λ19:15   01100  ��4��ת��  ADC3_IN12   PC2  bet_vol_buf_068[get_adc_cnt_058] = ADC3->JDR4;     ��ص�ѹ����
	λ14:10   01010  ��3��ת��  ADC3_IN10   PC0  motor2_load_buf_060[get_adc_cnt_058] = ADC3->JDR3; VCCR
	λ 9: 5   00000  ��2��ת��  ADC3_IN0    PA0  motor2_w_cur_05E = ADC3->JDR2;                     VCCR&VCC1(AR���)
	λ 4: 0   01101  ��1��ת��  ADC3_IN13   PC3  motor2_u_cur_05C = ADC3->JDR1;                     VCCR&VCC2(BR���)
	*/
	
	//4��ת�� ADC2_H14 ADC2_H15 ADC2_H11 ADC2_H1
	//PC4 PC5 PC1 PA1
	//w u�� ����
  ADC2->JSQR = 0x30ADEE;
	/*0b0011 0000 1010 1101 1110 1110
	λ21:20      11  �ĸ�ת��
	λ19:15   00001  ��4��ת��  ADC2_IN1    PA1  boot_vol_buf_07C[get_adc_cnt_058] = ADC2->JDR4;      ��Դ���ؼ��
	λ14:10   01011  ��3��ת��  ADC2_IN11   PC1  motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;   VCCL
	λ 9: 5   01111  ��2��ת��  ADC2_IN15   PC5  motor1_w_cur_072 = ADC2->JDR2;                       VCCL&VCC3(CL���)
	λ 4: 0   01110  ��1��ת��  ADC2_IN14   PC4  motor1_u_cur_070 = ADC2->JDR1;                       VCCL&VCC4(BL���)
	*/
	
	
  ADC2->CR2 = 0x8001;//ʹ�� ����ģʽ �ⲿʱ������ת�� T1��TRGO �¼�
  ADC3->CR2 = 0x8001;//0xC001;//ʹ�� ����ģʽ �ⲿʱ������ת�� T3��CC4 �¼�
  ADC1->CR2 = 9;//ʹ��
  while ( ADC1->CR2 & 8 ){;}  ADC1->CR2 |= 4u;
  while ( ADC1->CR2 & 4 ){;}  ADC2->CR2 |= 8u;
		
  while ( ADC2->CR2 & 8 ){;}	ADC2->CR2 |= 4u;
  while ( ADC2->CR2 & 4 ){;}  ADC3->CR2 |= 8u;
		
  while ( ADC3->CR2 & 8 ){;}  ADC3->CR2 |= 4u;
	while ( ADC3->CR2 & 4 ){;}  //ADC3->CR2 |= 4u;
}

//----- (08001B54) --------------------------------------------------------
void init_rcc()
{//��ʼ��rcc
  RCC_DeInit();//������ RCC �Ĵ�������Ϊȱʡֵ
  RCC_HSICmd(ENABLE);//ʹ���ڲ����پ���HSI
  while ( !RCC_GetFlagStatus(33) )//���ָ���� RCC ��־λ�������
    ;
  FLASH_PrefetchBufferCmd(16);//ʹ�ܻ���ʧ��Ԥȡָ����
  FLASH_SetLatency(FLASH_Latency_2);//���ô�����ʱֵ
  RCC_HCLKConfig(0);//���� AHB ʱ��
  RCC_PCLK2Config(0);//���ø��� AHB ʱ�ӣ�PCLK2��
  RCC_PCLK1Config(1024);//���õ��� AHB ʱ�ӣ�PCLK1��
  RCC_PLLConfig(0, RCC_PLLMul_16);//���� PLL ʱ��Դ����Ƶϵ��
  RCC_PLLCmd(ENABLE);//ʹ�ܻ���ʧ�� PLL
  while ( !RCC_GetFlagStatus(RCC_FLAG_PLLRDY) )//���ָ���� RCC ��־λ�������
    ;
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while ( RCC_GetSYSCLKSource() != 8 );//����ϵͳʱ��
}
//----- (08001BBA) --------------------------------------------------------
void UART2_init(int burt)
{
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
////  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//  USART2->BRR = 1216;//�����ʼĴ��� 9600
////  USART3->BRR = 1216;//�����ʼĴ���
//  USART2->CR1 = 12300;//���ƼĴ���
////	USART3->CR1 = 12300;
	GPIO_InitTypeDef mGPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef mUSART_InitStructure;    
		
/************************USART ��Ӧ��ʱ�ӳ�ʼ��************************/
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		
/************************USART �жϽ���********************************/
		
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
	
/************************USART ��Ӧ�Ķ˿ڳ�ʼ��************************/
    
	//PA2 -- USART2_TX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;				
	mGPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);
	
	//PA3 -- USART2_RX
	mGPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;			
	mGPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&mGPIO_InitStructure);

/************************USART ��ʼ��************************/

	mUSART_InitStructure.USART_BaudRate = burt;//����������
	mUSART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	mUSART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	mUSART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	mUSART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	mUSART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	USART_Init(USART2, &mUSART_InitStructure); //��ʼ������2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��ʼ�������ж�		
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
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
			case 1://length,,������7E��7D��������Ҫ�޸ĳ���
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
  //����������
  //�������  PC10 PC11 PC12
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
	
	//Զ�����  PB5 PB6 PB7
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
{//��ʼ��
  

	//��ʱ
//  v0 = 20000;
//  while ( v0-- == 0 );//û����
  init_rcc();
  init_port();
  init_time1();//���������ʼ��1
  //init_time2();//���������ʼ��2
  init_adc();
  init_nvic();
  UART2_init(115200);
	//init_EXIT();//����ԭ���ⲿ�����жϳ�ʼ��
	//Bsp_timInit();
	
	PIDInit();
}

/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"

uip_ipaddr_t ipaddr;
extern uint8_t slave_id;

int j=0,k=0,l=0;
int SendFlag;
extern uint8_t receive_data[21][50];
extern uint8_t receive_dp_data[90];
extern uint8_t slave_id_max;
extern uint8_t CH_NUM;
uint8_t set_data[22] ;
uint8_t data_header_set[2]={0xAB,0xCD};
uint8_t data_end_set[2]={0xBC,0xDE};
uint8_t EN[21];
uint8_t CH_NUM_temp = 0x0B ;
extern int data;
int flag=0;
uint8_t rx_len = 0;
uint8_t receive_bufdata;

uint8_t temp_data[25];
extern uint8_t ii;
extern uint8_t offline_flag[21] ;
extern uint8_t receive_ip[4];

uint8_t IRQ_in[21] = {0};

extern u8 tcp_server_tsta;
extern uint8_t signal_intensity[5];
//	extern uint8_t signal_intensity_flag;

//uint8_t data_header[] = {0x55,0x55};
//uint8_t data_end[] = {0x0d,0x0d};

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
	
}
	

void UART4_IRQHandler(void)                	  //����1�жϷ������
{

} 

void USART2_IRQHandler(void)                	//����2�жϷ������
{ 	
		 if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
			{ 
				 USART_ClearITPendingBit(USART2, USART_IT_RXNE);			
				 receive_dp_data[l++] = USART_ReceiveData(USART2);
			}
			for(uint8_t a=0;a<90;a++)
			{
				if(receive_dp_data[a] == 0xAB && receive_dp_data[a+1] == 0xCD && 
					receive_dp_data[a+28] ==0xBC && receive_dp_data[a+29] == 0xDE)
				{
					for(uint8_t b=0;b<26;b++)
					{
						set_data[b] = receive_dp_data[a+2+b];
					}
				}
			}
			slave_id_max = set_data[21];
			
			for(u8 i=22;i<26;i++)  //����ӵ�ip��ַ���͸�ֵ��dp��оƬ�İ�β���
			{
				receive_ip[i-22]=set_data[i];
			}
			
			CH_NUM_temp = set_data[0];
			for(u8 c=1;c<21;c++)
			{
				EN[c] = set_data[c];
			}
			
			if(CH_NUM_temp != CH_NUM)
			{
				
				CH_NUM = CH_NUM_temp;
				
				
				zigbee_configure();
				delay_ms(20);
				ii=0;

			}
			
			 uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],receive_ip[3]);	//���ñ�������IP��ַ
			 uip_sethostaddr(ipaddr);					    
			 uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],1); 	//��������IP��ַ(��ʵ������·������IP��ַ)
			 uip_setdraddr(ipaddr);						 
			 uip_ipaddr(ipaddr,255,255,255,0);//������������
			 uip_setnetmask(ipaddr);
			 uip_listen(HTONS(55555));
			

			 uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],receive_ip[3]);	//���ñ�������IP��ַ
			 uip_sethostaddr(ipaddr);					    
			 uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],1); 	//��������IP��ַ(��ʵ������·������IP��ַ)
			 uip_setdraddr(ipaddr);						 
			 uip_ipaddr(ipaddr,255,255,255,0);//������������
			 uip_setnetmask(ipaddr);
			 uip_listen(HTONS(55555));
	
			
			if(l==90)
			{
				l = 0;
			}
} 

void TIM5_IRQHandler(void)//��ʱ1sɨ��һ�δ�վ״̬����ʾ��Ӧ��ָʾ��
{ 	
	uint8_t i ;
	
	
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		
	
		for(i=0;i<19;i=i+2)//��Ӧ��20����ɨ��״̬
		{
			switch(offline_flag[i+1])//��ɨ�������ŵ�
			{
				case 1:switch(offline_flag[i+2])//��ɨ��ż���ŵ�
				{
					case 1:HC595G_WriteByte(LED_ODD_GREEN &  LED_EVEN_GREEN,i);break;
					case 2:HC595G_WriteByte(LED_ODD_GREEN &  LED_EVEN_RED,i);	 break;
					case 3:HC595G_WriteByte(LED_ODD_GREEN &  LED_EVEN_BLUE,i); break;
			    case 4:HC595G_WriteByte(LED_ODD_GREEN &  LED_EVEN_OFF,i);  break;
					
				}
				break;
				case 2:switch(offline_flag[i+2])
				{
					case 1:HC595G_WriteByte(LED_ODD_RED &  LED_EVEN_GREEN,i);  break;
					case 2:HC595G_WriteByte(LED_ODD_RED &  LED_EVEN_RED,i);    break;
					case 3:HC595G_WriteByte(LED_ODD_RED &  LED_EVEN_BLUE,i);   break;
					case 4:HC595G_WriteByte(LED_ODD_RED &  LED_EVEN_OFF,i);   break;
				
				}
					break;
				case 3:switch(offline_flag[i+2])
				{
					case 1:HC595G_WriteByte(LED_ODD_BLUE &  LED_EVEN_GREEN,i); break;
					case 2:HC595G_WriteByte(LED_ODD_BLUE &  LED_EVEN_RED,i);	 break;
					case 3:HC595G_WriteByte(LED_ODD_BLUE &  LED_EVEN_BLUE,i);  break;
					case 4:HC595G_WriteByte(LED_ODD_BLUE &  LED_EVEN_OFF,i);  break;
					
				}
					break;
				case 4:switch(offline_flag[i+2])
				{
					case 1:HC595G_WriteByte(LED_ODD_OFF &  LED_EVEN_GREEN,i); break;
					case 2:HC595G_WriteByte(LED_ODD_OFF &  LED_EVEN_RED,i);	 break;
					case 3:HC595G_WriteByte(LED_ODD_OFF &  LED_EVEN_BLUE,i);  break;
					case 4:HC595G_WriteByte(LED_ODD_OFF &  LED_EVEN_OFF,i);  break;
					
				}
					break;
				
			}
					
		}


		
	} 
	
	
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				    		  			    	    
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */



void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
//  while (1)
  {
  }

}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
	
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

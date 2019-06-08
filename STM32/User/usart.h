#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2011/6/14
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
typedef enum _UartEvent_
{
   E_uart_0 = 0,// ????
   E_uart_tc=0x40,                  //????
   E_uart_idle=0x80,               //????
}UartEvent;


void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart4_init(u32 bound);

uint16_t USART1_Receive(void);
int UART4_Receive(void);
void UartASendStr (uint8_t  *pucStr, u8 ulNum) ;
void UartASendStr_slow (uint16_t *pucStr, u8 ulNum) ;
void Uart2ASendStr_slow (unsigned char *pucStr, u8 ulNum) ;
void Uart4ASendStr_slow (unsigned char *pucStr, u8 ulNum) ;
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u32 cndtr);
UartEvent Uart_Get_Event(void);
#endif

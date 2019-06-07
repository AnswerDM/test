#ifndef _USART_H_
#define _USART_H_

#include <MAIN.h>

extern void UART1_init(int burt);
extern void UART2_init(int burt);
extern void UART3_init(int burt);

extern void Uartx_SendnBuf(USART_TypeDef* USARTx, uint8_t *buf, uint16_t len);
extern void Uartx_SendMessage(USART_TypeDef* USARTx, uint8_t *buf);
extern void Uartx_SendData(USART_TypeDef* USARTx, uint8_t data);

extern u8 buf_rec_usart_2[10];
#endif

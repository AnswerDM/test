#ifndef _RELAY_H_
#define _RELAY_H_

#include <MAIN.h>

extern void RELAY_Init(void);

extern void Relay_SendData(uint32_t Data);
extern void Relay_Send8BitData(uint8_t Data);

#endif

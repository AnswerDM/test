#ifndef __74hc595_H
#define __74hc595_H


#include <stm32f10x.h>

#include "GPIO_Init.h"

void HC595G_WriteByte(uint32_t byte,uint8_t Enable);

#endif




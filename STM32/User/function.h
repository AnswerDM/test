#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "main.h"

void scan_enable_receive(void);
uint8_t Get_SumCheck(uint8_t x,uint8_t array[x][26]);
//uint8_t Get_SumCheck(uint8_t array[25]);
unsigned char SumCheck(unsigned char data);
void clear_receive_data(void);



#endif



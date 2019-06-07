#ifndef __INIT_H
#define __INIT_H		
#include "extern.h"
#include "pid.h"

void init_port(void);
void init_time2(void);
void init_time1(void);
void init_nvic(void);
void init_adc(void);
void init_rcc(void);
void UART2_init(int burt);

void init_EXIT(void);

void init(void);
#endif


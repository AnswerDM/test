#ifndef _DIGITAL_INPUT_
#define _DIGITAL_INPUT_

#include <MAIN.h>

extern void DIGITAL_INPUT_Init(void);
extern unsigned char DIGITAL_READ(unsigned char ICnum);
extern uint32_t DIGITAL_READ_All(void);
#endif

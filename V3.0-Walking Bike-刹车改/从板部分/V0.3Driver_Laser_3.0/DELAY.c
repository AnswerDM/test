#include <DELAY.h>

void Delay_Ms(int time)
{
	int i = 0;
	while(i++ < time)
		Delay_Us(950);
}

void Delay_Us(int time)
{
	int i = 0;
	while(i++ < time)
		;
}

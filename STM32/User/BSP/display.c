#include "display.h"

unsigned char scandata[20] = 			//段码表
{
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBF , 0x89  ,0x86,0xC7,0x8E,0xff,0xc8,0x8c,0x8d,0xA1
}; 
										//0,1,2,3,4,5,6,7,8,9,-,H,E,L,F,?,N,P,r

unsigned char displaynum[5] = 
{ 
	0,10,0,0,0							         //第几个数码管显示第几个数
};

unsigned char displaychar[5] = 
{	
	0,10,0,0,0                       //中间变量
};	

unsigned char bit = 0; 	

void display_number(unsigned char number)
{
	if(number == 0)
	{
		
	}
}

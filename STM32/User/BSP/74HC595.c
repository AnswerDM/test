#include "74hc595.h"
#include "delay.h"
/***************在74hc595中，Qa为高位，依次分别为最低位**************************/
//亮红灯为108，绿灯为180

void HC595G_WriteByte(uint32_t byte,uint8_t Enable)
 {
	if(Enable ==0)
	{
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOF,GPIO_Pin_8);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOF,GPIO_Pin_8);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		 delay_ms(1);
		 GPIO_SetBits(GPIOF,GPIO_Pin_10);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);
	delay_ms(1);
	GPIO_SetBits(GPIOF,GPIO_Pin_9);
}
	
if(Enable == 2)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOF,GPIO_Pin_5);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOF,GPIO_Pin_5);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOF,GPIO_Pin_7);
		 delay_ms(1);
		 GPIO_SetBits(GPIOF,GPIO_Pin_7);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	delay_ms(1);
	GPIO_SetBits(GPIOF,GPIO_Pin_6);
 }

 
 if(Enable == 4)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOA,GPIO_Pin_15);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOA,GPIO_Pin_15);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOF,GPIO_Pin_4);
		 delay_ms(1);
		 GPIO_SetBits(GPIOF,GPIO_Pin_4);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);
	delay_ms(1);
	GPIO_SetBits(GPIOF,GPIO_Pin_3);
 }
 
 
 if(Enable == 6)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOF,GPIO_Pin_0);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOF,GPIO_Pin_0);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOF,GPIO_Pin_2);
		 delay_ms(1);
		 GPIO_SetBits(GPIOF,GPIO_Pin_2);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);
	delay_ms(1);
	GPIO_SetBits(GPIOF,GPIO_Pin_1);
 }
	 
 if(Enable ==8)
	{
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOE,GPIO_Pin_5);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		 delay_ms(1);
		 GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	delay_ms(1);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);
 }
 
 
 if(Enable ==10)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOE,GPIO_Pin_2);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOE,GPIO_Pin_2);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOE,GPIO_Pin_4);
		 delay_ms(1);
		 GPIO_SetBits(GPIOE,GPIO_Pin_4);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	delay_ms(1);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
 }
 
 
 
 if(Enable == 12)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOG,GPIO_Pin_9);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOG,GPIO_Pin_9);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOG,GPIO_Pin_11);
		 delay_ms(1);
		 GPIO_SetBits(GPIOG,GPIO_Pin_11);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOG,GPIO_Pin_10);
	delay_ms(1);
	GPIO_SetBits(GPIOG,GPIO_Pin_10);
 }
 
 	 if(Enable == 14)
	 { 
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOD,GPIO_Pin_5);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOD,GPIO_Pin_5);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOD,GPIO_Pin_7);
		 delay_ms(1);
		 GPIO_SetBits(GPIOD,GPIO_Pin_7);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOD,GPIO_Pin_6);
	delay_ms(1);
	GPIO_SetBits(GPIOD,GPIO_Pin_6);
 }
	 
 if(Enable == 16)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOD,GPIO_Pin_2);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		 delay_ms(1);
		 GPIO_SetBits(GPIOD,GPIO_Pin_4);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	delay_ms(1);
	GPIO_SetBits(GPIOD,GPIO_Pin_3);
 }
 
 
	 if(Enable == 18)
	 {
	 uint8_t i;
	 
	 for(i=0;i<8;i++)
	 {
		 //将输入参数（二进制）与1按位取与。如果为1，则将相应的位置为1，否则为0。
		 if((byte & (0x01<<i)))
		 {
			 GPIO_SetBits(GPIOC,GPIO_Pin_12);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		 }
		 //SCK产生上升沿。进行移位
		 GPIO_ResetBits(GPIOD,GPIO_Pin_1);
		delay_ms(1);
		 GPIO_SetBits(GPIOD,GPIO_Pin_1);
	}
	//LCK产上升沿，将位移缓存器上的数据转移到输出缓存器。相当于一个开关
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	delay_ms(1);
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
 }
 
}



 




 
 
 
 
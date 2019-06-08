#include "zigbee.h"
//<=11CH_NUM<=26为信道和PAN ID
extern uint8_t CH_NUM;

void zigbee_configure(void)
{
	
	int i;
	

//	uint8_t link_zigbee[9]={0xFC,0x06,0x04,0x44,0x54,0x4B,0x52,0x46,0x81};//连接模块指令
//	//如果连接成功，回复fa,06,0a,04,44,54,4b,00,46,37,失败回复fa,02,0b,04,0b
//	uint8_t read_zigbee[9]={0xFC,0x06,0x05,0x44,0x54,0x4B,0x52,0x46,0x82};//读取zigbee模块参数指令
//	//成功回复fa 2b 0a 05 01 5a 76 14 01 00 01 aa bb 06 01 01 01 05 a6 01 00 12 4b 00 07 fc c9 e2 02 5a 76 14 01 0a 0b cc dd 04 01 01 01 05 a6 00 00 00 97
	uint8_t restart_zigbee[9]={0xFC,0x06,0x06,0x44,0x54,0x4B,0xAA,0xBB,0x50};
//	//如果重启成功返回fa 06 0a 06 44 54 4b aa bb 58 失败返回fa 06 0b 06 44 54 4b aa bb 59

	uint8_t write_zigbee[36];
	write_zigbee[0]=0xFC;write_zigbee[1]=0x21;write_zigbee[2]=0x07;
	write_zigbee[3]=0x01;write_zigbee[4]=0x01;
	write_zigbee[5]=CH_NUM;write_zigbee[6]=CH_NUM;
	//write_zigbee[5]=0x0b;write_zigbee[6]=0x0b;
	write_zigbee[7]=0x01;
	write_zigbee[8]=0x00;write_zigbee[9]=0x01;write_zigbee[10]=0xAA;write_zigbee[11]=0xBB;write_zigbee[12]=0x06;
	write_zigbee[13]=0x01;write_zigbee[14]=0x01;write_zigbee[15]=0x01;write_zigbee[16]=0x05;write_zigbee[17]=0xA6;
	write_zigbee[18]=0x01;write_zigbee[19]=0x02;write_zigbee[20]=0x01;
	write_zigbee[21]=CH_NUM;write_zigbee[22]=CH_NUM;
	//write_zigbee[21]=0x0b;write_zigbee[22]=0x0b;
	write_zigbee[23]=0x01;write_zigbee[24]=0x66;write_zigbee[25]=0x77;write_zigbee[26]=0xCC;write_zigbee[27]=0xDD;
	write_zigbee[28]=0x06;write_zigbee[29]=0x01;write_zigbee[30]=0x01;write_zigbee[31]=0x01;write_zigbee[32]=0x05;
	write_zigbee[33]=0xA6;write_zigbee[34]=0x01;
	for(i=0;i<35;i++)
	{
		write_zigbee[35]=write_zigbee[35]+write_zigbee[i];
	}

	
	//如果配置成功返回fa 01 0a 07 0c

 UartASendStr(write_zigbee,36);
	delay_ms(50);

 UartASendStr(restart_zigbee,9);
		delay_ms(50);
	
}

void zigbee_to_get_signal_intensity(void)
{
	uint8_t zigbee_to_get_signal_intensity[5] = {0x11,0x22,0x33,0x44,0x55};
	UartASendStr(zigbee_to_get_signal_intensity,5);
	delay_ms(50);
}

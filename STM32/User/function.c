#include "function.h"


  extern void uip_polling(void);
	extern uint8_t set_data[22];
	extern uint8_t USART_RX_BUF[25]; //DMA½ÓÊÕÊı¾İ»º´æÇø
	extern uint8_t USART_RX_BUF1[6];
	extern uint8_t EN[21];           //Ê¹ÄÜ²¦ÂëÊı×é
  extern uint8_t rx_len;           //Êı¾İ³¤¶È
	extern uint8_t CH_NUM_temp ;
 	uint8_t receive_data[21][50];    //×ö½âÎöÓÃµÄÊı×é£¬ÓÃÀ´´æ·ÅDMAÖ±½Ó½ÓÊÕµ½µÄÊı¾İ£¬receive_data[0][25]ÎªÎŞĞ§Êı¾İ
	uint8_t receive_signal_data[21][6];
  uint8_t  cnt;										 //¼ÆÊı±äÁ¿
	uint8_t CH_NUM = 0x0B;
	uint8_t slave_id_max = 0x0A;
	uint8_t receive_slave_data[21][26];//´«ËÍµ½PC¶ËºÍDPµÄÊı¾İ£
	uint8_t receive_slave_signal_data[21];
	uint8_t data_to_dp_1[2];
	uint8_t data_to_dp_2[2];
	uint8_t dp_offline_flag[21];
	uint8_t data_to_dp_temp[21][16];
	uint8_t offline_to_tcp[21];
	uint8_t tcp_server_tsta=0XFF;
	uint8_t signal_intensity[5];
//	uint8_t signal_intensity_flag = 0;
	uint8_t signal_data[21][6];
	/*****************offline_flag[i]=1   ÎªÍ¨ĞÅÕı³£           ÂÌµÆ 
										offline_flag[i] = 2 µôÏßºÍ²»Ê¹ÄÜ         ºìµÆ
										offline_flag[i] = 3 Í¨ĞÅ³öÏÖÖ¡´íÎó       À¶µÆ
										ÆäÖĞoffline_flag[0] Ã»ÓÃµ½´Ó1ÒÔºó¾ÍÊÇ¶ÔÓ¦µÄ´ÓÕ¾
	****************/


	
	uint8_t offline_flag[21] ;              //Êı¾İ±êÖ¾Î»offline_flag[0]ÎªÎŞĞ§Êı¾İ
	uint8_t offline_cnt[21] = {0};         //±êÖ¾Î»¼ÆÊıÊı×é
	uint8_t offline_flag_temp[21] = {0};   //±êÖ¾Î»µÄÖĞ¼ä±äÁ¿

	int test_get;
	
	uint8_t slave_id ;//´ÓÕ¾zigbee IDºÅ
	
	uint8_t slave_id_cnt;
		
  int a=0,b=0,c,d=2,i;

  uint8_t data_header[] = {0x55,0x55,0x00};//½ÓÊÕÊı¾İÖ¡Í·

  uint8_t data_end[] = {0x0d,0x0d};//½ÓÊÕÊı¾İÖ¡Î²

	uint32_t checksum = 0;//Ğ£ÑéºÍ
 
	uint16_t frame_to_slave[5] = {0x77,0x77,0x00,0x66,0x66};//Ïò´ÓÕ¾·¢ËÍÒªÊı¾İÖ¸Áî,Ö¡Í·Îª0x77 0x77,µÚÈıÎ»Îª´ÓÕ¾ID£¬Ö¡Î²Îª0x66 0x66
//	
//	uint8_t data_header_1[] = {0x11,0x11};//½ÓÊÕÊı¾İÖ¡Í·

//  uint8_t data_end_1[] = {0x22,0x22};//½ÓÊÕÊı¾İÖ¡Î²

/*--------------------------------------------------------------------
º¯ÊıÃû³Æ£ºunsigned char SumCheck(unsigned char data) 
º¯Êı¹¦ÄÜ£º×öĞ£ÑéºÍÓÃ
×¢ÒâÊÂÏî£º
ÌáÊ¾ËµÃ÷£º
Êä    Èë£º
·µ    »Ø£º
--------------------------------------------------------------------*/
	

unsigned char SumCheck(unsigned char data)		
{
	return ((data) / 16 + data % 16);
}


/*--------------------------------------------------------------------
º¯ÊıÃû³Æ£ºuint8_t Get_SumCheck(uint8_t x,uint8_t array[x][25]) 
º¯Êı¹¦ÄÜ£º°ÑÒ»¸ö¶şÎ¬Êı×éµÄxĞĞµÄÊı¾İÇóºÍ£¬Ö»Çó2-20
×¢ÒâÊÂÏî£º
ÌáÊ¾ËµÃ÷£º
Êä    Èë£º
·µ    »Ø£º
--------------------------------------------------------------------*/
	
uint8_t Get_SumCheck(uint8_t x,uint8_t array[x][26])
{
	uint8_t i,sum=array[x][2];
	for(i=4;i<22;i++)
	{
		sum += SumCheck(array[x][i]);
	}
	if(x>15)
	{
		sum=sum-0x0f; 
	}
	return sum;
}	
  
/*--------------------------------------------------------------------
º¯ÊıÃû³Æ£ºvoid scan_enable_receive(void)
º¯Êı¹¦ÄÜ£ºÉ¨ÃèÊ¹ÄÜ£¬²¢½âÎöÊı¾İ
×¢ÒâÊÂÏî£º
ÌáÊ¾ËµÃ÷£º
Êä    Èë£º
·µ    »Ø£º
--------------------------------------------------------------------*/
 
void scan_enable_receive(void)
{


for(slave_id=1;slave_id<21;slave_id++) //ÂÖÑ¯20¸ö´ÓÕ¾
{

//	if(EN[slave_id]==1 || slave_id == 10 || slave_id == 20)                  //ÅĞ¶ÏÊ¹ÄÜ²¦ÂëÊÇ·ñÊ¹ÄÜ£¬1£ºÊ¹ÄÜ£»0£ºÊ§ÄÜ
//	{
			
		frame_to_slave[2] = slave_id;         //Ïò´ÓÕ¾·¢ËÍµÄÖ¸ÁîµÄµÚÈı¸öÊı×éÔªËØÊÇ´ÓÕ¾ID
	  data_header[2] = slave_id;            //Ö¡Í·µÄµÚÈı¸öÊı¾İÎª´ÓÕ¾ID

	  if(EN[slave_id]==1)
		{
				UartASendStr_slow(frame_to_slave,5);  //Á¬ĞøÏò´ÓÕ¾·¢ËÍ10´ÎÒªÊıÖ¸Áî
	  }
		
	

		delay_ms(100);                        //ÑÓÊ±²»¿É¸Ä£¬150ºÏÊÊ

		
	
		DataParser *data_parser = parser_init(data_header, sizeof(data_header), data_end, sizeof(data_end), 25);//³õÊ¼»¯Ò»ÕëÊı¾İ
		

		for(i=0;i<25;i++)
		{
			
			receive_data[slave_id][i] = USART_RX_BUF[i];//½«DMAµÄÊı¾İ¿½±´µ½receive_dataµÄ¶şÎ¬Êı×éÖĞ
			
		}
		
		
		memset(USART_RX_BUF,0,sizeof(USART_RX_BUF));                   //½«USART_RX_BUFÖĞµÄÊı¾İÇåÁã
		
		delay_ms(5); //100ms ¿ªÊ¼µÄÊ±ºò

		
		for(i = 0; i<25; i++)                        //ÔÚreceive_dataÖĞµÄÊı¾İ½âÎöfor(i = 0; i<sizeof(receive_data); i++)
		{
			if(parser_put_data (data_parser, receive_data[slave_id][i]) == RESULT_TRUE )//½âÎö³É¹¦
			{
					
				  memset(receive_data[slave_id],0,sizeof(receive_data[slave_id])); //¶ÔÓ¦Êı×éÇåÁã
				

				
			
				for(cnt = 4;cnt<24;cnt++)
				{
					receive_slave_data[slave_id][cnt] = parser_get_data(data_parser, cnt-4);//È¡³ö½âÎö³É¹¦µÄÖĞ¼äµÄÊı
			
				}
				for(u8 v=0;v<16;v++)
				{
					data_to_dp_temp[slave_id][v] = receive_slave_data[slave_id][v+6];
				}
			
				
		  
				if(parser_get_data(data_parser, 19) == slave_id  )//×ö½øÒ»²½ÅĞ¶Ï£¬ÊÇ·ñ½ÓÊÕµ½µÄµÚ19¸öÊıÊÇ´ÓÕ¾ID
				{		
					offline_cnt[slave_id] = 0;                      //½«offline_cntÊı×éÇåÁã
					checksum = Get_SumCheck(slave_id,receive_slave_data);//¼ÆËã½âÎö³É¹¦µÄÊıµÄĞ£ÑéºÍ
				  test_get = parser_get_data(data_parser, 18);//È¡³ö½ÓÊÕµ½µÄµÚ18¸öÊıÎªÊı¾İµÄĞ£ÑéºÍ
					if(test_get == checksum)
					{
						offline_flag[slave_id] = 1;                  //Èç¹û½ÓÊÕµ½µÄÊı¾İµÄĞ£ÑéºÍºÍ¼ÆËãµÄĞ£ÑéºÍÒ»ÖÂ£¬Êı¾İÕıÈ·£¬ÖÃ±êÖ¾Î»
						dp_offline_flag[slave_id] = 1;
						offline_to_tcp[slave_id] = 1;
					}
				}
				else
				{
					offline_cnt[slave_id]++;                //Èç¹ûºÍ´ÓÕ¾ID²»ÏàµÈ£¬µôÏß¼ÆÊı±êÖ¾Î»++
				}	
				
			
			}
			  
			else
			{
				offline_flag_temp[slave_id] = 1;        //µôÏß±êÖ¾Î»ÖĞ¼ä±äÁ¿
				
			}

		}

		      
		
		
//			uip_polling();                            //ÍøÂçµÄ´«ËÍ³õÊ¼»¯µÈ
		
		if (slave_id == 10)
	 {
			data_to_dp_1[0] = 0x00 | (dp_offline_flag[1]<< 1) | dp_offline_flag[2];
		 
			data_to_dp_1[1] = (dp_offline_flag[3]<< 7)| (dp_offline_flag[4]<< 6)| (dp_offline_flag[5]<< 5)| 
		   (dp_offline_flag[6]<< 4)| (dp_offline_flag[7]<< 3)| (dp_offline_flag[8]<< 2)| (dp_offline_flag[9]<< 1)
		 | dp_offline_flag[10];
		 
		  Uart2ASendStr_slow (data_to_dp_1,2); 
		 for(u8 num1=1;num1<11;num1++)
		 {
				Uart2ASendStr_slow (data_to_dp_temp[num1],16); 
		 }
	 }
	 
	 
	    if (slave_id == 20)
	 {
			data_to_dp_2[0] = 0x80 | (dp_offline_flag[11]<< 1) | dp_offline_flag[12];
		 
			data_to_dp_2[1] = (dp_offline_flag[13]<< 7)| (dp_offline_flag[14]<< 6)| (dp_offline_flag[15]<< 5)| 
		   (dp_offline_flag[16]<< 4)| (dp_offline_flag[17]<< 3)| (dp_offline_flag[18]<< 2)| (dp_offline_flag[19]<< 1)
		 | dp_offline_flag[20];
		 
		  Uart2ASendStr_slow (data_to_dp_2,2); 
		 for(u8 num1=11;num1<21;num1++)
		 {
				Uart2ASendStr_slow (data_to_dp_temp[num1],16); 
		 }
	 }

		
		parser_release(data_parser);   //ÊÍ·Å½âÎöÆ÷£¬Ò»¶¨ÓÃÍêÒªÊÍ·Å
		if(offline_flag_temp[slave_id] == 1) //ÅĞ¶ÏÊÇ·ñÓĞ½ÓÊÜµ½ÕıÈ·µÄÊı¾İ
	  {
			offline_flag_temp[1] = 0;
			offline_cnt[slave_id]++;
			if(offline_cnt[slave_id]>10 && offline_cnt[slave_id]<=15)//5-10´Î±íÊ¾Ö¡´íÎó
			{
				offline_flag[slave_id] = 3;
				offline_to_tcp[slave_id] = 1;
			}
			if(offline_cnt[slave_id]>15)//´óÓÚ10´Î±íÊ¾µôÏß
			{
				offline_flag[slave_id] = 2;
				dp_offline_flag[slave_id] = 0;
				offline_to_tcp[slave_id] = 2;
			}
			
	  }

			
//  }	
	
	
	
if(EN[slave_id]==0)
	{
		offline_flag[slave_id] = 4;//Ê§ÄÜÃğµÆ
		dp_offline_flag[slave_id] = 0;
		offline_to_tcp[slave_id] = 3;
		for(u8 x=4;x<24;x++)
		{
			receive_slave_data[slave_id][x] = 0x00;
		}
	}

	 receive_slave_data[slave_id][0]=receive_slave_data[slave_id][1]=0x55;//½«Ö¡Í·0x55¸³Öµ¸øÇ°Á½¸öÊı
	 receive_slave_data[slave_id][2]=slave_id;                            //½«´ÓÕ¾ID¸³Öµ¸øµÚÈı¸öÊı
	 receive_slave_data[slave_id][3]=offline_to_tcp[slave_id];
	 receive_slave_data[slave_id][24]=receive_slave_data[slave_id][25]=0x0d;//½«Ö¡Í·¸³Öµ¸ø×îºóÁ½¸öÊı
	

  uip_polling();                   //ÍøÂçµÄ´«ËÍ³õÊ¼»¯µÈ
	

	MYDMA_Enable(DMA1_Channel5);//Ê¹ÄÜDMA
	
	
	IWDG_Feed();
	

		if(offline_flag[slave_id]==2)
		{
			for(u8 x=4;x<24;x++)
		 {
			 receive_slave_data[slave_id][x] = 0x00;
		 }
		}
	
}
}



#include "function.h"


  extern void uip_polling(void);
	extern uint8_t set_data[22];
	extern uint8_t USART_RX_BUF[25]; //DMA�������ݻ�����
	extern uint8_t USART_RX_BUF1[6];
	extern uint8_t EN[21];           //ʹ�ܲ�������
  extern uint8_t rx_len;           //���ݳ���
	extern uint8_t CH_NUM_temp ;
 	uint8_t receive_data[21][50];    //�������õ����飬�������DMAֱ�ӽ��յ������ݣ�receive_data[0][25]Ϊ��Ч����
	uint8_t receive_signal_data[21][6];
  uint8_t  cnt;										 //��������
	uint8_t CH_NUM = 0x0B;
	uint8_t slave_id_max = 0x0A;
	uint8_t receive_slave_data[21][26];//���͵�PC�˺�DP�����ݣ
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
	/*****************offline_flag[i]=1   Ϊͨ������           �̵� 
										offline_flag[i] = 2 ���ߺͲ�ʹ��         ���
										offline_flag[i] = 3 ͨ�ų���֡����       ����
										����offline_flag[0] û�õ���1�Ժ���Ƕ�Ӧ�Ĵ�վ
	****************/


	
	uint8_t offline_flag[21] ;              //���ݱ�־λoffline_flag[0]Ϊ��Ч����
	uint8_t offline_cnt[21] = {0};         //��־λ��������
	uint8_t offline_flag_temp[21] = {0};   //��־λ���м����

	int test_get;
	
	uint8_t slave_id ;//��վzigbee ID��
	
	uint8_t slave_id_cnt;
		
  int a=0,b=0,c,d=2,i;

  uint8_t data_header[] = {0x55,0x55,0x00};//��������֡ͷ

  uint8_t data_end[] = {0x0d,0x0d};//��������֡β

	uint32_t checksum = 0;//У���
 
	uint16_t frame_to_slave[5] = {0x77,0x77,0x00,0x66,0x66};//���վ����Ҫ����ָ��,֡ͷΪ0x77 0x77,����λΪ��վID��֡βΪ0x66 0x66
//	
//	uint8_t data_header_1[] = {0x11,0x11};//��������֡ͷ

//  uint8_t data_end_1[] = {0x22,0x22};//��������֡β

/*--------------------------------------------------------------------
�������ƣ�unsigned char SumCheck(unsigned char data) 
�������ܣ���У�����
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
	

unsigned char SumCheck(unsigned char data)		
{
	return ((data) / 16 + data % 16);
}


/*--------------------------------------------------------------------
�������ƣ�uint8_t Get_SumCheck(uint8_t x,uint8_t array[x][25]) 
�������ܣ���һ����ά�����x�е�������ͣ�ֻ��2-20
ע�����
��ʾ˵����
��    �룺
��    �أ�
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
�������ƣ�void scan_enable_receive(void)
�������ܣ�ɨ��ʹ�ܣ�����������
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
 
void scan_enable_receive(void)
{


for(slave_id=1;slave_id<21;slave_id++) //��ѯ20����վ
{

//	if(EN[slave_id]==1 || slave_id == 10 || slave_id == 20)                  //�ж�ʹ�ܲ����Ƿ�ʹ�ܣ�1��ʹ�ܣ�0��ʧ��
//	{
			
		frame_to_slave[2] = slave_id;         //���վ���͵�ָ��ĵ���������Ԫ���Ǵ�վID
	  data_header[2] = slave_id;            //֡ͷ�ĵ���������Ϊ��վID

	  if(EN[slave_id]==1)
		{
				UartASendStr_slow(frame_to_slave,5);  //�������վ����10��Ҫ��ָ��
	  }
		
	

		delay_ms(100);                        //��ʱ���ɸģ�150����

		
	
		DataParser *data_parser = parser_init(data_header, sizeof(data_header), data_end, sizeof(data_end), 25);//��ʼ��һ������
		

		for(i=0;i<25;i++)
		{
			
			receive_data[slave_id][i] = USART_RX_BUF[i];//��DMA�����ݿ�����receive_data�Ķ�ά������
			
		}
		
		
		memset(USART_RX_BUF,0,sizeof(USART_RX_BUF));                   //��USART_RX_BUF�е���������
		
		delay_ms(5); //100ms ��ʼ��ʱ��

		
		for(i = 0; i<25; i++)                        //��receive_data�е����ݽ���for(i = 0; i<sizeof(receive_data); i++)
		{
			if(parser_put_data (data_parser, receive_data[slave_id][i]) == RESULT_TRUE )//�����ɹ�
			{
					
				  memset(receive_data[slave_id],0,sizeof(receive_data[slave_id])); //��Ӧ��������
				

				
			
				for(cnt = 4;cnt<24;cnt++)
				{
					receive_slave_data[slave_id][cnt] = parser_get_data(data_parser, cnt-4);//ȡ�������ɹ����м����
			
				}
				for(u8 v=0;v<16;v++)
				{
					data_to_dp_temp[slave_id][v] = receive_slave_data[slave_id][v+6];
				}
			
				
		  
				if(parser_get_data(data_parser, 19) == slave_id  )//����һ���жϣ��Ƿ���յ��ĵ�19�����Ǵ�վID
				{		
					offline_cnt[slave_id] = 0;                      //��offline_cnt��������
					checksum = Get_SumCheck(slave_id,receive_slave_data);//��������ɹ�������У���
				  test_get = parser_get_data(data_parser, 18);//ȡ�����յ��ĵ�18����Ϊ���ݵ�У���
					if(test_get == checksum)
					{
						offline_flag[slave_id] = 1;                  //������յ������ݵ�У��ͺͼ����У���һ�£�������ȷ���ñ�־λ
						dp_offline_flag[slave_id] = 1;
						offline_to_tcp[slave_id] = 1;
					}
				}
				else
				{
					offline_cnt[slave_id]++;                //����ʹ�վID����ȣ����߼�����־λ++
				}	
				
			
			}
			  
			else
			{
				offline_flag_temp[slave_id] = 1;        //���߱�־λ�м����
				
			}

		}

		      
		
		
//			uip_polling();                            //����Ĵ��ͳ�ʼ����
		
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

		
		parser_release(data_parser);   //�ͷŽ�������һ������Ҫ�ͷ�
		if(offline_flag_temp[slave_id] == 1) //�ж��Ƿ��н��ܵ���ȷ������
	  {
			offline_flag_temp[1] = 0;
			offline_cnt[slave_id]++;
			if(offline_cnt[slave_id]>10 && offline_cnt[slave_id]<=15)//5-10�α�ʾ֡����
			{
				offline_flag[slave_id] = 3;
				offline_to_tcp[slave_id] = 1;
			}
			if(offline_cnt[slave_id]>15)//����10�α�ʾ����
			{
				offline_flag[slave_id] = 2;
				dp_offline_flag[slave_id] = 0;
				offline_to_tcp[slave_id] = 2;
			}
			
	  }

			
//  }	
	
	
	
if(EN[slave_id]==0)
	{
		offline_flag[slave_id] = 4;//ʧ�����
		dp_offline_flag[slave_id] = 0;
		offline_to_tcp[slave_id] = 3;
		for(u8 x=4;x<24;x++)
		{
			receive_slave_data[slave_id][x] = 0x00;
		}
	}

	 receive_slave_data[slave_id][0]=receive_slave_data[slave_id][1]=0x55;//��֡ͷ0x55��ֵ��ǰ������
	 receive_slave_data[slave_id][2]=slave_id;                            //����վID��ֵ����������
	 receive_slave_data[slave_id][3]=offline_to_tcp[slave_id];
	 receive_slave_data[slave_id][24]=receive_slave_data[slave_id][25]=0x0d;//��֡ͷ��ֵ�����������
	

  uip_polling();                   //����Ĵ��ͳ�ʼ����
	

	MYDMA_Enable(DMA1_Channel5);//ʹ��DMA
	
	
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



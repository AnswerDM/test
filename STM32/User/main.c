
  #include "main.h" 
	
	
  extern uint8_t CH_NUM_temp;
  extern uint8_t CH_NUM;
  uint8_t USART_RX_BUF[25];
  uint8_t USART_RX_BUF1[6]; 	
	uint8_t receive_dp_data[90];
	uint8_t receive_ip[4]={192,168,1,1};
//	extern uint8_t signal_intensity_flag;
	void uip_polling(void);	 												
	#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
		
	extern u8 tcp_server_tsta;
	extern uint8_t signal_intensity[5];
//	extern uint8_t signal_intensity_flag;
  uint8_t ii=0;
	
	
int main(void)
{

 	uip_ipaddr_t ipaddr;	
	uart2_init(38400);
	delay_init();
	gpio_init();
  uart4_init(38400);
	uart1_init(38400);
	TIM5_Int_Init(9999,7199);
	IWDG_Init(5,625);
  MYDMA_Config(DMA1_Channel5,(u32)&USART1->DR,(u32)USART_RX_BUF,75);	
	while(tapdev_init())	            //��ʼ��ENC28J60���� 0 ������ 1 ������
	{								   
	};
	uip_init();			                	//uIP��ʼ��	
	uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],receive_ip[3]);	//���ñ�������IP��ַ
	uip_sethostaddr(ipaddr);					    
	uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],1); 	//��������IP��ַ(��ʵ������·������IP��ַ)
	uip_setdraddr(ipaddr);						 
	uip_ipaddr(ipaddr,255,255,255,0);//������������
	uip_setnetmask(ipaddr);
	uip_listen(HTONS(55555));			      //����1200�˿�,����TCP Server

	while(1)
	{


		scan_enable_receive();

		ii++;
		if(ii<5)
		{		
				zigbee_configure();
				delay_ms(20);
		}
		else
		{
			ii=6;
		}

	}  
	
} 
void uip_polling(void)
{
	u8 i;
	static struct timer periodic_timer, arp_timer;
	static u8 timer_ok=0;	 
	if(timer_ok==0)//����ʼ��һ��
	{
		timer_ok = 1;
		timer_set(&periodic_timer,CLOCK_SECOND/2);  //����1��0.5��Ķ�ʱ�� 
//		timer_set(&periodic_timer,CLOCK_SECOND*5);
		timer_set(&arp_timer,CLOCK_SECOND*10);	   	//����1��10��Ķ�ʱ�� 
	}				 
	uip_len=tapdev_read();	//�������豸��ȡһ��IP��,�õ����ݳ���.uip_len��uip.c�ж���
	if(uip_len>0) 			//������
	{   
		//����IP���ݰ�(ֻ��У��ͨ����IP���Żᱻ����) 
		if(BUF->type == htons(UIP_ETHTYPE_IP))//�Ƿ���IP��? 
		{
			uip_arp_ipin();	//ȥ����̫��ͷ�ṹ������ARP��
			uip_input();   	//IP������
			//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ��� uip_len > 0
			//��Ҫ���͵�������uip_buf, ������uip_len  (����2��ȫ�ֱ���)		    
			if(uip_len>0)//��Ҫ��Ӧ����
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}else if (BUF->type==htons(UIP_ETHTYPE_ARP))//����arp����,�Ƿ���ARP�����?
		{
			uip_arp_arpin();
 			//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len(����2��ȫ�ֱ���)
 			if(uip_len>0)tapdev_send();//��Ҫ��������,��ͨ��tapdev_send����	 
		}
	}else if(timer_expired(&periodic_timer))	//0.5�붨ʱ����ʱ
	{
		timer_reset(&periodic_timer);		//��λ0.5�붨ʱ�� 
		//��������ÿ��TCP����, UIP_CONNSȱʡ��40��  
		for(i=0;i<UIP_CONNS;i++)
		{
			uip_periodic(i);	//����TCPͨ���¼�  
	 		//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len (����2��ȫ�ֱ���)
	 		if(uip_len>0)
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}
#if UIP_UDP	//UIP_UDP 
		//��������ÿ��UDP����, UIP_UDP_CONNSȱʡ��10��
		for(i=0;i<UIP_UDP_CONNS;i++)
		{
			uip_udp_periodic(i);	//����UDPͨ���¼�
	 		//������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ���uip_len>0
			//��Ҫ���͵�������uip_buf, ������uip_len (����2��ȫ�ֱ���)
			if(uip_len > 0)
			{
				uip_arp_out();//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();//�������ݵ���̫��
			}
		}
#endif 
		//ÿ��10�����1��ARP��ʱ������ ���ڶ���ARP����,ARP��10�����һ�Σ��ɵ���Ŀ�ᱻ����
		if(timer_expired(&arp_timer))
		{
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}





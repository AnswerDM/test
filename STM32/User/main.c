
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
	while(tapdev_init())	            //初始化ENC28J60错误 0 ：正常 1 ：错误
	{								   
	};
	uip_init();			                	//uIP初始化	
	uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],receive_ip[3]);	//设置本地设置IP地址
	uip_sethostaddr(ipaddr);					    
	uip_ipaddr(ipaddr,receive_ip[0],receive_ip[1],receive_ip[2],1); 	//设置网关IP地址(其实就是你路由器的IP地址)
	uip_setdraddr(ipaddr);						 
	uip_ipaddr(ipaddr,255,255,255,0);//设置网络掩码
	uip_setnetmask(ipaddr);
	uip_listen(HTONS(55555));			      //监听1200端口,用于TCP Server

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
	if(timer_ok==0)//仅初始化一次
	{
		timer_ok = 1;
		timer_set(&periodic_timer,CLOCK_SECOND/2);  //创建1个0.5秒的定时器 
//		timer_set(&periodic_timer,CLOCK_SECOND*5);
		timer_set(&arp_timer,CLOCK_SECOND*10);	   	//创建1个10秒的定时器 
	}				 
	uip_len=tapdev_read();	//从网络设备读取一个IP包,得到数据长度.uip_len在uip.c中定义
	if(uip_len>0) 			//有数据
	{   
		//处理IP数据包(只有校验通过的IP包才会被接收) 
		if(BUF->type == htons(UIP_ETHTYPE_IP))//是否是IP包? 
		{
			uip_arp_ipin();	//去除以太网头结构，更新ARP表
			uip_input();   	//IP包处理
			//当上面的函数执行后，如果需要发送数据，则全局变量 uip_len > 0
			//需要发送的数据在uip_buf, 长度是uip_len  (这是2个全局变量)		    
			if(uip_len>0)//需要回应数据
			{
				uip_arp_out();//加以太网头结构，在主动连接时可能要构造ARP请求
				tapdev_send();//发送数据到以太网
			}
		}else if (BUF->type==htons(UIP_ETHTYPE_ARP))//处理arp报文,是否是ARP请求包?
		{
			uip_arp_arpin();
 			//当上面的函数执行后，如果需要发送数据，则全局变量uip_len>0
			//需要发送的数据在uip_buf, 长度是uip_len(这是2个全局变量)
 			if(uip_len>0)tapdev_send();//需要发送数据,则通过tapdev_send发送	 
		}
	}else if(timer_expired(&periodic_timer))	//0.5秒定时器超时
	{
		timer_reset(&periodic_timer);		//复位0.5秒定时器 
		//轮流处理每个TCP连接, UIP_CONNS缺省是40个  
		for(i=0;i<UIP_CONNS;i++)
		{
			uip_periodic(i);	//处理TCP通信事件  
	 		//当上面的函数执行后，如果需要发送数据，则全局变量uip_len>0
			//需要发送的数据在uip_buf, 长度是uip_len (这是2个全局变量)
	 		if(uip_len>0)
			{
				uip_arp_out();//加以太网头结构，在主动连接时可能要构造ARP请求
				tapdev_send();//发送数据到以太网
			}
		}
#if UIP_UDP	//UIP_UDP 
		//轮流处理每个UDP连接, UIP_UDP_CONNS缺省是10个
		for(i=0;i<UIP_UDP_CONNS;i++)
		{
			uip_udp_periodic(i);	//处理UDP通信事件
	 		//当上面的函数执行后，如果需要发送数据，则全局变量uip_len>0
			//需要发送的数据在uip_buf, 长度是uip_len (这是2个全局变量)
			if(uip_len > 0)
			{
				uip_arp_out();//加以太网头结构，在主动连接时可能要构造ARP请求
				tapdev_send();//发送数据到以太网
			}
		}
#endif 
		//每隔10秒调用1次ARP定时器函数 用于定期ARP处理,ARP表10秒更新一次，旧的条目会被抛弃
		if(timer_expired(&arp_timer))
		{
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}





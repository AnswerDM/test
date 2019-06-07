#include "usart.h"



//----- (08004E70) --------------------------------------------------------
int speed_level = 0;
int send_speed_level = 0;
int power_level = 0;
int send_power_level = 0;
unsigned char data_buf[14]={0};
unsigned char send_buf[30]={0};

void Uartx_SendData(USART_TypeDef* USARTx, uint8_t data)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx,data);
}

void Uartx_SendnBuf(USART_TypeDef* USARTx, uint8_t *buf, uint16_t len)
{
    while(len--)
    {
			Uartx_SendData(USARTx,*buf++);
    }
}

void usart_send()
{//ͨѶ����
	int i = 0;
	int j = 1;
	send_buf[0]=0xFA;
	for(i=0;i<2;i++)
	{
			send_buf[j]=data_buf[i];
			j++;
	}
	Uartx_SendnBuf(USART2, send_buf, j);
}
int lk_remove_flag_mpu2 = 1;//�������β�̤����Far
int lk_remove_flag_mpu3 = 1;//�������β�̤����Near
u16 v00; 
//----- (08004BAC) --------------------------------------------------------
void get_usart2()
{//����USART2����
	
	v00 = USART2->DR;
	
	if(v00==0)
	{
		time_out_usart2_cnt_192++;
		if(time_out_usart2_cnt_192>=100)
		{
			time_out_usart2_cnt_192=100;
			//���������й���
			flag_mpu2_online1_174 = 0;
			error_1D0 = 1;//����һ�ั�����ӹ���
//			TIM1->BDTR &= 0x7FFFu;//�ر�pwm
			motor_direction=0;
		}
	}
	else
	{
		//��������
		time_out_usart2_cnt_192 = 0;
		error_1D0=0;
		
		
    if ( v00 == 0x100 )
    {
			
			if(rec_usart2_buf_18B[5]==0x58)
			{
				motor_direction = 0;
			}
			else if(rec_usart2_buf_18B[5]<=6)
			{
				motor_direction = rec_usart2_buf_18B[5];
			}
			else
			{
				//motor_direction = 0;
			}
			
//			rec_usart2_buf_18B[0] = 0;
//			rec_usart2_buf_18B[1] = 0;
//			rec_usart2_buf_18B[2] = 0;
//			rec_usart2_buf_18B[3] = 0;
//			rec_usart2_buf_18B[4] = 0;
//			rec_usart2_buf_18B[5] = 0;
			
      get_usart2_cnt = 0;
    }
    else 
		{
			rec_usart2_buf_18B[get_usart2_cnt] = v00;
			get_usart2_cnt++;
			if(get_usart2_cnt>=6)get_usart2_cnt=6;
		}	
	}
	
	




////	float fbak;
// // s16 v12;

//	
//  if ( USART2->SR & 0x20 )
//  {
//    v0 = USART2->DR;
//    ++get_usart2_cnt;
//    if ( v0 & 0x100 )
//    {
//      if ( get_usart2_cnt == 6 )
//      {
//				
//				if( rec_usart2_buf_18B[5]<=6 )
//				{
//					motor_direction = rec_usart2_buf_18B[5]; //1ǰ�M 2���� 3���D 4���D
//				}
//								
//				
//				if( lk_remove_flag_mpu2 ==1  )
//				{
//					flag_mpu2_online2_1D2 = 1;
//					cycle_cnt_usart2_18A = 0;
//				}
//      }
//      get_usart2_cnt = 0;
//    }
//    if ( (signed int)get_usart2_cnt <= 5 )
//      rec_usart2_buf_18B[get_usart2_cnt] = v0;
//    time_out_usart2_cnt_192 = 0;
//  }
//  else if ( (signed int)time_out_usart2_cnt_192 >= 1888 )
//  {//���������й���
//    flag_mpu2_online1_174 = 0;
//    error_1D0 = 1;//����һ�ั�����ӹ���
//    TIM1->BDTR &= 0x7FFFu;//�ر�pwm
//    TIM8->BDTR &= 0x7FFFu;//�ر�pwm
//  }
//  else
//  {
//    ++time_out_usart2_cnt_192;
//  }
}



//----- (08004D14) --------------------------------------------------------
void get_usart3()
{
	u16 v0; 
//	float fbak;
//  s16 v12; 

  if ( USART3->SR & 0x20 )
  {
    v0 = USART3->DR;
    ++get_usart3_cnt;
    if ( v0 & 0x100 )
    {//��ʼ��ַ
      if ( get_usart3_cnt == 6 )
      {
				if(rec_usart3_buf_19E[5]<=6)
				{
					motor_direction = rec_usart3_buf_19E[5]; //1ǰ�M 2���� 3���D 4���D
				}

				if( lk_remove_flag_mpu3 ==1  )
				{
					flag_mpu3_online2_1D3 = 1;
					cycle_cnt_usart3_19D = 0;
				}
      }
      get_usart3_cnt = 0;
    }
    if ( (signed int)get_usart3_cnt <= 5 )
      rec_usart3_buf_19E[get_usart3_cnt] = v0;
    time_out_usart3_cnt_1A4 = 0;
  }
  else if ( (signed int)time_out_usart3_cnt_1A4 >= 1888 )
  {
    flag_mpu3_online1_175 = 0;
    error_1D1 = 1;//����һ�ั�����ӹ���
//    TIM1->BDTR &= 0x7FFFu;//�ر�pwm
    TIM8->BDTR &= 0x7FFFu;//�ر�pwm
  }
  else
  {
    ++time_out_usart3_cnt_1A4;
  }
}
//int stop_str = 3;
int start_str = 0;
int start_str_his = 0;
int count_start_ms = 0;
int count_start_s  = 4;
int count_usart2_rec = 0;
//----- (08005A40) --------------------------------------------------------
void check_vice()
{//��鸱��
  //stop_str = (GPIOC->IDR >> 7) & 3;
	
	start_str = (GPIOC->IDR>> 9) & 1;
	
	count_start_ms++;
	if(count_start_ms>=500)
	{
		count_start_ms = 0;
		count_start_s++;
	}
	if(count_start_s>=4)
	{
		count_start_s = 4;
	}

	
	if(start_str==1&&start_str_his==0)
	{
		count_start_ms = 0;
		count_start_s = 0;
	}
	start_str_his = start_str;
	
	count_usart2_rec++;
	if(count_usart2_rec>=100)
	{
		count_usart2_rec = 100;
		error_1D1 = 1;
	}
	
	if ( (error_motor1_pos_flag_0D2)//����һ������������
			|| (error_1D1)//����һ�ั�����ӹ���
			|| (motor1_error_el_vol_flag_0BF)//����һ�ྲ̬��������
			|| (error_motor_line_05B))//��������ж�·
		//	|| (error_vol_flag_030))//��ص�ѹ����
		//	||(stop_str!=3))
		{//�й���
			TIM1->BDTR &= 0x7FFFu;//�ر�pwm
		}
		else
		{//û����������
			//flag_mpu2_ok_211 = 1;
			if(val1_final_xiepo==0)
			{
				TIM1->BDTR &= 0x7FFFu;//�ر�pwm
				flag_motor1_status_20B=0;
			}
			else if ( flag_motor1_status_20B==0 )//�ر���tim1 ���¿���
			{
				TIM1->BDTR |= 0x8000u;
				flag_motor1_status_20B = 1;
			}
			
			//error_vice_20D = 0;
			//error_angle_186 = 0;
		}
		
//	if(stop_str!=3)//ɲ��
//	{
//		TIM1->BDTR &= 0x7FFFu;//�ر�pwm
//		flag_motor1_status_20B = 0;
//		val1_final_xiepo = 0;
//	}
	
	
	if(count_start_s>=1)
	{
//		TIM1->BDTR &= 0x7FFFu;//�ر�pwm
//		flag_motor1_status_20B = 0;
//		val1_final_xiepo = 0;
	}
	else
	{
		//flag_motor1_status_20B = 1;
	}
		
}

//----- (080051AE) --------------------------------------------------------
void get_motor_state_to_usart()
{//��ȡ��ǰ״̬���͸�С��
  if ( flash_para4_050 == flash_para3_054 )
  {
    if ( ((signed int)moter2_roll_time_15E <= 1350) || ((signed int)moter1_roll_time_0EC <= 1350) )
    {//������������ʱ�� С
      if ( motor1_dir_flag_0EE == motor2_dir_flag_160 )
      {
        if ( motor1_dir_flag_0EE == motor2_dir_flag_160 )
        {
					if(moter2_roll_time_15E < 1350 ) motor2_state_1_176 = 1;
					else motor2_state_1_176 = 0;
					if(moter1_roll_time_0EC < 1350 ) motor1_state_1_177 = 1;
					else motor1_state_1_177 = 0;
        }
        else
        {
          motor2_state_1_176 = 0;
          motor1_state_1_177 = 0;
        }
      }
			else
			{
				if( moter2_roll_time_15E > moter1_roll_time_0EC + 88 )
				{
          motor2_state_1_176 = 1;
          motor1_state_1_177 = 0;
					//loc_800528E
				}	
				else if ( moter1_roll_time_0EC > moter2_roll_time_15E + 88 )
        {
          motor2_state_1_176 = 0;
          motor1_state_1_177 = 1;
        }
        else
        {
          motor2_state_1_176 = 0;
          motor1_state_1_177 = 0;
        }
			}
    }
    else
    {
      motor2_state_1_176 = 0;
      motor1_state_1_177 = 0;
    }
    if ( flag_charging_085 )//����־λ
    {//�����
      motor_state_vol_1BB = 0;
      if ( flag_charging_mpu_online_20C )
      {//���ʱ ����̤��
        motor_state_7_17A = 1;//���������
        motor_state_4_1BA = 0;
      }
      else
      {//�������
        motor_state_7_17A = 0;//�������
        if ( (signed int)vol_val_032 >= 1634 )
          motor_state_4_1BA = 1;
        else
          motor_state_4_1BA ^= 1u;//��λ���
      }
    }
    else
    {//�ǳ��״̬
      motor_state_4_1BA = 0;
      if ( flag_vol_lower_031 )
      {//��ѹ����
        motor_state_7_17A = 1;
        motor_state_vol_1BB = 0;//��ѹ״̬
      }
      else
      {
        motor_state_7_17A = 0;//��ѹ��״̬
        if ( flag_vol_low_02B )
        {//��ѹ��
          if ( flag_vol_low_02B )
            motor_state_vol_1BB ^= 1u;
          else
            motor_state_vol_1BB = 1;
        }
        else
        {
          motor_state_vol_1BB = 1;
        }
      }
    }
    motor_state_vol_bak_179 = motor_state_vol_1BB;
    motor_state_4_bak_178 = motor_state_4_1BA;
    motor_state_5_17D = 0;
    motor_state_6_17C = 0;
    if ( error_vice_20D )
    {
      motor_state_5_17D = 1;
    }
    else if ( flag_motor1_status_20B || flag_motor2_status_20A )
    {
      motor_state_6_17C = 1;
    }
  }
}




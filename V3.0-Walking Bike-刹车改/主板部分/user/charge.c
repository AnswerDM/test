#include "charge.h"
int lk = 0;
//----- (080014B4) --------------------------------------------------------
void get_vol()
{//��ص�ѹ
  u16 val; 
  u8 i; 

	//���2�ĵ�ѹ
  val = 0;
  for ( i = 0; i < 4; i = (u8)(i + 1) )
    val = (u16)(bet_vol_buf_068[i] + val);//��ص�ѹ����
  vol_val_032 = val >> 2;//��ѹֵƽ��
	
	power_level = (vol_val_032*100/1270)/3*3;
	if(power_level>=100)power_level=100;
	
  if ( (signed int)vol_val_032 <= 720 )   //��ص�ѹ����
  {//������Χ �ر�pwm
    error_vol_flag_030 = 1;//��ص�ѹ����
		lk = 1;
    TIM1->BDTR &= 0x7FFFu;//�ر�pwm
  }
	else
	{
		//error_vol_flag_030 = 0;
	}
	
	//��ѹ���
	//motor1_speed_0C4:VCCL�ĵ�ѹʵʱֵ���ѹ�궨ֵ�Ĳ�ֵ
	//motor2_speed_0BC:VCCR�ĵ�ѹʵʱֵ���ѹ�궨ֵ�Ĳ�ֵ
	//vol_val_bak_02C:ÿ80��ѭ������һ�ε�ص�ѹֵ ���Ͳ���Ƶ��
	//vol_val_032:��ص�ѹƽ��ֵ
//  if ( (((motor1_speed_0C4 + motor2_speed_0BC) > 0)  //VCCL��VCCR�ĵ�ѹֵ��ֵ 
//	 	&&  ((motor1_speed_0C4 + motor2_speed_0BC) < 105))//
//		&&   (vol_val_bak_02C > (signed int)vol_val_032) )
//  {
//		//��ص�����ͣ���� ������µ�ǰ�ĵ�ص�ѹֵ
//    if ( (signed int)cycle_vol_cnt1_02E >= 80 )
//    {
//      cycle_vol_cnt1_02E = 0;//�ƴ�
//      vol_val_bak_02C = vol_val_032;
//    }
//    else
//    {
//      ++cycle_vol_cnt1_02E;
//    }
//  }
//	//��ѹ��
//	if(vol_val_bak_02C < 1373)
//	{
//		flag_vol_low_02B = 1;//��ѹ��
//	}
//	else
//	{
//		flag_vol_low_02B = 0;
//	}
//	
//	if(vol_val_bak_02C <= 1360)
//	{
//		flag_vol_lower_031 = 1;//��ѹ����
//	}
//	else
//	{
//		flag_vol_lower_031 = 0;
//	}
	
//  if ( flash_para5_04E != flash_para2_052 )
//    flag_vol_lower_031 = 1;
//  if(((signed int)moter1_roll_time_0EC < 1350) 
//			&& ((signed int)moter2_roll_time_15E < 1350) 
//			&& (flag_vol_lower_031 == 1)) 
//	{
//		flag_unknown_1_02A = 1;
//	}
//	else flag_unknown_1_02A = 0;
  
}


//----- (08002DBC) --------------------------------------------------------
void get_charger_status()
{//��ȡ�����״̬
  if ( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) )
  {
    flag_charge_cnt1_0A6 = 0;//��������ѭ������
    if ( (signed int)flag_charge_cnt2_0A7 >= 10 )
    {
      flag_charging_085 = 0;//����־λ
    }
    else
    {
      ++flag_charge_cnt2_0A7;
    }
  }
  else
  {
    flag_charge_cnt2_0A7 = 0;
    if ( (signed int)flag_charge_cnt1_0A6 >= 10 )
    {
      flag_charging_085 = 1;//����־λ
    }
    else
    {
      ++flag_charge_cnt1_0A6;
    }
  }
}

//----- (08002B82) --------------------------------------------------------
void check_boot()
{//���ؼ��
	int vol; 
  signed int i; 
  signed int j;

  vol = (u32)(boot_vol_buf_07C[3] + boot_vol_buf_07C[2] + boot_vol_buf_07C[1] + boot_vol_buf_07C[0]) >> 2;
  
	if ( (signed int)cycle_vol_cnt2_0A4 < 1000 )
    ++cycle_vol_cnt2_0A4;
  if ( flag_dormancy_098 )
  {//û������
		/*****************����ѹ******************/
    if ( vol <= 1240 )
    {
			//��ѹ��
      if ( (signed int)cycle_vol_cnt_09A > 6 )
      {
        if ( (signed int)cycle_vol_cnt2_0A4 >= 800 )
        {//��ѹ���ѭ���ƴ�
					//ʱ�䳤�ػ�
          buzz_type_0B2 = 1;
          for ( i = 0; i < 200; i = (u16)(i + 1) )
          {
            while ( !time1_ok_05A )
              ;
            time1_ok_05A = 0;
          }
          buzz_type_0B2 = 0;
          GPIO_ResetBits(GPIOA, 32);//�ػ�
        }
        else
        {
          flag_unknown_7_186 ^= 1u;
          flag_unknown_8_188 = 1;
          cycle_vol_cnt2_0A4 = 800;
        }
      }
      cycle_vol_cnt_09A = 0;
    }
    else if ( (signed int)cycle_vol_cnt_09A < 500 )
    {
      ++cycle_vol_cnt_09A;
    }
		/*****************���ϼ��************************/
    if ( (flag_motor1_move_0EA != 1) || (flag_motor2_move_15C != 1) )
    {
      cycle_error_cnt_0A0 = 0;
    }
    else if ( flash_para7_048
			|| (error_vol_flag_030)
			|| error_motor1_pos_flag_0D2
			|| error_motor2_pos_flag_144
			|| error_motor_line_05B
			|| motor2_error_el_vol_flag_0B6
			|| motor1_error_el_vol_flag_0BF//����һ�ྲ̬��������
			|| error_1D0
			|| error_1D1
			|| ((!flag_motor1_status_20B) && (!flag_motor2_status_20A)) )
    {//����
      if ( cycle_error_cnt_0A0 >= 0x1AD274u )//���ϼ��ʱ�� 
      {//����ѭ���ƴ�
        if ( !flag_unknown_2_086 )
        {
					//���ϱ���
          buzz_type_0B2 = 1;
          for ( j = 0; j < 200; j = (u16)(j + 1) )
          {
            while ( !time1_ok_05A )
              ;
            time1_ok_05A = 0;
          }
          buzz_type_0B2 = 0;
        }
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);//�ػ�
      }
      else
      {
        cycle_error_cnt_0A0++;
      }
    }
    else
    {
      cycle_error_cnt_0A0 = 0;
    }
  }
  else
	{
		//����
		if ( vol > 1240 )
		{
			//��ѹ��
			if ( cycle_vol_cnt3_high_09C < 1500 )
			{
				++cycle_vol_cnt3_high_09C;
			}
			else
			{
				flag_dormancy_reset_039 = 1;//������־
			}
		}
		else if ( vol <= 1240 )
		{//��ѹ��
			cycle_vol_cnt3_high_09C = 0;
			flag_dormancy_098 = 1;//��ʼ����ѹ��־
			flag_vol_low_03A = 1;
		}
	}
}



#include "led.h"



//----- (080023F8) --------------------------------------------------------
void led1_ctrl()
{//����led��˸Ƶ�� ����ָʾ
  u16 cnt=0; 
	
  if ( error_1D0 )
  {//����һ�ั�����ӹ���
    cnt = 7;
  }
  else if ( error_1D1 )
  {//����һ�ั�����ӹ���
    cnt = 8;
  }
  else if ( motor1_error_el_vol_flag_0BF )//����һ�ྲ̬��������
  {
    cnt = 1;
  }
  else if ( motor2_error_el_vol_flag_0B6 )//����һ�ྲ̬��������
  {
    cnt = 2;
  }
  else if ( error_motor_line_05B )//��������ж�·
  {
    cnt = 3;
  }
  else if ( error_motor1_pos_flag_0D2 )//����һ������������
  {
    cnt = 4;
  }
  else if ( error_motor2_pos_flag_144 )//����һ������������
  {
    cnt = 5;
  }
  else if ( error_vol_flag_030 )//��ص�ѹ����
  {
    cnt = 6;
  }
  else if ( error_angle_186 )
  {//��̬��Ƕȹ���
    cnt = 9;
  }
  else
  {
    cnt = 0;//����˸ �޴���
  }
  if ( cnt )
  {
    if ( !led1_on_089 )
    {
      ++led1_cnt_088;//����
      if ( led1_cnt_088 > cnt )
        led1_cnt_088 = 0;
    }
    if ( led1_cnt_088 >= cnt )
    {
      GPIO_ResetBits(GPIOB, 4);//LED
    }
    else if ( led1_on_089 )
    {
      GPIO_SetBits(GPIOB, 4);//LED
    }
    else
    {
      GPIO_ResetBits(GPIOB, 4);//LED
    }
    led1_on_089 ^= 1u;
  }
  else
  {
    GPIO_ResetBits(GPIOB, 4);//LED
  }
}

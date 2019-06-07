#include "led.h"



//----- (080023F8) --------------------------------------------------------
void led1_ctrl()
{//控制led闪烁频率 故障指示
  u16 cnt=0; 
	
  if ( error_1D0 )
  {//长线一侧副班连接故障
    cnt = 7;
  }
  else if ( error_1D1 )
  {//短线一侧副班连接故障
    cnt = 8;
  }
  else if ( motor1_error_el_vol_flag_0BF )//短线一侧静态电流故障
  {
    cnt = 1;
  }
  else if ( motor2_error_el_vol_flag_0B6 )//长线一侧静态电流故障
  {
    cnt = 2;
  }
  else if ( error_motor_line_05B )//电机相线有短路
  {
    cnt = 3;
  }
  else if ( error_motor1_pos_flag_0D2 )//短线一侧电机霍尔故障
  {
    cnt = 4;
  }
  else if ( error_motor2_pos_flag_144 )//长线一侧电机霍尔故障
  {
    cnt = 5;
  }
  else if ( error_vol_flag_030 )//电池电压过低
  {
    cnt = 6;
  }
  else if ( error_angle_186 )
  {//姿态板角度过大
    cnt = 9;
  }
  else
  {
    cnt = 0;//不闪烁 无错误
  }
  if ( cnt )
  {
    if ( !led1_on_089 )
    {
      ++led1_cnt_088;//计数
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

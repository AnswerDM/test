//#include "stm32f10x.h"
#include "main.h"
#include "pid.h"


float KP_test = 8.0;
float KI_test = 120.0;
float KD_test = 80.0;

int speed_set_test = 800;//16000;

int val1_final = -100;
int val2_final = 0;

int count_speed_time = 0;

int motor_direction = 0;

int val1_final_open = 0;
int val1_final_xiepo = 0;
u16 roll_time = 0;

//----- (08001318) --------------------------------------------------------
int main()
{
  s16 val1; // r5@30
  s16 val2; // r0@30
	init();
	self_checking();//自检
	while ( 1 )
	{
//		if ( TIM1->SR & 0x80 )//状态寄存器
//		{
//			error_motor_line_05B = 1;//电机相线有短路
//			TIM1->SR = 0;
		
//			TIM1->BDTR &= 0x7FFFu;//关闭pwm
//		}
		if ( get_adc_ok_0B4 )//每 64*3 = 192 us  get_adc_ok_0B4  置位
		{//获取adc 4次完成
			vlot_cmp1_regulation();//电机速度调节 电池电压低的时候
			get_adc_ok_0B4 = 0;
		}
		
		if ( time1_ok_05A )//每  64*16 = 1024 us 将近1ms  time1_ok_05A  置位
		{
			time1_ok_05A = 0;
			roll_time = 16872-moter1_roll_time_0EC;
			speed_level = (roll_time - 16500)/6*6;
			if(speed_level<=0)speed_level=0;
			else if(speed_level>=126)speed_level=126;
			
			data_buf[0] = power_level;
			data_buf[1] = speed_level;
			usart_send();//和副板通讯 发送状态
			++get_vol_cnt_028;//获取次数
			if ( (signed int)get_vol_cnt_028 < 2 )
			{
//        //PID参数调节				
//				sPID_Near.v_Kp = KP_test;       
//        sPID_Near.v_Ki = KI_test;    
//        sPID_Near.v_Kd = KD_test;   
				
//				//闭环
//				if(motor1_dir_flag_0EE==1)
//				{
//					sPID_Near.vi_FeedBack = 16872-moter1_roll_time_0EC;
//				}
//				else
//				{
//					sPID_Near.vi_FeedBack = 0;
//				}
//				
//				if(motor_direction==0)
//				{
//					speed_set_test = 0;
//				}
//				else if(motor_direction==1)
//				{
//					speed_set_test = 16000;
//				}
//				else if(motor_direction==2)
//				{
//					speed_set_test = 16500;
//				}
//				else if(motor_direction==3)
//				{
//					speed_set_test = 16580;
//				}
//				else if(motor_direction==4)
//				{
//					speed_set_test = 16700;
//				}
//				else if(motor_direction==5)
//				{
//					speed_set_test = 16750;
//				}
//				else if(motor_direction==6)
//				{
//					speed_set_test = 16780;
//				}
//				else
//				{
//					speed_set_test = 0;
//				}
//				
//				
//				sPID_Near.vi_Ref=speed_set_test;
//				val1_final=v_PIDCalc(&sPID_Near);
//				if(speed_set_test==0)
//				{
//					sPID_Near.vl_PreU=0;
//					val1_final=0;
//				}
//				//v_PIDCalc(&sPID_Near);
//				if(val1_final<0)val1_final=0;
				
				motor_direction = buf_rec_usart_2[0];
				if(motor_direction==0){val1_final_open=0;}
				else if(motor_direction==1)val1_final_open=750;//420;
				else if(motor_direction==2)val1_final_open=900;//550;
				else if(motor_direction==3)val1_final_open=1000;//720;
//				else if(motor_direction==4)val1_final_open=850;
//				else if(motor_direction==5)val1_final_open=850;
//				else if(motor_direction==6)val1_final_open=850;
//				else if(motor_direction==1)val1_final_open=500;
//				else if(motor_direction==2)val1_final_open=600;
//				else if(motor_direction==3)val1_final_open=700;
//				else if(motor_direction==4)val1_final_open=800;
//				else if(motor_direction==5)val1_final_open=900;
//				else if(motor_direction==6)val1_final_open=1023;
				
				
				if(val1_final_open > val1_final_xiepo)
				{
					val1_final_xiepo += 5;
					if(val1_final_xiepo>val1_final_open)val1_final_xiepo=val1_final_open;
				} 
				else
				{
					val1_final_xiepo = val1_final_open;
				}
				
				//para_motor2_attitude_0BA = val2_final;
				//para_motor1_attitude_0C2 = -1*val1_final;//板子相反 角度一正一副
				para_motor1_attitude_0C2 = val1_final_xiepo;//板子相反 角度一正一副
				//para_motor1_attitude_0C2 = 0;//板子相反 角度一正一副
				check_vice();//检查副板
			}
			else
			{
				get_vol_cnt_028 = 0;
				
				get_vol();//电池检测
			}
		}
	}
}

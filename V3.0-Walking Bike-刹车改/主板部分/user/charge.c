#include "charge.h"
int lk = 0;
//----- (080014B4) --------------------------------------------------------
void get_vol()
{//电池电压
  u16 val; 
  u8 i; 

	//电机2的电压
  val = 0;
  for ( i = 0; i < 4; i = (u8)(i + 1) )
    val = (u16)(bet_vol_buf_068[i] + val);//电池电压采样
  vol_val_032 = val >> 2;//电压值平均
	
	power_level = (vol_val_032*100/1270)/3*3;
	if(power_level>=100)power_level=100;
	
  if ( (signed int)vol_val_032 <= 720 )   //电池电压过低
  {//超出范围 关闭pwm
    error_vol_flag_030 = 1;//电池电压过低
		lk = 1;
    TIM1->BDTR &= 0x7FFFu;//关闭pwm
  }
	else
	{
		//error_vol_flag_030 = 0;
	}
	
	//电压检测
	//motor1_speed_0C4:VCCL的电压实时值与电压标定值的差值
	//motor2_speed_0BC:VCCR的电压实时值与电压标定值的差值
	//vol_val_bak_02C:每80个循环更新一次电池电压值 降低采样频率
	//vol_val_032:电池电压平均值
//  if ( (((motor1_speed_0C4 + motor2_speed_0BC) > 0)  //VCCL与VCCR的电压值合值 
//	 	&&  ((motor1_speed_0C4 + motor2_speed_0BC) < 105))//
//		&&   (vol_val_bak_02C > (signed int)vol_val_032) )
//  {
//		//电池电量不停消耗 这里更新当前的电池电压值
//    if ( (signed int)cycle_vol_cnt1_02E >= 80 )
//    {
//      cycle_vol_cnt1_02E = 0;//计次
//      vol_val_bak_02C = vol_val_032;
//    }
//    else
//    {
//      ++cycle_vol_cnt1_02E;
//    }
//  }
//	//电压低
//	if(vol_val_bak_02C < 1373)
//	{
//		flag_vol_low_02B = 1;//电压低
//	}
//	else
//	{
//		flag_vol_low_02B = 0;
//	}
//	
//	if(vol_val_bak_02C <= 1360)
//	{
//		flag_vol_lower_031 = 1;//电压更低
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
{//获取充电器状态
  if ( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) )
  {
    flag_charge_cnt1_0A6 = 0;//充电器检测循环计数
    if ( (signed int)flag_charge_cnt2_0A7 >= 10 )
    {
      flag_charging_085 = 0;//充电标志位
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
      flag_charging_085 = 1;//充电标志位
    }
    else
    {
      ++flag_charge_cnt1_0A6;
    }
  }
}

//----- (08002B82) --------------------------------------------------------
void check_boot()
{//开关检测
	int vol; 
  signed int i; 
  signed int j;

  vol = (u32)(boot_vol_buf_07C[3] + boot_vol_buf_07C[2] + boot_vol_buf_07C[1] + boot_vol_buf_07C[0]) >> 2;
  
	if ( (signed int)cycle_vol_cnt2_0A4 < 1000 )
    ++cycle_vol_cnt2_0A4;
  if ( flag_dormancy_098 )
  {//没有休眠
		/*****************检测电压******************/
    if ( vol <= 1240 )
    {
			//电压低
      if ( (signed int)cycle_vol_cnt_09A > 6 )
      {
        if ( (signed int)cycle_vol_cnt2_0A4 >= 800 )
        {//电压检测循环计次
					//时间长关机
          buzz_type_0B2 = 1;
          for ( i = 0; i < 200; i = (u16)(i + 1) )
          {
            while ( !time1_ok_05A )
              ;
            time1_ok_05A = 0;
          }
          buzz_type_0B2 = 0;
          GPIO_ResetBits(GPIOA, 32);//关机
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
		/*****************故障检测************************/
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
			|| motor1_error_el_vol_flag_0BF//短线一侧静态电流故障
			|| error_1D0
			|| error_1D1
			|| ((!flag_motor1_status_20B) && (!flag_motor2_status_20A)) )
    {//故障
      if ( cycle_error_cnt_0A0 >= 0x1AD274u )//故障检测时间 
      {//故障循环计次
        if ( !flag_unknown_2_086 )
        {
					//故障报警
          buzz_type_0B2 = 1;
          for ( j = 0; j < 200; j = (u16)(j + 1) )
          {
            while ( !time1_ok_05A )
              ;
            time1_ok_05A = 0;
          }
          buzz_type_0B2 = 0;
        }
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);//关机
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
		//休眠
		if ( vol > 1240 )
		{
			//电压高
			if ( cycle_vol_cnt3_high_09C < 1500 )
			{
				++cycle_vol_cnt3_high_09C;
			}
			else
			{
				flag_dormancy_reset_039 = 1;//启动标志
			}
		}
		else if ( vol <= 1240 )
		{//电压低
			cycle_vol_cnt3_high_09C = 0;
			flag_dormancy_098 = 1;//开始检测电压标志
			flag_vol_low_03A = 1;
		}
	}
}



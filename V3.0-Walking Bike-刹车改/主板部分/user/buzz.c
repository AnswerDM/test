#include "buzz.h"





//----- (080024CE) --------------------------------------------------------
void buzz_ctrl_all()
{
  signed int i; // r0@6

  if ( (flag_unknown_2_bak_094 != 1) || flag_unknown_2_086 )
  {
    if ( (!flag_unknown_2_bak_094) && (flag_unknown_2_086 == 1) )
    {//可能是软启动 儿童模式 慢速
      buzz_type_0B2 = 1;
      for ( i = 0; i < 200; i = (u8)(i + 1) )
      {
        while ( !time1_ok_05A )
          ;
        time1_ok_05A = 0;
      }
      buzz_type_0B2 = 0;
    }
  }
  else
  {
    buzz_power_on_type_08B = 0;
    flag_buzz_poweron_08A = 0;
  }
  flag_unknown_2_bak_094 = flag_unknown_2_086;
	/*************开机喇叭完成鸣叫*******************/
  if ( flag_buzz_poweron_08A )
  {//time
    if ( flash_para4_050 == flash_para3_054 )
    {
      if ( flag_unknown_2_086 )
      {
        buzz_type_0B2 = 0;
      }
      else if ( flag_unknown_3_087 )
      {
        buzz_type_0B2 = 3;
      }
      else if ( flag_dormancy_reset_039 )
      {//电压稳定标志
        if ( !flag_buzz_ok_1_084 )
        {
          buzz_type_0B2 = 3;//滴的一声
          if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
          {
            cycle_buzz_cnt1_08C = 0;
            flag_buzz_ok_1_084 = 1;
            buzz_type_0B2 = 0;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
      }
      else
      {
        if ( (flag_charging_085 != 1) || flag_pa12_ok_last_08D )
        {
          if ( (!flag_charging_085) && (flag_pa12_ok_last_08D == 1) )
            flag_buzz_unknown2_091 = 1;
        }
        else
        {
          flag_buzz_unknown1_090 = 1;//开机buzz完成
        }
        if ( ((flag_mpu2_online2_1D2 == 1) 
							&& (!flag_mpu2_online2_last_08E)
							&& (!flag_mpu3_online2_1D3)) 
					|| ((!flag_mpu2_online2_1D2) 
							&& (!flag_mpu3_online2_last_08F) 
							&& (flag_mpu3_online2_1D3 == 1)) )
							flag_buzz_unknown3_092 = 1;
        if ( ((!flag_mpu2_online2_1D2) 
							&& (flag_mpu2_online2_last_08E == 1) 
							&& (!flag_mpu3_online2_1D3) 
							&& (!flag_mpu3_online2_last_08F))
          || ((!flag_mpu2_online2_1D2) 
							&& (!flag_mpu2_online2_last_08E) 
							&& (flag_mpu3_online2_last_08F == 1) 
							&& (!flag_mpu3_online2_1D3)) )
							flag_buzz_unknown4_093 = 1;
        flag_pa12_ok_last_08D = flag_charging_085;
        flag_mpu2_online2_last_08E = flag_mpu2_online2_1D2;
        flag_mpu3_online2_last_08F = flag_mpu3_online2_1D3;
        if ( flag_unknown_8_188 )
        {
          if ( buzz_power_on_type_08B )
          {//开机
            buzz_type_0B2 = 0;
            cycle_buzz_cnt1_08C = 0;
            buzz_power_on_type_08B = 0;
            flag_unknown_8_188 = 0;
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 200 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown1_090 )//开机buzz完成
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 2;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown1_090 = 0;//开机buzz完成
            }
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown2_091 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 1;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown2_091 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 2;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown3_092 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 2;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown3_092 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown4_093 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 1;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown4_093 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 2;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_charging_mpu_online_20C || flag_vol_lower_031 )
        {//充电时 踩下踏板 或者电压低 报警
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if(buzz_type_0B2 == 0) buzz_type_0B2 = 1;
						else buzz_type_0B2 = 0;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else if ( error_vice_20D )
        {
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if ( buzz_type_0B2 )
              buzz_type_0B2 = 0;
            else
              buzz_type_0B2 = 2;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else if ( flag_two_motor_dir_20E )
        {
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if ( buzz_type_0B2 )
              buzz_type_0B2 = 0;
            else
              buzz_type_0B2 = 3;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else
        {
          buzz_type_0B2 = 0;
        }
      }
    }
  }
	/********开机喇叭控制***********/
  else if ( buzz_power_on_type_08B )
  {//可能是开机叫的声音
		//暂时屏蔽 改变开机声音
    if ( buzz_power_on_type_08B == 1 )
    {//开机
      buzz_type_0B2 = 2;
      if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//原版的声音是80
      {
        cycle_buzz_cnt1_08C = 0;
        buzz_power_on_type_08B = 2;
      }
      else
      {
        ++cycle_buzz_cnt1_08C;
      }
    }
    else if ( buzz_power_on_type_08B == 2 )
    {
      buzz_type_0B2 = 3;
      if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//原版的声音是80
      {
        cycle_buzz_cnt1_08C = 0;
        buzz_power_on_type_08B = 3;
      }
      else
      {
        ++cycle_buzz_cnt1_08C;
      }
    }
    else
    {
      buzz_type_0B2 = 0;
      cycle_buzz_cnt1_08C = 0;
      buzz_power_on_type_08B = 0;
      flag_buzz_poweron_08A = 1;//开机标志 喇叭鸣叫完成
    }
  }
  else
  {
    buzz_type_0B2 = 1;
    if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//原版的声音是80
    {
      cycle_buzz_cnt1_08C = 0;
      buzz_power_on_type_08B = 1;
    }
    else
    {
      ++cycle_buzz_cnt1_08C;
    }
  }
}

//----- (08002AEA) --------------------------------------------------------
void buzz_ctrl()
{//控制嗡鸣器状态
  if (( buzz_type_0B2 == 1 )&& (!buzz_cnt_095))
  {
    buzz_total_096 = 6;
  }
  else if ( (buzz_type_0B2 == 2)&& (!buzz_cnt_095 ) )
  {
    buzz_total_096 = 5;
  }
  else if ( (buzz_type_0B2 == 3) && (!buzz_cnt_095) )
  {
    buzz_total_096 = 4;
  }
	
  if ( buzz_cnt_095 >= (signed int)buzz_total_096 )
  {
    buzz_cnt_095 = 0;
    if ( buzz_on_097 )
    {
      buzz_on_097 = 0;
      GPIO_SetBits(GPIOA, 16);//喇叭
    }
    else
    {
      buzz_on_097 = 1;
      GPIO_ResetBits(GPIOA, 16);
    }
  }
  else
  {
    ++buzz_cnt_095;
  }
}



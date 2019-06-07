
#include "attitude.h"
//姿态板算法
#define PARA_PID_P		75.0f//70.0f
#define PID_PARA_KD		30.0f//30.0f

//----- (08002E1A) --------------------------------------------------------
void check_attitude()
{//小板检测
	int result; // 

  result = flag_mpu2_online1_174;//副板状态
  if ( !flag_mpu2_online1_174 )
    result = flag_mpu3_online1_175;
  if ( result == 4 )
  {
    flag_unknown_3_087 = 1;
    cycle_unknown_cnt5_0AC = 0;
  }
  else if ( (signed int)cycle_unknown_cnt5_0AC >= 80 )
  {
    flag_unknown_3_087 = 0;
  }
  else
  {
    ++cycle_unknown_cnt5_0AC;
  }
  if ( ((!flag_mpu3_online2_1D3) && (!flag_mpu2_online2_1D2) 
						&&(!flag_motor1_status_20B) && (!flag_motor2_status_20A)) 
				|| flag_unknown_2_086 )
  {
    switch ( result )
    {
      case 2:
        if ( (signed int)cycle_unknown_cnt1_0A8 > 8 )
        {
          if ( !flag_unknown_5_0AB )
          {
            flag_unknown_5_0AB = 1;
            flag_unknown_2_086 ^= 1u;
          }
        }
        else
        {
          ++cycle_unknown_cnt1_0A8;
        }
        cycle_unknown_cnt3_0AA = 0;
        break;
      case 1:
        if ( (signed int)cycle_unknown_cnt1_0A8 > 8 )
        {
          if ( !flag_unknown_5_0AB )
          {
            flag_unknown_5_0AB = 1;
            flag_unknown_2_086 = 0;
          }
        }
        else
        {
          ++cycle_unknown_cnt1_0A8;
        }
        cycle_unknown_cnt3_0AA = 0;
        break;
      case 8:
        if ( (signed int)cycle_unknown_cnt1_0A8 > 10 )
        {
          if ( !flag_unknown_4_0A9 )
          {
            flag_unknown_7_186 ^= 1u;
            flag_unknown_8_188 = 1;
            flag_unknown_4_0A9 = 1;
          }
        }
        else
        {
          ++cycle_unknown_cnt1_0A8;
        }
        cycle_unknown_cnt3_0AA = 0;
        break;
      case 3:
        if ( (signed int)cycle_unknown_cnt6_0AE >= 1500 )
        {
          cycle_unknown_cnt6_0AE = 0;
          flag_unknown_6_0AD = 1;
          flag_dormancy_reset_039 = 1;//休眠重启
          flag_buzz_ok_1_084 = 0;
        }
        else
        {
          ++cycle_unknown_cnt6_0AE;
        }
        cycle_unknown_cnt3_0AA = 0;
        break;
      default:
        if ( (signed int)cycle_unknown_cnt3_0AA >= 180 )
        {
          cycle_unknown_cnt3_0AA = 0;
          flag_unknown_4_0A9 = 0;
          flag_unknown_5_0AB = 0;
        }
        else
        {
          ++cycle_unknown_cnt3_0AA;
        }
        cycle_unknown_cnt6_0AE = 0;
        cycle_unknown_cnt1_0A8 = 0;
        break;
    }
    if ( flag_dormancy_reset_039 )
    {//休眠重启
			//电压正常
      if ( (signed int)cycle_unknown_cnt4_0B0 >= 80 )
      {
        if ( flag_unknown_6_0AD )
        {
          flag_dormancy_reset_039 = 0;
          flag_buzz_ok_1_084 = 0;
        }
      }
      else
      {
        ++cycle_unknown_cnt4_0B0;
      }
    }
    else
    {
      cycle_unknown_cnt4_0B0 = 0;
    }
  }
}

//----- (08005378) --------------------------------------------------------
float get_diroffset(float acce, float offset)
{//之前错误的时候 返回值和angle_dot_1DC赋值反了 现象是轮子打滑
	//改完后 没用这种现象了
	//计算方向偏差
	float diff;
	float rst;
	diff = acce - offset;
	rst = 0.002f * diff + 0.00003f * diff_last_1D8;//偏差和前一次偏差
	diff_last_1D8 = diff;
	return rst;
}



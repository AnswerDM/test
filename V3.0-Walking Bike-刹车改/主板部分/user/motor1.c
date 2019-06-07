#include "motor1.h"

//----- (080031B4) --------------------------------------------------------
void motor1_get_angle()
{//根据当前相位 获取需要调整的角度
	s16 result;
	u32 sum; // 
  signed int i; // 
	s8 pos_diff;
	
  if ( (signed int)motor1_time_phase_switch_0DA < 2812 )
    ++motor1_time_phase_switch_0DA;
  if ( (signed int)motor1_time_phase_switch_0DA >= 2812 )
  {
    moter1_roll_time_0EC = 16872;
    flag_motor1_roll_begin_0D8 = 0;
    flag_motor1_roll_ok_0D9 = 0;
    moter1_phase_num_0E8 = 0;
  }
  if ( ((signed int)moter1_roll_time_0EC > 1013) || (5 * motor1_time_phase_switch_0DA > 1012) )
    motor1_angle_para_c_0F2 = motor1_angle_para_g_0FC;
  if ( ((signed int)moter1_roll_time_0EC <= 1350) && (6 * motor1_time_phase_switch_0DA <= 1350) )
  {
    if ( (signed int)cycle_motor1_cnt4_0E9 >= 6 )
    {
      flag_motor1_move_0EA = 0;
//      ram_0C6 = 0;
    }
  }
  else
  {
    flag_motor1_move_0EA = 1;
    cycle_motor1_cnt4_0E9 = 0;
  }
  if ( motor1_dir_flag_0EE )
  {
    if ( (motor1_cur_phase_0DC == 6) && (motor1_angle_para_c_0F2 != 0xffff) )
    {
      if ( flag_motor1_shake_0E6 )
      {
        if ( (motor1_angle_para_c_0F2 - motor1_unknown_para1_0E0) <= motor1_electrical_angle_bak_0DE )
          motor1_electrical_angle_bak_0DE = motor1_angle_para_c_0F2;
        else
          motor1_electrical_angle_bak_0DE += motor1_unknown_para1_0E0;
      }
      else
      {
        if ( (0xFFFF - motor1_unknown_para1_0E0) < motor1_electrical_angle_bak_0DE )
          flag_motor1_shake_0E6 = 1;
        motor1_electrical_angle_bak_0DE += motor1_unknown_para1_0E0;
      }
    }
    else if ( motor1_angle_para1_0E7 )
    {
      if ( (0xFFFF - motor1_unknown_para1_0E0) < motor1_electrical_angle_bak_0DE )
        motor1_angle_para1_0E7 = 0;
      motor1_electrical_angle_bak_0DE += motor1_unknown_para1_0E0;
    }
    else if ( (motor1_angle_para_c_0F2 - motor1_unknown_para1_0E0) <= motor1_electrical_angle_bak_0DE )
    {
      motor1_electrical_angle_bak_0DE = motor1_angle_para_c_0F2;
    }
    else
    {
      motor1_electrical_angle_bak_0DE += motor1_unknown_para1_0E0;
    }
  }
  else if ( (motor1_cur_phase_0DC == 1) && motor1_angle_para_c_0F2 )
  {
    if ( flag_motor1_shake_0E6 )
    {
      if ( (motor1_angle_para_c_0F2 + motor1_unknown_para1_0E0) >= motor1_electrical_angle_bak_0DE )
        motor1_electrical_angle_bak_0DE = motor1_angle_para_c_0F2;
      else
        motor1_electrical_angle_bak_0DE -= motor1_unknown_para1_0E0;
    }
    else
    {
      if ( motor1_electrical_angle_bak_0DE < (signed int)motor1_unknown_para1_0E0 )
        flag_motor1_shake_0E6 = 1;
      motor1_electrical_angle_bak_0DE -= motor1_unknown_para1_0E0;
    }
  }
  else if ( motor1_angle_para1_0E7 )
  {
    if ( motor1_electrical_angle_bak_0DE < (signed int)motor1_unknown_para1_0E0 )
      motor1_angle_para1_0E7 = 0;
    motor1_electrical_angle_bak_0DE -= motor1_unknown_para1_0E0;
  }
  else if ( (motor1_angle_para_c_0F2 + motor1_unknown_para1_0E0) >= motor1_electrical_angle_bak_0DE )
  {
    motor1_electrical_angle_bak_0DE = motor1_angle_para_c_0F2;
  }
  else
  {
    motor1_electrical_angle_bak_0DE -= motor1_unknown_para1_0E0;
  }
  //motor1_cur_hall_0D5 = (GPIOC->IDR >> 10) & 7;
	motor1_cur_hall_0D5 = (GPIOB->IDR >> 5) & 7;
  if ( ((GPIOC->IDR >> 10) & 7) && (motor1_cur_hall_0D5 != 7) )
  {
    cycle_motor1_phase_cnt_0D7 = 0;
  }
  else if ( (signed int)cycle_motor1_phase_cnt_0D7 < 30 )
  {
    ++cycle_motor1_phase_cnt_0D7;
    motor1_cur_hall_0D5 = motor1_last_hall_0D6;
  }
	//读取sa sb sc状态 电机霍尔状态
  if ( motor1_cur_hall_0D5 != motor1_last_hall_0D6 )//如果hall改变
  {
    motor1_angle_para1_0E7 = 0;
    flag_motor1_roll_begin_0D8 = 1;
    pos_diff = MOTOR_PHASE_SEQUENCE_120[motor1_cur_hall_0D5] - motor1_cur_phase_0DC;//角度差
    if ( (pos_diff != 1) && (pos_diff != -5) )
    {
      if ( (pos_diff == -1) || (pos_diff == 5) )
        motor1_dir_flag_0EE = 0;//电机方向标志 正反转
    }
    else
    {
      motor1_dir_flag_0EE = 1;//电机方向标志 正反转
    }
    if ( motor1_dir_flag_last_0D3 != motor1_dir_flag_0EE )
    {
      moter1_roll_time_0EC = 16872;
      flag_motor1_roll_begin_0D8 = 0;
      flag_motor1_roll_ok_0D9 = 0;
      moter1_phase_num_0E8 = 0;
    }
    motor1_dir_flag_last_0D3 = motor1_dir_flag_0EE;
    if ( (signed int)cycle_motor1_cnt4_0E9 < 6 )
      ++cycle_motor1_cnt4_0E9;
    moter1_angle_buf_234[moter1_phase_num_0E8] = motor1_time_phase_switch_0DA;
    motor1_time_phase_switch_0DA = 0;
    if ( flag_motor1_roll_ok_0D9 )
    {
      sum = 0;
      for ( i = 0; i < 6; i = (u8)(i + 1) )
        sum += moter1_angle_buf_234[i];
      moter1_roll_time_0EC = sum;
    }
    else
    {
      if ( flag_motor1_roll_begin_0D8 )
      {
        moter1_roll_time_0EC = 6 * moter1_angle_buf_234[moter1_phase_num_0E8];
      }
      else
      {
        moter1_roll_time_0EC = 16872;
        flag_motor1_move_0EA = 1;
      }
      if ( moter1_phase_num_0E8 == 5 )
        flag_motor1_roll_ok_0D9 = 1;
    }
    if ( (signed int)moter1_phase_num_0E8 >= 5 )
      moter1_phase_num_0E8 = 0;
    else
      ++moter1_phase_num_0E8;
    if ( (signed int)moter1_roll_time_0EC < 46 )
      moter1_roll_time_0EC = 46;
    motor1_cur_phase_0DC = MOTOR_PHASE_SEQUENCE_120[motor1_cur_hall_0D5];
    motor1_last_hall_0D6 = motor1_cur_hall_0D5;
    //motor1_phase_last_bak_100 = motor1_cur_hall_0D5;
    if ( motor1_cur_phase_0DC ==0 )
    {
      error_motor1_pos_flag_0D2 = 1;//电机位置错误标志
      TIM1->BDTR &= 0x7FFFu;//关闭pwm
    }
    else
    {
      if ( motor1_dir_flag_0EE )
      {
        switch ( motor1_cur_phase_0DC )
        {
          case 1u:
            motor1_electrical_angle_0F4 = 5461;
            motor1_angle_para_a_0F0 = 0;
            motor1_angle_para_e_0F8 = 0xEC16;
            motor1_angle_para_d_0F6 = 5097;
            motor1_angle_para_g_0FC = 10922;
            motor1_angle_para_f_0FA = 16019;
            if ( !flag_motor1_shake_0E6 )
              motor1_angle_para1_0E7 = 1;
            break;
          case 2u:
            motor1_electrical_angle_0F4 = 0x3FFF;
            motor1_angle_para_a_0F0 = 10922;
            motor1_angle_para_e_0F8 = 5825;
            motor1_angle_para_d_0F6 = 16019;
            motor1_angle_para_g_0FC = 21845;
            motor1_angle_para_f_0FA = 26942;
            break;
          case 3u:
            motor1_electrical_angle_0F4 = 27306;
            motor1_angle_para_a_0F0 = 21845;
            motor1_angle_para_e_0F8 = 16748;
            motor1_angle_para_d_0F6 = 26942;
            motor1_angle_para_g_0FC = 0x8000;
            motor1_angle_para_f_0FA = 0x93E9;
            break;
          case 4u:
            motor1_electrical_angle_0F4 = 0x9555;
            motor1_angle_para_a_0F0 = 0x8000;
            motor1_angle_para_e_0F8 = 27671;
            motor1_angle_para_d_0F6 = 0x93E9;
            motor1_angle_para_g_0FC = 0xAAAA;
            motor1_angle_para_f_0FA = 0xBE93;
            break;
          case 5u:
            motor1_electrical_angle_0F4 = 0xBFFF;
            motor1_angle_para_a_0F0 = 0xAAAA;
            motor1_angle_para_e_0F8 = 0x96C1;
            motor1_angle_para_d_0F6 = 0xBE93;
            motor1_angle_para_g_0FC = 0xD555;
            motor1_angle_para_f_0FA = 0xE93E;
            break;
          case 6u:
            motor1_electrical_angle_0F4 = 0xEAAA;
            motor1_angle_para_a_0F0 = 0xD555;
            motor1_angle_para_e_0F8 = 0xC16C;
            motor1_angle_para_d_0F6 = 0xE93E;
            motor1_angle_para_g_0FC = 0xFFFF;
            motor1_angle_para_f_0FA = 5097;
            break;
          case 0u:
            break;
        }
        motor1_angle_diff_0E2 = motor1_angle_para_a_0F0 - motor1_electrical_angle_bak_0DE;
      }
      else
      {
        switch ( motor1_cur_phase_0DC )
        {
          case 1u:
            motor1_electrical_angle_0F4 = 5461;
            motor1_angle_para_a_0F0 = 10922;
            motor1_angle_para_e_0F8 = 5825;
            motor1_angle_para_d_0F6 = 16019;
            motor1_angle_para_g_0FC = 0;
            motor1_angle_para_f_0FA = 0xEC16;
            break;
          case 2u:
            motor1_electrical_angle_0F4 = 0x3FFF;
            motor1_angle_para_a_0F0 = 21845;
            motor1_angle_para_e_0F8 = 16748;
            motor1_angle_para_d_0F6 = 26942;
            motor1_angle_para_g_0FC = 10922;
            motor1_angle_para_f_0FA = 5825;
            break;
          case 3u:
            motor1_electrical_angle_0F4 = 27306;
            motor1_angle_para_a_0F0 = 0x8000;
            motor1_angle_para_e_0F8 = 27671;
            motor1_angle_para_d_0F6 = 0x93E9;
            motor1_angle_para_g_0FC = 21845;
            motor1_angle_para_f_0FA = 16748;
            break;
          case 4u:
            motor1_electrical_angle_0F4 = 0x9555;
            motor1_angle_para_a_0F0 = 0xAAAA;
            motor1_angle_para_e_0F8 = 0x96C1;
            motor1_angle_para_d_0F6 = 0xBE93;
            motor1_angle_para_g_0FC = 0x8000;
            motor1_angle_para_f_0FA = 27671;
            break;
          case 5u:
            motor1_electrical_angle_0F4 = 0xBFFF;
            motor1_angle_para_a_0F0 = 0xD555;
            motor1_angle_para_e_0F8 = 0xC16C;
            motor1_angle_para_d_0F6 = 0xE93E;
            motor1_angle_para_g_0FC = 0xAAAA;
            motor1_angle_para_f_0FA = 0x96C1;
            break;
          case 6u:
            motor1_electrical_angle_0F4 = 0xEAAA;
            motor1_angle_para_a_0F0 = 0xFFFF;
            motor1_angle_para_e_0F8 = 0xEC16;
            motor1_angle_para_d_0F6 = 5097;
            motor1_angle_para_g_0FC = 0xD555;
            motor1_angle_para_f_0FA = 0xC16C;
            if ( !flag_motor1_shake_0E6 )
              motor1_angle_para1_0E7 = 1;
            break;
          case 0u:
            break;
        }
        motor1_angle_diff_0E2 = motor1_electrical_angle_bak_0DE - motor1_angle_para_a_0F0;
      }
      if ( ((signed int)moter1_roll_time_0EC > 1013) || (flag_motor1_roll_ok_0D9==0) )
      {
        motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
        motor1_angle_para_c_0F2 = motor1_angle_para_g_0FC;
        motor1_angle_diff_0E2 = 0;
        motor1_angle_para1_0E7 = 0;
      }
      else
      {
        motor1_angle_para_c_0F2 = motor1_angle_para_f_0FA;
        if ( motor1_dir_flag_0EE )
        {
          if ( motor1_cur_phase_0DC == 1 )
          {
            if ( flag_motor1_shake_0E6 )
            {
              if ( motor1_electrical_angle_bak_0DE > (signed int)motor1_angle_para_d_0F6 )
              {
                motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
                motor1_angle_diff_0E2 = 0;
                motor1_angle_para1_0E7 = 0;
              }
            }
            else if ( motor1_electrical_angle_bak_0DE < (signed int)motor1_angle_para_e_0F8 )
            {
              motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
              motor1_angle_diff_0E2 = 0;
              motor1_angle_para1_0E7 = 0;
            }
          }
          else
          {
            if ( (motor1_cur_phase_0DC == 6) && ((signed int)moter1_roll_time_0EC > 1013) )
              motor1_angle_para_c_0F2 = 0xffff;
            if ( (motor1_electrical_angle_bak_0DE > (signed int)motor1_angle_para_d_0F6) || (motor1_electrical_angle_bak_0DE < (signed int)motor1_angle_para_e_0F8) )
            {
              motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
              motor1_angle_diff_0E2 = 0;
              motor1_angle_para1_0E7 = 0;
            }
          }
        }
        else if ( motor1_cur_phase_0DC == 6 )
        {
          if ( flag_motor1_shake_0E6 )
          {
            if ( motor1_electrical_angle_bak_0DE < (signed int)motor1_angle_para_e_0F8 )
            {
              motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
              motor1_angle_diff_0E2 = 0;
              motor1_angle_para1_0E7 = 0;
            }
          }
          else if ( motor1_electrical_angle_bak_0DE > (signed int)motor1_angle_para_d_0F6 )
          {
            motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
            motor1_angle_diff_0E2 = 0;
            motor1_angle_para1_0E7 = 0;
          }
        }
        else
        {
          if ( (motor1_cur_phase_0DC == 1) && ((signed int)moter1_roll_time_0EC > 1013) )
            motor1_angle_para_c_0F2 = 0;
          if ( (motor1_electrical_angle_bak_0DE > (signed int)motor1_angle_para_d_0F6) || (motor1_electrical_angle_bak_0DE < (signed int)motor1_angle_para_e_0F8) )
          {
            motor1_electrical_angle_bak_0DE = motor1_angle_para_a_0F0;
            motor1_angle_diff_0E2 = 0;
            motor1_angle_para1_0E7 = 0;
          }
        }
      }
    }
    if ( (signed int)moter1_roll_time_0EC <= 1013 )
      result = (s16)(moter1_roll_time_0EC - moter1_roll_time_laset_0E4);
    else
      result = 0;
    motor1_unknown_para1_0E0 = (motor1_angle_diff_0E2 + 0xFFFF + ((moter1_roll_time_0EC + result) >> 1)) / ((unsigned int)moter1_roll_time_0EC + result);
    flag_motor1_shake_0E6 = 0;
    moter1_roll_time_laset_0E4 = moter1_roll_time_0EC;
  }
  if ( flag_motor1_move_0EA )
    motor1_electrical_angle_bak_0DE = motor1_electrical_angle_0F4;
  motor1_Angle = motor1_electrical_angle_bak_0DE;//角度
  if ( flag_motor1_move_0EA )
  {
    motor1_Angle += 4732;
  }
  else if ( motor1_dir_flag_0EE )
  {
    motor1_Angle += 5825;
  }
  else
  {
    motor1_Angle += 3640;
  }
}

//----- (08003BA8) --------------------------------------------------------
void motor1_init_para()
{//参数初始化
  motor1_flow_integral = 0;//负载累积参数
  motor1_Curr_q_d_108 = 0;
  motor1_stat_volt_q_d.qV_Component2 = 0;
}

//----- (08003BBA) --------------------------------------------------------
void motor1_flow_reg()
{//负载电流调节 输出参考电压vds
	signed int curq_d; // r2@1
  signed int diff; // r0@2
  int val; // r4@6
  signed int rst; // r1@6

  curq_d = (s16)-motor1_Curr_q_d_108;
  if ( curq_d > 0 )
  {
    diff = 1;
  }
  else if ( curq_d < 0 )
	{
		diff = -1;
  }
	else
	{
		diff = 0;
  }
	//
  motor1_flow_integral += diff;//负载正负积分
  val = motor1_flow_integral + (curq_d >> 2);
  rst = (s16)val;
  if ( val < -0x4000 )
  {
    rst = -16384;
    motor1_flow_integral = -16384;
  }
  else if ( (s16)val > 0x4000 )
  {
    rst = 0x4000;
    motor1_flow_integral = 0x4000;
  }
  motor1_stat_volt_q_d.qV_Component2 = rst >> 6;
  //return result;
}

//----- (08003C20) --------------------------------------------------------
void motor1_Clarke()
{//坐标变换 	笛卡尔坐标变换
	//改大了 一卡一卡的 对速度没用太大影响
  motor1_Curr_alfa_beta.qI_Component1 = motor1_curr_a_b.qI_Component1;
  motor1_Curr_alfa_beta.qI_Component2 = 18918 * (motor1_curr_a_b.qI_Component1 
									+ 2 * motor1_curr_a_b.qI_Component2) >> 15;
}

//----- (08003C4E) --------------------------------------------------------
void motor1_Park()
{//Park变换
	s32 result; // r0@1

  result = (motor1_Curr_alfa_beta.qI_Component1 * motor1_vector_Components.hCos
					+ motor1_Curr_alfa_beta.qI_Component2 * motor1_vector_Components.hSin) >> 15;
  motor1_Curr_q_d_108 = (20317 * motor1_Curr_q_d_108
														+ 12451 * result) >> 15;
}

//----- (08003C8E) --------------------------------------------------------
void motor1_Rev_Park()
{// 反park变换		
  motor1_vector_Components.hSin = get_sin(motor1_Angle);
  motor1_vector_Components.hCos = get_cos(motor1_Angle);
  motor1_vol_a_b.qV_Component2 = 
		(motor1_stat_volt_q_d.qV_Component2 * motor1_vector_Components.hCos 
		- motor1_stat_volt_q_d.qV_Component1 * motor1_vector_Components.hSin) >> 15;
  motor1_vol_a_b.qV_Component1 = 
		(motor1_stat_volt_q_d.qV_Component1 * motor1_vector_Components.hCos 
		+ motor1_stat_volt_q_d.qV_Component2 * motor1_vector_Components.hSin) >> 15;
}


//----- (08003CF2) --------------------------------------------------------
void motor1_motor_ctrl(void)
{// 控制pwm wZ wY wX有可能不对（错位） 其他的是对的
	s16 hTimePhB;
	s16 hTimePhC; // r4@0
  s16 wZbak; // r1@1
  u16 bSector; // r5@1
  s16 hTimePhA; // r6@7
  s16 wX; // r2@7
  s16 wZ; // r0@7
  s16 wY; // r1@7
	
  wZbak = (s16)-(motor1_vol_a_b.qV_Component1 + 
									((3547 * motor1_vol_a_b.qV_Component2) >> 11));
  bSector = 0;
  if ( motor1_vol_a_b.qV_Component1 > 0 )
    bSector = 1;
  if ( (s16)(((3547 * motor1_vol_a_b.qV_Component2) >> 11) 
										- motor1_vol_a_b.qV_Component1) > 0 )
    bSector = (u16)(bSector + 2);
  if ( wZbak > 0 )
    bSector = (u16)(bSector + 4);
  hTimePhA = (s16)(((3547 * motor1_vol_a_b.qV_Component2) >> 11)
										- motor1_vol_a_b.qV_Component1);
  wX = (255 * motor1_vol_a_b.qV_Component1) >> 10;
  wZ = (255 * ((-wZbak) >> 1)) >> 10;
  wY = (255 * ((-hTimePhA) >> 1)) >> 10;
  if ( (unsigned int)bSector < 7 )
  {
    switch ( bSector )
    {
      case 0:
        hTimePhA = 255;
        hTimePhB = 255;
        hTimePhC = 255;
        break;
      case 1:
        hTimePhA = (s16)(255 - wY + wZ);
        hTimePhB = (s16)(wY + 255 + wZ);
        hTimePhC = (s16)(255 - wY - wZ);
        break;
      case 2:
        hTimePhA = (s16)(255 - wX + wZ);
        hTimePhB = (s16)(255 - wZ + wX);
        hTimePhC = (s16)(255 - wZ - wX);
        break;
      case 3:
        hTimePhA = (s16)(255 - wY + wX);
        hTimePhB = (s16)(wY + 255 + wX);
        hTimePhC = (s16)(255 - wX + wY);
        break;
      case 4:
        hTimePhA = (s16)(255 - wY + wX);
        hTimePhB = (s16)(wY + 255 + wX);
        hTimePhC = (s16)(255 - wX + wY);
        break;
      case 5:
        hTimePhA = (s16)(255 - wX + wZ);
        hTimePhB = (s16)(255 - wZ + wX);
        hTimePhC = (s16)(255 - wZ - wX);
        break;
      case 6:
        hTimePhA = (s16)(255 - wY + wZ);
        hTimePhB = (s16)(wY + 255 + wZ);
        hTimePhC = (s16)(255 - wY - wZ);
        break;
      default:
        break;
    }
  }
  if ( hTimePhA < 0 )
    (hTimePhA) = 0;
  if ( hTimePhB < 0 )
    (hTimePhB) = 0;
  if ( hTimePhC < 0 )
    (hTimePhC) = 0;
  TIM1->CCR1 = hTimePhA;        //占空比=(TIMx_CRRx/TIMx_ARR)*100%
  TIM1->CCR2 = hTimePhB;
  TIM1->CCR3 = hTimePhC;
}



#include "motor2.h"

//----- (080041B8) --------------------------------------------------------
void motor2_get_angle()
{//���ݵ�ǰ��λ ��ȡ��Ƕ�
	s16 result;
  u32 sum; 
  signed int i; 
	s8 pos_diff;

  if ( (signed int)motor2_time_phase_switch_14C < 2812 )//�л���λ��ʱ��
    ++motor2_time_phase_switch_14C;
  if ( (signed int)motor2_time_phase_switch_14C >= 2812 )
  {//����ʱ����� �����־λ
    moter2_roll_time_15E = 16872;//����һ�ܵ�ʱ��
    flag_motor2_roll_begin_14A = 0;//���ֿ�ʼ���� ��־
    flag_motor2_roll_ok_14B = 0;//���ֹ���һ�ܱ�־λ
    moter2_phase_num_15A = 0;//�����
  }
  if ( ((signed int)moter2_roll_time_15E > 1013) //����һ��ʱ�� > 1013
		|| ((5 * motor2_time_phase_switch_14C) > 1012) )
    motor2_angle_para_c_164 = motor2_angle_para_g_16E;
	
  if ( ((signed int)moter2_roll_time_15E <= 1350) 
		&& (6 * motor2_time_phase_switch_14C <= 1350) )//��ǰ�л���λ��ʱ��
  {
    if ( (signed int)cycle_motor2_cnt4_15B >= 6 )
    {
      flag_motor2_move_15C = 0;//�����ƶ�
      //ram_0C8 = 0;
    }
  }
  else
  {
    flag_motor2_move_15C = 1;//����δ�ƶ�
    cycle_motor2_cnt4_15B = 0;
  }
	
  if ( motor2_dir_flag_160 )
  {//����
    if ( (motor2_cur_phase_14E == 6) && (motor2_angle_para_c_164 != 0xffff) )
    {
      if ( flag_motor2_shake_158 )
      {
        if ( (motor2_angle_para_c_164 - motor2_unknown_para1_152) <= motor2_electrical_angle_bak_150 )
          motor2_electrical_angle_bak_150 = motor2_angle_para_c_164;
        else
          motor2_electrical_angle_bak_150 += motor2_unknown_para1_152;
      }
      else
      {
        if ( (0xFFFF - motor2_unknown_para1_152) < motor2_electrical_angle_bak_150 )
          flag_motor2_shake_158 = 1;
        motor2_electrical_angle_bak_150 += motor2_unknown_para1_152;
      }
    }
    else if ( motor2_angle_para1_159 )
    {
      if ( (0xFFFF - motor2_unknown_para1_152) < motor2_electrical_angle_bak_150 )
        motor2_angle_para1_159 = 0;
      motor2_electrical_angle_bak_150 += motor2_unknown_para1_152;
    }
    else if ( motor2_angle_para_c_164 - motor2_unknown_para1_152 <= motor2_electrical_angle_bak_150 )
    {
      motor2_electrical_angle_bak_150 = motor2_angle_para_c_164;
    }
    else
    {
      motor2_electrical_angle_bak_150 += motor2_unknown_para1_152;
    }
  }
  else if ( (motor2_cur_phase_14E == 1) && motor2_angle_para_c_164 )
  {
    if ( flag_motor2_shake_158 )
    {
      if ( (motor2_angle_para_c_164 + motor2_unknown_para1_152) >= motor2_electrical_angle_bak_150 )
        motor2_electrical_angle_bak_150 = motor2_angle_para_c_164;
      else
        motor2_electrical_angle_bak_150 -= motor2_unknown_para1_152;
    }
    else
    {
      if ( motor2_electrical_angle_bak_150 < (signed int)motor2_unknown_para1_152 )
        flag_motor2_shake_158 = 1;
      motor2_electrical_angle_bak_150 -= motor2_unknown_para1_152;
    }
  }
  else if ( motor2_angle_para1_159 )
  {
    if ( motor2_electrical_angle_bak_150 < (signed int)motor2_unknown_para1_152 )
      motor2_angle_para1_159 = 0;
    motor2_electrical_angle_bak_150 -= motor2_unknown_para1_152;
  }
  else if ( (motor2_angle_para_c_164 + motor2_unknown_para1_152) >= motor2_electrical_angle_bak_150 )
  {
    motor2_electrical_angle_bak_150 = motor2_angle_para_c_164;
  }
  else
  {
    motor2_electrical_angle_bak_150 -= motor2_unknown_para1_152;
  }
	/***************����*******************/
  motor2_cur_hall_147 = (GPIOB->IDR >> 5) & 7;//����״̬
  if ( ((GPIOB->IDR >> 5) & 7) && (motor2_cur_hall_147 != 7) )
  {//����״̬��ȷ ��λ��ȷ
    cycle_motor2_phase_cnt_149 = 0;
  }
  else if ( (signed int)cycle_motor2_phase_cnt_149 < 30 )
  {
    ++cycle_motor2_phase_cnt_149;//������״̬ ������ 
    motor2_cur_hall_147 = motor2_last_hall_148;//����״̬����һ��״̬
  }
	//����״̬�л� 
  if ( motor2_cur_hall_147 != motor2_last_hall_148 )
  {
    motor2_angle_para1_159 = 0;
    flag_motor2_roll_begin_14A = 1;//��λ�����
		//�жϷ��� �����ת��ת
    pos_diff = MOTOR_PHASE_SEQUENCE_120[motor2_cur_hall_147] - motor2_cur_phase_14E;
    if ( (pos_diff == 1) || (pos_diff == -5) )
    {
      motor2_dir_flag_160 = 1;//�����־λ
    }
    else if ( (pos_diff == -1) || (pos_diff == 5) )
		{
      motor2_dir_flag_160 = 0;//����
    }
    if ( motor2_dir_flag_last_145 != motor2_dir_flag_160 )
    {//����෴����ת
      moter2_roll_time_15E = 16872;
      flag_motor2_roll_begin_14A = 0;//���ֿ�ʼ����
      flag_motor2_roll_ok_14B = 0;//���ֹ���һ�ܱ�־λ
      moter2_phase_num_15A = 0;//�����
    }
    motor2_dir_flag_last_145 = motor2_dir_flag_160;//ǰһ�εķ���
		////////////////////////////////
    if ( (signed int)cycle_motor2_cnt4_15B < 6 )
      ++cycle_motor2_cnt4_15B;
		//�л���λ��ʱ��
    moter2_phase_time_buf_240[moter2_phase_num_15A] = motor2_time_phase_switch_14C;
    motor2_time_phase_switch_14C = 0;//����
		
    if ( flag_motor2_roll_ok_14B )
    {//���ֹ���һ�����
      sum = 0;
      for ( i = 0; i < 6; i = (u8)(i + 1) )
        sum += moter2_phase_time_buf_240[i];//������·��������ʱ��
      moter2_roll_time_15E = sum;//���� ���ֹ���һ�ܵ�ʱ��
    }
    else
    {//û����ɹ���һ�ܵĶ���
      if ( flag_motor2_roll_begin_14A )
      {//���ֿ�ʼ���� ����λ�л�
				//����ĳ���һ��ʱ��Ϊ  6*��ǰ����λ�л�ʱ��
        moter2_roll_time_15E = 6 * moter2_phase_time_buf_240[moter2_phase_num_15A];
      }
      else
      {//û����ɹ���һ�� Ĭ�ϳ���һ��ʱ��
        moter2_roll_time_15E = 16872;//Ĭ��
        flag_motor2_move_15C = 1;//����δ�ƶ�
      }
      if ( moter2_phase_num_15A == 5 )
        flag_motor2_roll_ok_14B = 1;//����һ�ܱ�־λ
    }
		//�����
    if ( (signed int)moter2_phase_num_15A >= 5 )
      moter2_phase_num_15A = 0;
    else
      ++moter2_phase_num_15A;//�����
		//����ʱ�� ����ٿ���
    if ( (signed int)moter2_roll_time_15E < 46 )
      moter2_roll_time_15E = 46;
		//��ȡ��ǰ��λ���
    motor2_cur_phase_14E = MOTOR_PHASE_SEQUENCE_120[motor2_cur_hall_147];
    motor2_last_hall_148 = motor2_cur_hall_147;//ǰһ�λ���״̬����
    //motor2_phase_bak_172 = motor2_cur_hall_147;
		
    if ( motor2_cur_phase_14E == 0 )
    {//��Ŵ��� �ر�pwm���
      error_motor2_pos_flag_144 = 1;
      TIM8->BDTR &= 0x7FFFu;//�ر�pwm
    }//����һ��
    else
    {
			/**************��ȡ��Ƕ�*********************/
			//�������ȷ
      if ( motor2_dir_flag_160 )
      {//���� ����
				switch ( motor2_cur_phase_14E )
				{
					case 1u://λ��1
						motor2_electrical_angle_166 = 0x1555;
						motor2_angle_para_a_162 = 0;
						motor2_angle_para_e_16A = 0xEC16;
						motor2_angle_para_d_168 = 5097;
						motor2_angle_para_g_16E = 10922;
						motor2_angle_para_f_16C = 16019;
						if ( !flag_motor2_shake_158 )
							motor2_angle_para1_159 = 1;
						break;
					case 2u://λ��2
						motor2_electrical_angle_166 = 0x3FFF;
						motor2_angle_para_a_162 = 0x2AAA;
						motor2_angle_para_e_16A = 5825;
						motor2_angle_para_d_168 = 16019;
						motor2_angle_para_g_16E = 21845;
						motor2_angle_para_f_16C = 26942;
						break;
					case 3u://λ��3
						motor2_electrical_angle_166 = 0x6AAA;
						motor2_angle_para_a_162 = 0x5555;
						motor2_angle_para_e_16A = 16748;
						motor2_angle_para_d_168 = 26942;
						motor2_angle_para_g_16E = 0x8000;
						motor2_angle_para_f_16C = 0x93E9;
						break;
					case 4u://λ��4
						motor2_electrical_angle_166 = 0x9555;
						motor2_angle_para_a_162 = 0x8000;
						motor2_angle_para_e_16A = 27671;
						motor2_angle_para_d_168 = 0x93E9;
						motor2_angle_para_g_16E = 0xAAAA;
						motor2_angle_para_f_16C = 0xBE93;
						break;
					case 5u://λ��5
						motor2_electrical_angle_166 = 0xBFFF;
						motor2_angle_para_a_162 = 0xAAAA;
						motor2_angle_para_e_16A = 0x96C1;
						motor2_angle_para_d_168 = 0xBE93;
						motor2_angle_para_g_16E = 0xD555;
						motor2_angle_para_f_16C = 0xE93E;
						break;
					case 6u://λ��6
						motor2_electrical_angle_166 = 0xEAAA;
						motor2_angle_para_a_162 = 0xD555;
						motor2_angle_para_e_16A = 0xC16C;
						motor2_angle_para_d_168 = 0xE93E;
						motor2_angle_para_g_16E = 0xFFFF;
						motor2_angle_para_f_16C = 5097;
						break;
					case 0u:
						break;
				}
        motor2_angle_diff_154 = motor2_angle_para_a_162 - motor2_electrical_angle_bak_150;
      }
      else
      {
				switch ( motor2_cur_phase_14E )
				{
					case 1u://λ��1
						motor2_electrical_angle_166 = 0x1555;//��Ƕ�
						motor2_angle_para_a_162 = 0x2AAA;
						motor2_angle_para_e_16A = 5825;
						motor2_angle_para_d_168 = 16019;
						motor2_angle_para_g_16E = 0;
						motor2_angle_para_f_16C = 0xEC16;
						break;
					case 2u://λ��2
						motor2_electrical_angle_166 = 0x3FFF;
						motor2_angle_para_a_162 = 0x5555;
						motor2_angle_para_e_16A = 16748;
						motor2_angle_para_d_168 = 26942;
						motor2_angle_para_g_16E = 10922;
						motor2_angle_para_f_16C = 5825;
						break;
					case 3u://λ��3
						motor2_electrical_angle_166 = 0x6AAA;
						motor2_angle_para_a_162 = 0x8000;
						motor2_angle_para_e_16A = 27671;
						motor2_angle_para_d_168 = 0x93E9;
						motor2_angle_para_g_16E = 21845;
						motor2_angle_para_f_16C = 16748;
						break;
					case 4u://λ��4
						motor2_electrical_angle_166 = 0x9555;
						motor2_angle_para_a_162 = 0xAAAA;
						motor2_angle_para_e_16A = 0x96C1;
						motor2_angle_para_d_168 = 0xBE93;
						motor2_angle_para_g_16E = 0x8000;
						motor2_angle_para_f_16C = 27671;
						break;
					case 5u://λ��5
						motor2_electrical_angle_166 = 0xBFFF;
						motor2_angle_para_a_162 = 0xD555;
						motor2_angle_para_e_16A = 0xC16C;
						motor2_angle_para_d_168 = 0xE93E;
						motor2_angle_para_g_16E = 0xAAAA;
						motor2_angle_para_f_16C = 0x96C1;
						break;
					case 6u://λ��6
						motor2_electrical_angle_166 = 0xEAAA;
						motor2_angle_para_a_162 = 0xFFFF;
						motor2_angle_para_e_16A = 0xEC16;
						motor2_angle_para_d_168 = 5097;
						motor2_angle_para_g_16E = 0xD555;
						motor2_angle_para_f_16C = 0xC16C;
						if ( !flag_motor2_shake_158 )
							motor2_angle_para1_159 = 1;
						break;
					case 0u:
						break;
				}
        motor2_angle_diff_154 = motor2_electrical_angle_bak_150 - motor2_angle_para_a_162;
      }
      if ( ((signed int)moter2_roll_time_15E > 1013) || (flag_motor2_roll_ok_14B==0) )
      {//һ��ʱ��
        motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
        motor2_angle_para_c_164 = motor2_angle_para_g_16E;
        motor2_angle_diff_154 = 0;
        motor2_angle_para1_159 = 0;
      }
      else
      {
        motor2_angle_para_c_164 = motor2_angle_para_f_16C;
        if ( motor2_dir_flag_160 )
        {//����
          if ( motor2_cur_phase_14E == 1 )
          {
            if ( flag_motor2_shake_158 )
            {
              if ( motor2_electrical_angle_bak_150 > (signed int)motor2_angle_para_d_168 )
              {
                motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
                motor2_angle_diff_154 = 0;
                motor2_angle_para1_159 = 0;
              }
            }
            else if ( motor2_electrical_angle_bak_150 < (signed int)motor2_angle_para_e_16A )
            {
              motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
              motor2_angle_diff_154 = 0;
              motor2_angle_para1_159 = 0;
            }
          }
          else
          {
            if ( (motor2_cur_phase_14E == 6) && ((signed int)moter2_roll_time_15E > 1013) )
              motor2_angle_para_c_164 = 0xffff;
            if ( (motor2_electrical_angle_bak_150 > (signed int)motor2_angle_para_d_168) || (motor2_electrical_angle_bak_150 < (signed int)motor2_angle_para_e_16A) )
            {
              motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
              motor2_angle_diff_154 = 0;
              motor2_angle_para1_159 = 0;
            }
          }
        }
        else if ( motor2_cur_phase_14E == 6 )
        {
          if ( flag_motor2_shake_158 )
          {
            if ( motor2_electrical_angle_bak_150 < (signed int)motor2_angle_para_e_16A )
            {
              motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
              motor2_angle_diff_154 = 0;
              motor2_angle_para1_159 = 0;
            }
          }
          else if ( motor2_electrical_angle_bak_150 > (signed int)motor2_angle_para_d_168 )
          {
            motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
            motor2_angle_diff_154 = 0;
            motor2_angle_para1_159 = 0;
          }
        }
        else
        {
          if ( (motor2_cur_phase_14E == 1) && ((signed int)moter2_roll_time_15E > 1013) )
            motor2_angle_para_c_164 = 0;
          if ( (motor2_electrical_angle_bak_150 > (signed int)motor2_angle_para_d_168) || (motor2_electrical_angle_bak_150 < (signed int)motor2_angle_para_e_16A) )
          {
            motor2_electrical_angle_bak_150 = motor2_angle_para_a_162;
            motor2_angle_diff_154 = 0;
            motor2_angle_para1_159 = 0;
          }
        }
      }
    }
    if ( (signed int)moter2_roll_time_15E <= 1013 )
      result = (moter2_roll_time_15E - moter2_roll_time_laset_156) >> 3;
    else
      result = 0;
    motor2_unknown_para1_152 = (motor2_angle_diff_154 + 0xFFFF + ((moter2_roll_time_15E + result) >> 1))
																/ ((unsigned int)moter2_roll_time_15E + result);
    flag_motor2_shake_158 = 0;
    moter2_roll_time_laset_156 = moter2_roll_time_15E;//����
  }
	/***********��Ƕ�*****************/
  if ( flag_motor2_move_15C )//����δ�ƶ�
    motor2_electrical_angle_bak_150 = motor2_electrical_angle_166;//
  motor2_Angle = motor2_electrical_angle_bak_150;
  if ( flag_motor2_move_15C )
  {//����δ�ƶ�
    motor2_Angle += 4732;//�Ƕ�����
  }
  else if ( motor2_dir_flag_160 )
  {//����
    motor2_Angle += 5825;//
  }
  else
  {//����
    motor2_Angle += 3640;
  }
}

//----- (08003EB0) --------------------------------------------------------
void motor2_init_para()
{
  motor2_flow_integral = 0;
  motor2_Curr_qd_Component1_128 = 0;
  motor2_stat_volt_q_d.qV_Component2 = 0;
}

//----- (08003EC2) --------------------------------------------------------
void motor2_flow_reg()
{//������������ ����ο���ѹvds 
	signed int q_comp1_val; // r2@1
  signed int diff; // r0@2
  int val; // r4@6
  signed int rst; // r1@6

  q_comp1_val = -motor2_Curr_qd_Component1_128;
  if ( q_comp1_val > 0 )
    diff = 1;
  else if ( q_comp1_val < 0 )
		diff = -1;
	else
		diff = 0;
	
  motor2_flow_integral += diff;
  val = motor2_flow_integral + (q_comp1_val >> 2);
  rst = (s16)val;
  if ( val < -0x4000 )
  {
    rst = -16384;
    motor2_flow_integral = 0xC000;
  }
  else if ( (s16)val > 0x4000 )
  {
    rst = 0x4000;
    motor2_flow_integral = 0x4000;
  }
  motor2_stat_volt_q_d.qV_Component2 = rst >> 6;// ����/64
  //return result;
}

//----- (08003F28) --------------------------------------------------------
void motor2_Clarke()
{//����任 
  motor2_Curr_alfa_beta.qI_Component1 = motor2_curr_a_b.qI_Component1;
	motor2_Curr_alfa_beta.qI_Component2 = 18918 * (motor2_curr_a_b.qI_Component1 
										+ 2 * motor2_curr_a_b.qI_Component2) >> 15;
}

//----- (08003F56) --------------------------------------------------------
void motor2_Park()
{
	s32 result; // r0@1

  result = (motor2_Curr_alfa_beta.qI_Component1 * motor2_vector_Components.hCos
						+ motor2_Curr_alfa_beta.qI_Component2 * motor2_vector_Components.hSin)
						>> 15;
  motor2_Curr_qd_Component1_128 = (20317 * motor2_Curr_qd_Component1_128 
															+ 12451 * result) 
															>> 15;
}

//----- (08003F96) --------------------------------------------------------
void motor2_Rev_Park()
{//��park�任 	
  motor2_vector_Components.hSin = get_sin(motor2_Angle);
  motor2_vector_Components.hCos = get_cos(motor2_Angle);
  motor2_vol_a_b.qV_Component2 = 
		(motor2_stat_volt_q_d.qV_Component2 * motor2_vector_Components.hCos 
		- motor2_stat_volt_q_d.qV_Component1 * motor2_vector_Components.hSin) >> 15;
  motor2_vol_a_b.qV_Component1 = 
		(motor2_stat_volt_q_d.qV_Component1 * motor2_vector_Components.hCos 
		+ motor2_stat_volt_q_d.qV_Component2 * motor2_vector_Components.hSin) >> 15;
}

//----- (08003FFA) --------------------------------------------------------
void motor2_motor_ctrl()
{// ����pwm wZ wY wX�п��ܲ��ԣ���λ�� �������ǶԵ�
	s16 hTimePhB;
	s16 hTimePhC; 
  s16 wZbak; 
  u16 bSector; 
  s16 hTimePhA; 
  s16 wX; 
  s16 wZ; 
  s16 wY;

  wZbak = (s16)-(motor2_vol_a_b.qV_Component1 + 
										((3547 * motor2_vol_a_b.qV_Component2) >> 11));
  bSector = 0;
  if ( motor2_vol_a_b.qV_Component1 > 0 )
    bSector = 1;
  if ( (s16)(((3547 * motor2_vol_a_b.qV_Component2) >> 11) 
										- motor2_vol_a_b.qV_Component1) > 0 )
    bSector = (u16)(bSector + 2);
  if ( wZbak > 0 )
    bSector = (u16)(bSector + 4);
  hTimePhA = (s16)(((3547 * motor2_vol_a_b.qV_Component2) >> 11) 
										- motor2_vol_a_b.qV_Component1);
  
	wX = (255 * motor2_vol_a_b.qV_Component1) >> 10;
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
  TIM8->CCR1 = hTimePhA;
  TIM8->CCR2 = hTimePhB;
  TIM8->CCR3 = hTimePhC;
}


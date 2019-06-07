
#include "algorithm.h"

//----- (08001C16) --------------------------------------------------------
void self_checking()
{//��ȫ��� ��Ҫ��ȡ��Ư
  signed int i; // r4@1
  signed int j; // r4@7
	signed int v1; // r4@11
  signed int l; // r5@17
  u16 val3; // r7@33
  u16 val4; // r8@33
  signed int n; // r5@33

  moter1_roll_time_0EC = 0xffff;
  moter2_roll_time_15E = 0xffff;
  flag_mpu2_unchange_17E = 0;
  flag_mpu3_unchange_17F = 0;
  error_1D0 = 0;
  error_1D1 = 0;
  flag_charging_085 = 0;//����־λ
  flag_vol_low_03A = 0;
  flag_dormancy_reset_039 = 0;//��������
  error_angle_186 = 0;//��̬��Ƕȹ���
	//��ʱ
  for ( i = 0; i < 50; i = i + 1 )//��ʱ 51.2ms
  {
    while ( !time1_ok_05A )
      ;
    time1_ok_05A = 0;               //time1_ok_05A:ÿ16*64us=1024us��λһ��
  }
  for ( j = 0; j < 380; j = (j + 1) )//��ʱ 389.12ms
  {
    while ( !time1_ok_05A )        //time1_ok_05A:ÿ16*64us=1024us��λһ��
      ;
    time1_ok_05A = 0;
  }
	/******************************/
	//��ȡ��̬����
	v1 = 0;
  for ( l = 0; l < 4; l = (u8)(l + 1) )
    v1 = (u16)(motor1_load_buf_074[l] + v1);  //motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;  VCCL
  motor1_load_ref_0C0 = v1 >> 2;
  if ( (motor1_load_ref_0C0 >= 2234) || (motor1_load_ref_0C0 <= 1614) ) //motor1_load_ref_0C0:�Լ�����궨ֵ
  {//������Χ �ر�pwm
    motor1_error_el_vol_flag_0BF = 1;//����һ�ྲ̬��������
    TIM1->BDTR &= 0x7FFFu;//�ر�pwm
  }
	/************��Ư******************/
  val3 = 0;
  val4 = 0;
  for ( n = 0; n < 16; n = (u8)(n + 1) )
  {
    val3 += motor1_u_cur_070;          //motor1_u_cur_070 = ADC2->JDR1; VCCL&VCC4(BL���)
    val4 += motor1_w_cur_072;          //motor1_w_cur_072 = ADC2->JDR2; VCCL&VCC3(CL���)
    while ( !time1_ok_05A )
      ;
    time1_ok_05A = 0;
  }
  motor1_hPhaseAOffset_110 = val3 >> 4;//motor1_u_cur_070��ƽ��ֵ
  motor1_hPhaseBOffset_112 = val4 >> 4;//motor1_w_cur_072��ƽ��ֵ
  if ( (motor1_hPhaseAOffset_110 > 2234) || (motor1_hPhaseAOffset_110 < 1614)
	  || (motor1_hPhaseBOffset_112 > 2234) || (motor1_hPhaseBOffset_112 < 1614) )
  {//������Χ �ر�pwm
    motor1_error_el_vol_flag_0BF = 1;      //u����� �� w����� �궨ֵ
    TIM1->BDTR &= 0x7FFFu;//�ر�pwm
  }	
  TIM1->BDTR &= 0x7FFFu;//�ر�pwm
	
	/************���¶�ȡ����*****************/
//	reset_flash_2();======================================================================================================================================
  self_check_ok_038 = 1;//�Լ����
  flag_unknown_7_186 = 0;
}

 int lk_torque_gas=0;
 int lk_gas_accelerate=0;

//----- (08002018) --------------------------------------------------------
//�ж�
void TIM1_UP_IRQHandler(void)    //64usһ��
{//time1��� ���Ƶ�����㷨�ڴ��ж������
	//ʱ���ۼ�
  int torque_gas; // r0@13
  int gas_accelerate; // r1@16	
	//ʱ���ۼ�
  if ( time1_cnt_056 >= 16 )  //ÿ  64*16 = 1024 us ����1ms  time1_ok_05A  ��λ
  {
    time1_cnt_056 = 0;
    time1_ok_05A = 1;
  }
  else
  {
    ++time1_cnt_056;
  }
	
	/*********************************/
	//��ȡadc����
  if ( (signed int)get_adc_cnt_058 >= 3 )  //ÿ 64*3 = 192 us  get_adc_ok_0B4  ��λ
  {
    get_adc_ok_0B4 = 1;
    get_adc_cnt_058 = 0;
  }
  else
  {
    ++get_adc_cnt_058;
  }
	
	/*********************************/
	//�Լ����
  if ( self_check_ok_038 )
  {
    motor1_get_angle();
  }
	
	/*********************************/
  bet_vol_buf_068[get_adc_cnt_058] = ADC3->JDR4;//��ص�ѹ����
	
	
	//��ȡ������ѹ1 motor1
  motor1_u_cur_070 = ADC2->JDR1;//VCCL&VCC4(BL���)
  motor1_w_cur_072 = ADC2->JDR2;//VCCL&VCC3(CL���)
  motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;//VCCL
	//����uw����� ��õ�ǰ�ඨ�ӵ���	 motor1
	motor1_curr_a_b.qI_Component2 = motor1_hPhaseAOffset_110 - motor1_u_cur_070;
  motor1_curr_a_b.qI_Component1 = -(s16)(motor1_hPhaseBOffset_112 - motor1_w_cur_072) 
																	- (motor1_hPhaseAOffset_110 - motor1_u_cur_070);
	
	//�ٶȵ��� 
	if ( para_motor1_attitude_0C2 < 0 )//�ٶȸ���ֵ
    torque_gas = -para_motor1_attitude_0C2;
  else
    torque_gas = para_motor1_attitude_0C2;
	
  if ( motor1_stat_volt_q_d.qV_Component1 < 0 )
    gas_accelerate = -motor1_stat_volt_q_d.qV_Component1;
  else
    gas_accelerate = motor1_stat_volt_q_d.qV_Component1;
	
	
	
	lk_torque_gas = torque_gas;
	lk_gas_accelerate = gas_accelerate;
	
	
  if ( torque_gas <= gas_accelerate )//ABS(�ٶȸ���ֵ)<=ABS(motor1_stat_volt_q_d.qV_Component1)
  {
    motor1_stat_volt_q_d.qV_Component1 = para_motor1_attitude_0C2;
  }
  else if ( !flag_motor1_reg_slow_0BE ) //flag_motor1_reg_slow_0BE==0
  {
    if ( motor1_stat_volt_q_d.qV_Component1 >= para_motor1_attitude_0C2 )       //б�¸���
    {
      if ( motor1_stat_volt_q_d.qV_Component1 > para_motor1_attitude_0C2 )
      {
        if ( motor1_stat_volt_q_d.qV_Component1 <= para_motor1_attitude_0C2 + 2 )
          --motor1_stat_volt_q_d.qV_Component1;
        else
          motor1_stat_volt_q_d.qV_Component1 -= 2;
      }
    }
    else if ( motor1_stat_volt_q_d.qV_Component1 + 2 >= para_motor1_attitude_0C2 )
    {
      ++motor1_stat_volt_q_d.qV_Component1;
    }
    else
    {
      motor1_stat_volt_q_d.qV_Component1 += 2;
    }
  }
	
  if ( self_check_ok_038 )
  {//�Լ����
		//�����������
		//���Ƶ��1
    if ( flag_motor1_move_0EA )
    {
      motor1_init_para();//������ʼ��
    }
    else if ( ((signed int)motor1_u_cur_070 < 3848) 
				&& ((signed int)motor1_w_cur_072 < 3848) )
    {
      motor1_Clarke();
      motor1_Park();//����ǶȲ�������غ��� ���庬�岻����
      motor1_flow_reg();//���������ĵ���
    }
    motor1_Rev_Park();//��park�任
    motor1_motor_ctrl();//�������
		
	}
		/**************************************/
  
  //get_usart2();//��ȡ�Ƕ�
  //get_usart3();//��ȡ�Ƕ�=========================================================================================================
  TIM1->SR &= 0xFFFEu;
  TIM1->SR &= 0xFFFEu;
}


//----- (08003088) --------------------------------------------------------
void vlot_cmp1_regulation()
{//���ص���
  u32 val; // r0@1
  signed int i; // r1@1
  u32 current1; // r0@4
//  u32 val2; // r0@10
//  signed int j; // r1@10
//  u32 current2; // r0@13

	/********motor1************/
  val = 0;
  for ( i = 0; i < 4; i = (u8)(i + 1) )
    val = (motor1_load_buf_074[i] + val);//����         //motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3; VCCL
  current1 = val >> 2;                                  //current1�������е�ʵʱ��ѹֵ
  motor1_speed_0C4 = current1 - motor1_load_ref_0C0;    //motor1_load_ref_0C0�������Լ�ʱ�ı궨ֵ
  if ( (motor1_load_ref_0C0 + 717 >= current1) &&       //ʵʱ����ֵ��������̬����ֵ+717 
		((signed int)vol_val_032 > 1032) )                  //vol_val_032:ʵʱ��ص�ѹ  ��ص�ѹ�㹻
  {
    flag_motor1_reg_slow_0BE = 0; //��ص�ѹ�㹻���������������ھ�̬����+717
  }
  else
  {
    flag_motor1_reg_slow_0BE = 1; //��ص�ѹ����
    if ( motor1_stat_volt_q_d.qV_Component1 >= 0 )
      --motor1_stat_volt_q_d.qV_Component1;
    else
      ++motor1_stat_volt_q_d.qV_Component1;//���ص���
  }
//	//2
//	/********motor2************/
//  val2 = 0;
//  for ( j = 0; j < 4; j = (u8)(j + 1) )
//    val2 = (motor2_load_buf_060[j] + val2);
//  current2 = val2 >> 2;//
//  motor2_speed_0BC = current2 - motor2_load_ref_0B8;//
//  if ( (motor2_load_ref_0B8 + 717 >= current2) && 
//		((signed int)vol_val_032 > 1032) )
//  {
//    flag_motor2_reg_slow_0B5 = 0;
//  }
//  else
//  {
//    flag_motor2_reg_slow_0B5 = 1;
//    if ( motor2_stat_volt_q_d.qV_Component1 >= 0 )
//      --motor2_stat_volt_q_d.qV_Component1;
//    else
//      ++motor2_stat_volt_q_d.qV_Component1;//���ص���
//  }
}

//----- (08005D00) --------------------------------------------------------
void get_motor_state()
{
	if(flag_charging_085 //����־λ
		&& (flag_mpu3_online2_1D3 || flag_mpu2_online2_1D2)) 
		flag_charging_mpu_online_20C = 1;
	else flag_charging_mpu_online_20C = 0;
	
  if ( motor1_dir_flag_0EE == motor2_dir_flag_160 )
  {//���ͬ��
    flag_two_motor_dir_20E = 0;
  }
  else if ( ((moter2_roll_time_15E + moter1_roll_time_0EC) / 2) >= 168 )
  {
    flag_two_motor_dir_20E = 0;//
  }
  else
  {
    flag_two_motor_dir_20E = 1;
  }
}

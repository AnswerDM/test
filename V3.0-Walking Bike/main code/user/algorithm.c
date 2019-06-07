
#include "algorithm.h"

//----- (08001C16) --------------------------------------------------------
void self_checking()
{//安全检查 主要获取温漂
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
  flag_charging_085 = 0;//充电标志位
  flag_vol_low_03A = 0;
  flag_dormancy_reset_039 = 0;//休眠重启
  error_angle_186 = 0;//姿态板角度过大
	//延时
  for ( i = 0; i < 50; i = i + 1 )//延时 51.2ms
  {
    while ( !time1_ok_05A )
      ;
    time1_ok_05A = 0;               //time1_ok_05A:每16*64us=1024us置位一次
  }
  for ( j = 0; j < 380; j = (j + 1) )//延时 389.12ms
  {
    while ( !time1_ok_05A )        //time1_ok_05A:每16*64us=1024us置位一次
      ;
    time1_ok_05A = 0;
  }
	/******************************/
	//获取静态电流
	v1 = 0;
  for ( l = 0; l < 4; l = (u8)(l + 1) )
    v1 = (u16)(motor1_load_buf_074[l] + v1);  //motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;  VCCL
  motor1_load_ref_0C0 = v1 >> 2;
  if ( (motor1_load_ref_0C0 >= 2234) || (motor1_load_ref_0C0 <= 1614) ) //motor1_load_ref_0C0:自检电流标定值
  {//超过范围 关闭pwm
    motor1_error_el_vol_flag_0BF = 1;//短线一侧静态电流故障
    TIM1->BDTR &= 0x7FFFu;//关闭pwm
  }
	/************温漂******************/
  val3 = 0;
  val4 = 0;
  for ( n = 0; n < 16; n = (u8)(n + 1) )
  {
    val3 += motor1_u_cur_070;          //motor1_u_cur_070 = ADC2->JDR1; VCCL&VCC4(BL输出)
    val4 += motor1_w_cur_072;          //motor1_w_cur_072 = ADC2->JDR2; VCCL&VCC3(CL输出)
    while ( !time1_ok_05A )
      ;
    time1_ok_05A = 0;
  }
  motor1_hPhaseAOffset_110 = val3 >> 4;//motor1_u_cur_070的平均值
  motor1_hPhaseBOffset_112 = val4 >> 4;//motor1_w_cur_072的平均值
  if ( (motor1_hPhaseAOffset_110 > 2234) || (motor1_hPhaseAOffset_110 < 1614)
	  || (motor1_hPhaseBOffset_112 > 2234) || (motor1_hPhaseBOffset_112 < 1614) )
  {//超过范围 关闭pwm
    motor1_error_el_vol_flag_0BF = 1;      //u相电流 或 w相电流 标定值
    TIM1->BDTR &= 0x7FFFu;//关闭pwm
  }	
  TIM1->BDTR &= 0x7FFFu;//关闭pwm
	
	/************重新读取参数*****************/
//	reset_flash_2();======================================================================================================================================
  self_check_ok_038 = 1;//自检完成
  flag_unknown_7_186 = 0;
}

 int lk_torque_gas=0;
 int lk_gas_accelerate=0;

//----- (08002018) --------------------------------------------------------
//中断
void TIM1_UP_IRQHandler(void)    //64us一次
{//time1溢出 控制电机主算法在此中断里进行
	//时间累计
  int torque_gas; // r0@13
  int gas_accelerate; // r1@16	
	//时间累计
  if ( time1_cnt_056 >= 16 )  //每  64*16 = 1024 us 将近1ms  time1_ok_05A  置位
  {
    time1_cnt_056 = 0;
    time1_ok_05A = 1;
  }
  else
  {
    ++time1_cnt_056;
  }
	
	/*********************************/
	//获取adc计数
  if ( (signed int)get_adc_cnt_058 >= 3 )  //每 64*3 = 192 us  get_adc_ok_0B4  置位
  {
    get_adc_ok_0B4 = 1;
    get_adc_cnt_058 = 0;
  }
  else
  {
    ++get_adc_cnt_058;
  }
	
	/*********************************/
	//自检完成
  if ( self_check_ok_038 )
  {
    motor1_get_angle();
  }
	
	/*********************************/
  bet_vol_buf_068[get_adc_cnt_058] = ADC3->JDR4;//电池电压采样
	
	
	//获取电流电压1 motor1
  motor1_u_cur_070 = ADC2->JDR1;//VCCL&VCC4(BL输出)
  motor1_w_cur_072 = ADC2->JDR2;//VCCL&VCC3(CL输出)
  motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3;//VCCL
	//根据uw相电流 获得当前相定子电流	 motor1
	motor1_curr_a_b.qI_Component2 = motor1_hPhaseAOffset_110 - motor1_u_cur_070;
  motor1_curr_a_b.qI_Component1 = -(s16)(motor1_hPhaseBOffset_112 - motor1_w_cur_072) 
																	- (motor1_hPhaseAOffset_110 - motor1_u_cur_070);
	
	//速度调节 
	if ( para_motor1_attitude_0C2 < 0 )//速度给定值
    torque_gas = -para_motor1_attitude_0C2;
  else
    torque_gas = para_motor1_attitude_0C2;
	
  if ( motor1_stat_volt_q_d.qV_Component1 < 0 )
    gas_accelerate = -motor1_stat_volt_q_d.qV_Component1;
  else
    gas_accelerate = motor1_stat_volt_q_d.qV_Component1;
	
	
	
	lk_torque_gas = torque_gas;
	lk_gas_accelerate = gas_accelerate;
	
	
  if ( torque_gas <= gas_accelerate )//ABS(速度给定值)<=ABS(motor1_stat_volt_q_d.qV_Component1)
  {
    motor1_stat_volt_q_d.qV_Component1 = para_motor1_attitude_0C2;
  }
  else if ( !flag_motor1_reg_slow_0BE ) //flag_motor1_reg_slow_0BE==0
  {
    if ( motor1_stat_volt_q_d.qV_Component1 >= para_motor1_attitude_0C2 )       //斜坡给定
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
  {//自检完成
		//控制两个电机
		//控制电机1
    if ( flag_motor1_move_0EA )
    {
      motor1_init_para();//参数初始化
    }
    else if ( ((signed int)motor1_u_cur_070 < 3848) 
				&& ((signed int)motor1_w_cur_072 < 3848) )
    {
      motor1_Clarke();
      motor1_Park();//计算角度参数等相关函数 具体含义不明白
      motor1_flow_reg();//负载流量的调节
    }
    motor1_Rev_Park();//反park变换
    motor1_motor_ctrl();//电机控制
		
	}
		/**************************************/
  
  //get_usart2();//获取角度
  //get_usart3();//获取角度=========================================================================================================
  TIM1->SR &= 0xFFFEu;
  TIM1->SR &= 0xFFFEu;
}


//----- (08003088) --------------------------------------------------------
void vlot_cmp1_regulation()
{//负载调节
  u32 val; // r0@1
  signed int i; // r1@1
  u32 current1; // r0@4
//  u32 val2; // r0@10
//  signed int j; // r1@10
//  u32 current2; // r0@13

	/********motor1************/
  val = 0;
  for ( i = 0; i < 4; i = (u8)(i + 1) )
    val = (motor1_load_buf_074[i] + val);//负载         //motor1_load_buf_074[get_adc_cnt_058] = ADC2->JDR3; VCCL
  current1 = val >> 2;                                  //current1：运行中的实时电压值
  motor1_speed_0C4 = current1 - motor1_load_ref_0C0;    //motor1_load_ref_0C0：开机自检时的标定值
  if ( (motor1_load_ref_0C0 + 717 >= current1) &&       //实时电流值不超过静态电流值+717 
		((signed int)vol_val_032 > 1032) )                  //vol_val_032:实时电池电压  电池电压足够
  {
    flag_motor1_reg_slow_0BE = 0; //电池电压足够，工作电流不大于静态电流+717
  }
  else
  {
    flag_motor1_reg_slow_0BE = 1; //电池电压不足
    if ( motor1_stat_volt_q_d.qV_Component1 >= 0 )
      --motor1_stat_volt_q_d.qV_Component1;
    else
      ++motor1_stat_volt_q_d.qV_Component1;//负载调节
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
//      ++motor2_stat_volt_q_d.qV_Component1;//负载调节
//  }
}

//----- (08005D00) --------------------------------------------------------
void get_motor_state()
{
	if(flag_charging_085 //充电标志位
		&& (flag_mpu3_online2_1D3 || flag_mpu2_online2_1D2)) 
		flag_charging_mpu_online_20C = 1;
	else flag_charging_mpu_online_20C = 0;
	
  if ( motor1_dir_flag_0EE == motor2_dir_flag_160 )
  {//电机同向
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

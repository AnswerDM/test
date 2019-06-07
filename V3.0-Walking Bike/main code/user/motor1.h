#ifndef __MOTOR1_H
#define __MOTOR1_H		
#include "extern.h"

u8 error_motor1_pos_flag_0D2;
u8 motor1_dir_flag_last_0D3;
//s8 motor1_pos_diff_0D4;
u8 motor1_cur_hall_0D5;
u8 motor1_last_hall_0D6;
u8 cycle_motor1_phase_cnt_0D7;
u8 flag_motor1_roll_begin_0D8;
u8 flag_motor1_roll_ok_0D9;
u16 motor1_time_phase_switch_0DA=0xafc;
u16 motor1_cur_phase_0DC;
u16 motor1_electrical_angle_bak_0DE;
u16 motor1_unknown_para1_0E0;//不知道的参数
s16 motor1_angle_diff_0E2;
u16 moter1_roll_time_laset_0E4;
u8 flag_motor1_shake_0E6;//可能是方向
u8 motor1_angle_para1_0E7;
u8 moter1_phase_num_0E8;
u8 cycle_motor1_cnt4_0E9;
s16 flag_motor1_move_0EA;//角度标志
u16 moter1_roll_time_0EC;
u16 motor1_dir_flag_0EE;//电机方向标志

u16 motor1_angle_para_a_0F0;
u16 motor1_angle_para_c_0F2;
u16 motor1_electrical_angle_0F4;
u16 motor1_angle_para_d_0F6;
u16 motor1_angle_para_e_0F8;
u16 motor1_angle_para_f_0FA;
u16 motor1_angle_para_g_0FC;

u16 moter1_angle_buf_234[6];//角度数组

u16 motor1_Angle;
//u32 motor1_phase_last_bak_100;
/////////////////////////
//电机1
Volt_Components motor1_stat_volt_q_d;//转子定向坐标系
s16 motor1_Curr_q_d_108;//负载调节park变换
s16 motor1_flow_integral;
Curr_Components motor1_curr_a_b;//10C 当前相电流结构
Curr_Components  motor1_Curr_alfa_beta; //114 
Volt_Components motor1_vol_a_b;//124
Trig_Components  motor1_vector_Components; //11C 

void motor1_get_angle(void);
void motor1_init_para(void);
void motor1_flow_reg(void);
void motor1_Clarke(void);
void motor1_Park(void);
void motor1_Rev_Park(void);
void motor1_motor_ctrl(void);
#endif


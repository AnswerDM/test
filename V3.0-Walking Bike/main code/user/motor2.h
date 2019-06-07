#ifndef __MOTOR2_H
#define __MOTOR2_H		
#include "extern.h"

//电机2
Volt_Components motor2_stat_volt_q_d;//124
s16 motor2_Curr_qd_Component1_128;
s16 motor2_flow_integral;
Curr_Components motor2_curr_a_b;//12C 当前相电流结构
Curr_Components  motor2_Curr_alfa_beta; //134
Curr_Components  motor2_Curr_q_d;
Volt_Components motor2_vol_a_b;//138 2   13A 1
Trig_Components  motor2_vector_Components; //13C 
/////////////////////////
u8 error_motor2_pos_flag_144;
u8 motor2_dir_flag_last_145;//上一次霍尔改变的方向
//s8 motor2_pos_diff_146;
u8 motor2_cur_hall_147;
u8 motor2_last_hall_148;
u8 cycle_motor2_phase_cnt_149;

u8 flag_motor2_roll_begin_14A;
u8 flag_motor2_roll_ok_14B;
u16 motor2_time_phase_switch_14C=0xafc;
u16 motor2_cur_phase_14E;
u16 motor2_electrical_angle_bak_150;
u16 motor2_unknown_para1_152;
s16 motor2_angle_diff_154;
u16 moter2_roll_time_laset_156;
u8 flag_motor2_shake_158;
u8 motor2_angle_para1_159;
u8 moter2_phase_num_15A;
u8 cycle_motor2_cnt4_15B;
u8 flag_motor2_move_15C;
u16 moter2_roll_time_15E;
u16 motor2_dir_flag_160;

u16 motor2_angle_para_a_162;
u16 motor2_angle_para_c_164;
u16 motor2_electrical_angle_166;
u16 motor2_angle_para_d_168;
u16 motor2_angle_para_e_16A;
u16 motor2_angle_para_f_16C;
u16 motor2_angle_para_g_16E;

u16 motor2_Angle;
//u16 motor2_phase_bak_172;
u16 moter2_phase_time_buf_240[6];

void motor2_init_para(void);
void motor2_flow_reg(void);
void motor2_Clarke(void);
void motor2_Park(void);
void motor2_Rev_Park(void);
void motor2_motor_ctrl(void);
void motor2_get_angle(void); // weak
#endif


#ifndef __ALGORITHM_H
#define __ALGORITHM_H		
#include "extern.h"


u8 flag_dormancy_reset_039;
u16 time1_cnt_056;//时间中断计次
u8 self_check_ok_038;//自检ok标志

u16 get_adc_cnt_058;//获取adc计
u8 time1_ok_05A;//tim1到时



u16 motor2_u_cur_05C;//adc的值 
u16 motor2_w_cur_05E;
u16 motor2_load_buf_060[4]={0};//可能是电流值 4个值一平均 

u16 bet_vol_buf_068[4]={0};//可能是电压值的缓冲

u16 motor1_u_cur_070;//adc的值 
u16 motor1_w_cur_072;
u16 motor1_load_buf_074[4];//可能是电流值 4个值一平均 

u16 boot_vol_buf_07C[4];//可能是电压值的缓冲

u8 flag_unknown_2_086;
u8 flag_unknown_3_087;

u8 get_adc_ok_0B4;//获取adc ok

u8 flag_motor2_reg_slow_0B5;
u16 motor2_error_el_vol_flag_0B6;//电机1电压故障

u16 motor2_load_ref_0B8;//速度基准
s16 para_motor2_attitude_0BA;

s16 motor2_speed_0BC;
s16 motor1_speed_0C4;
//u8 ram_099;
u8 flag_motor1_reg_slow_0BE;
u8 motor1_error_el_vol_flag_0BF;//电机2电压故障
u16 motor1_load_ref_0C0;//速度基准
s16 para_motor1_attitude_0C2;

u8 MOTOR_PHASE_SEQUENCE_120[8]={0,2,4,3,6,1,5};//120度无刷电机 相位顺序表

///////////////////////////////////////////////////
u8 flag_unknown_7_186;
u8 flag_unknown_8_188;

s16 motor1_hPhaseAOffset_110;
s16 motor1_hPhaseBOffset_112;
s16 motor2_hPhaseAOffset_130;
s16 motor2_hPhaseBOffset_132;



void self_checking(void);
void vlot_cmp1_regulation(void);//踏板速度调节
void get_motor_state(void);
#endif 

#ifndef __ATTITUDE_H
#define __ATTITUDE_H		
#include "extern.h"

float diff_last_1D8;
float motor1_cor_para_angle;//修正参数 之前把他当成了局部变量
float motor2_cor_para_angle;
float motor1_integral_1E8;//motor1积分项
float motor2_integral_1EC;//motor2积分项
float attitude_motor1_angle_last_1F4;//上一个角度
float pid_ki;
float attitude_motor2_angle_last_200;//上一个角度
u8 flag_motor2_status_20A;//电机启动标志
u8 flag_motor1_status_20B;//
u8 flag_charging_mpu_online_20C;//充电时 踩下踏板
u8 error_vice_20D;
u8 flag_two_motor_dir_20E;
u8 flag_mpu2_online2_bak_20F;
u8 flag_mpu3_online2_bak_210;
u8 flag_mpu2_ok_211;
u8 flag_mpu3_ok_212;

float dir_offset;//

u8 mpu6050_1_data_1BC[2];
float mpu_2_angle_1C0;//姿态传来的角度
float mpu_3_angle_1C4;//姿态板传来的角度
float attitude_motor2_angle_1C8;//最终修正角度 motor2
float attitude_motor1_angle_1CC;//最终修正角度 motor1
u8 flag_mpu2_online2_1D2;

u8 cycle_unknown_cnt1_0A8;
u8 flag_unknown_4_0A9;
u8 cycle_unknown_cnt3_0AA;
u8 flag_unknown_5_0AB;
u8 cycle_unknown_cnt5_0AC;
u8 flag_unknown_6_0AD;
u16 cycle_unknown_cnt6_0AE;
u16 cycle_unknown_cnt4_0B0;



void check_attitude(void);
float get_diroffset(float acce, float offset);
#endif


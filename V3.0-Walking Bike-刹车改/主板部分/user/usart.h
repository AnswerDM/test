#ifndef __USART_H
#define __USART_H		
#include "extern.h"

u8 uart2_send_cnt;

u8 flag_mpu2_online1_174;
u8 flag_mpu3_online1_175;

u8 motor2_state_1_176;//通过通讯发送
u8 motor1_state_1_177;
u8 motor_state_4_bak_178;
u8 motor_state_vol_bak_179;
u8 motor_state_7_17A;
u8 motor_state_8_17B;
u8 motor_state_6_17C;
u8 motor_state_5_17D;

u8 motor_state_vol_1BB;
u8 motor_state_4_1BA;
u8 get_usart3_cnt;
u8 uart3_send_cnt_1B9;
float mpu2_last_194;
float mpu_2_198;
u8 rec_usart3_buf_19E[7];//通讯3数据
float mpu3_last_1A8;
u8 get_usart2_cnt;
u8 cycle_cnt_usart2_18A;
u8 rec_usart2_buf_18B[7];
u8 error_angle_186;//姿态板角度过大

u8 error_1D0;
u8 error_1D1;
u8 cycle_cnt_usart3_19D;
u8 flag_mpu3_online2_1D3;
u16 time_out_usart2_cnt_192;
u32 time_out_usart3_cnt_1A4;

u8 flag_mpu2_unchange_17E;
u8 flag_mpu3_unchange_17F;

u8 uart2_data[6];
u8 uart3_data[6];
void get_usart2(void);
void get_usart3(void);
void usart_send(void);
void get_motor_state_to_usart(void);//获取当前状态发送给小板
void check_vice(void);//检查副板


#endif


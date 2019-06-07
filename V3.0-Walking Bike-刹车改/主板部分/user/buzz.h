#ifndef __BUZZ_H
#define __BUZZ_H		
#include "extern.h"



u8 flag_buzz_poweron_08A;
u8 buzz_power_on_type_08B;
u8 cycle_buzz_cnt1_08C;
u8 flag_pa12_ok_last_08D;
u8 flag_mpu2_online2_last_08E;
u8 flag_mpu3_online2_last_08F;

u8 flag_buzz_ok_1_084;//buzz鸣叫完成
u8 flag_buzz_unknown1_090;//开机buzz完成
u8 flag_buzz_unknown2_091;
u8 flag_buzz_unknown3_092;
u8 flag_buzz_unknown4_093;
u8 flag_unknown_2_bak_094;
u8 buzz_cnt_095;//嗡鸣器计次
u8 buzz_total_096;
u8 buzz_on_097;//嗡鸣器开关
u16 buzz_type_0B2;


void buzz_ctrl_all(void);
void buzz_ctrl(void);

#endif



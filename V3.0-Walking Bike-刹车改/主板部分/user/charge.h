#ifndef __CHARGE_H
#define __CHARGE_H	

#include "extern.h"


u8 flag_unknown_1_02A;//不知道的标志位
u8 flag_vol_low_02B;
u16 vol_val_bak_02C=0xffff;
s16 cycle_vol_cnt1_02E;
u8 error_vol_flag_030;//电压故障标志
u8 flag_vol_lower_031;
u16 vol_val_032;// 电压值
u8 flag_vol_low_03A;
u8 flag_charging_085;//pa12标志
u8 flag_dormancy_098;

u16 cycle_vol_cnt_09A;//电压检测循环计次
u16 cycle_vol_cnt3_high_09C;
u32 cycle_error_cnt_0A0;//故障循环计次
u16 cycle_vol_cnt2_0A4;
u8 flag_charge_cnt1_0A6;
u8 flag_charge_cnt2_0A7;

void get_vol(void);
void get_charger_status(void);//获取充电器状态
void check_boot(void);
#endif



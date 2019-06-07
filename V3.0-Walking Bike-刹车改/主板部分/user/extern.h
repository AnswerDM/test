#ifndef __EXTERN_H
#define __EXTERN_H		
#include "stm32f10x.h"	
#include "math.h"
//#include "usart.h"


typedef struct 
{
  s16 qI_Component1;
  s16 qI_Component2;
} Curr_Components;

typedef struct 
{
  s16 qV_Component1;
  s16 qV_Component2;
} Volt_Components; 
							
typedef struct
{
  s16 hCos;
  s16 hSin;
} Trig_Components;	
		   		   

/**********main***************/
extern int motor_direction ;




extern u8 flag_unknown_1_02A;
extern u8 flag_vol_low_02B;
extern s16 cycle_vol_cnt1_02E;
extern u8 error_vol_flag_030;//电压故障标志
extern u8 flag_vol_lower_031;
extern u16 vol_val_032;// 电压值
extern u8 self_check_ok_038;//自检ok标志
extern u8 flag_dormancy_reset_039;//休眠重启
extern u8 flag_vol_low_03A;

extern u8 time1_ok_05A;//tim1到时
extern u8 error_motor_line_05B;
//电压电流寄存器
extern u16 bet_vol_buf_068[4];//可能是电压值的缓冲
extern u16 boot_vol_buf_07C[4];//可能是电压值的缓冲

extern u8 flag_buzz_ok_1_084;
extern u8 flag_charging_085;
extern u8 flag_unknown_2_086;
extern u8 flag_unknown_3_087;

extern u16 buzz_type_0B2;
extern u8 get_adc_ok_0B4;//获取adc ok
extern u16 motor2_error_el_vol_flag_0B6;//电机1电压故障
extern s16 para_motor2_attitude_0BA;//调节参数1
extern s16 motor2_speed_0BC;
extern u8 motor1_error_el_vol_flag_0BF;//电机2电压故障
extern s16 para_motor1_attitude_0C2;
extern s16 motor1_speed_0C4;

extern u8 MOTOR_PHASE_SEQUENCE_120[8];

extern u8 error_motor1_pos_flag_0D2;
extern s16 flag_motor1_move_0EA;
extern u16 moter1_roll_time_0EC;
extern u16 motor1_dir_flag_0EE;//电机方向标志
/////////////////////////
//电机1
extern Volt_Components motor1_stat_volt_q_d;//104 反park变换 最后赋值给pwm
extern Curr_Components motor1_curr_a_b;//10C 当前相电流结构

/***********motor2.c***************/
//电机2
extern Volt_Components motor2_stat_volt_q_d;//124
extern Curr_Components motor2_curr_a_b;//12C 当前相电流结构
//
extern u8 error_motor2_pos_flag_144;//错误标志
extern u8 flag_motor2_move_15C;
extern u16 moter2_roll_time_15E;
extern u16 motor2_dir_flag_160;

extern u8 flag_mpu2_unchange_17E;
extern u8 flag_mpu3_unchange_17F;
extern float dir_offset;
extern u8 error_angle_186;//姿态板角度过大

extern u8 flag_unknown_7_186;
extern u8 flag_unknown_8_188;

extern u8 mpu6050_1_data_1BC[2];
extern float mpu_2_angle_1C0;
extern float mpu_3_angle_1C4;
extern float attitude_motor2_angle_1C8;
extern float attitude_motor1_angle_1CC;
extern u8 flag_mpu2_online2_1D2;

extern u8 flag_motor2_status_20A;
extern u8 flag_motor1_status_20B;
extern u8 flag_charging_mpu_online_20C;//充电时 踩下踏板
extern u8 error_vice_20D;//小板错误
extern u8 flag_two_motor_dir_20E;
extern u8 flag_mpu2_online2_bak_20F;
extern u8 flag_mpu3_online2_bak_210;
extern u8 flag_mpu2_ok_211;
extern u8 flag_mpu3_ok_212;



extern u8 flag_dormancy_reset_039;//休眠重启
extern u8 flag_charging_085;
extern u8 flag_unknown_2_086;


extern int power_level ;
extern int speed_level ;

/**********charge.h***************/
extern void get_vol(void);
extern void get_charger_status(void);//获取充电器状态
extern void check_boot(void);//休眠检测
/**********attitude.h***************/
extern void check_attitude(void);
extern float get_diroffset(float angle_m_cf, float gyro_m_cf);

/**********algorithm.h***************/
extern void self_checking(void);
extern void vlot_cmp1_regulation(void);//踏板速度调节
extern void get_motor_state(void);
/**********triangle***************/
extern s16 get_sin(u16); // weak
extern s16 get_cos(u32 a1);
/**********motor2***************/
extern void motor2_init_para(void);
extern void motor2_flow_reg(void);
extern void motor2_Clarke(void);
extern void motor2_Park(void);
extern void motor2_Rev_Park(void);
extern void motor2_motor_ctrl(void);
extern void motor2_get_angle(void); // weak
/**********motor1***************/
extern void motor1_get_angle(void);
extern void motor1_init_para(void);
extern void motor1_flow_reg(void);
extern void motor1_Clarke(void);
extern void motor1_Park(void);
extern void motor1_Rev_Park(void);
extern void motor1_motor_ctrl(void);

/**********buzz***************/
extern void buzz_ctrl_all(void);
extern void buzz_ctrl(void);

/**********led***************/
extern void led1_ctrl(void);//控制led闪烁频率 故障指示
/**********usart***************/
extern u8 flag_mpu2_online1_174;
extern u8 flag_mpu3_online1_175;
extern u8 get_usart3_cnt;
extern u8 error_1D0;
extern u8 error_1D1;
extern u8 cycle_cnt_usart3_19D;
extern u8 flag_mpu3_online2_1D3;
extern void get_usart2(void);
extern void get_usart3(void);
extern void usart_send(void);
extern void get_motor_state_to_usart(void);//获取当前状态发送给小板
extern void check_vice(void);//检查副板


/**********init***************/
extern void init(void);


/*********flash****************/
extern u16 flash_para8_046;
extern u16 flash_para7_048;
extern u16 flash_para5_04E;
extern u16 flash_para4_050;
extern u16 flash_para2_052;
extern u16 flash_para3_054;
extern u8 flag_flash_write3_218;
extern u8 flag_flash_write4_220;
extern u8 flag_flash_write5_228;
extern u8 flag_flash_write6_230;

extern void reset_flash_2(void);
extern void read_flash_2(void);//读参数
extern void reset_flash_3(void);
extern void reset_flash_4(void);
extern void reset_flash_5(void);
extern void reset_flash_6(void);


extern s32 speedCounter_Far ;
extern s32 speedCounter_Near ;

extern int val1_final_xiepo  ;
extern unsigned char data_buf[14];
extern int count_usart2_rec;
extern u8 buf_rec_usart_2[10];
#endif

#ifndef __ALGORITHM_H
#define __ALGORITHM_H		
#include "extern.h"


u8 flag_dormancy_reset_039;
u16 time1_cnt_056;//ʱ���жϼƴ�
u8 self_check_ok_038;//�Լ�ok��־

u16 get_adc_cnt_058;//��ȡadc��
u8 time1_ok_05A;//tim1��ʱ



u16 motor2_u_cur_05C;//adc��ֵ 
u16 motor2_w_cur_05E;
u16 motor2_load_buf_060[4]={0};//�����ǵ���ֵ 4��ֵһƽ�� 

u16 bet_vol_buf_068[4]={0};//�����ǵ�ѹֵ�Ļ���

u16 motor1_u_cur_070;//adc��ֵ 
u16 motor1_w_cur_072;
u16 motor1_load_buf_074[4];//�����ǵ���ֵ 4��ֵһƽ�� 

u16 boot_vol_buf_07C[4];//�����ǵ�ѹֵ�Ļ���

u8 flag_unknown_2_086;
u8 flag_unknown_3_087;

u8 get_adc_ok_0B4;//��ȡadc ok

u8 flag_motor2_reg_slow_0B5;
u16 motor2_error_el_vol_flag_0B6;//���1��ѹ����

u16 motor2_load_ref_0B8;//�ٶȻ�׼
s16 para_motor2_attitude_0BA;

s16 motor2_speed_0BC;
s16 motor1_speed_0C4;
//u8 ram_099;
u8 flag_motor1_reg_slow_0BE;
u8 motor1_error_el_vol_flag_0BF;//���2��ѹ����
u16 motor1_load_ref_0C0;//�ٶȻ�׼
s16 para_motor1_attitude_0C2;

u8 MOTOR_PHASE_SEQUENCE_120[8]={0,2,4,3,6,1,5};//120����ˢ��� ��λ˳���

///////////////////////////////////////////////////
u8 flag_unknown_7_186;
u8 flag_unknown_8_188;

s16 motor1_hPhaseAOffset_110;
s16 motor1_hPhaseBOffset_112;
s16 motor2_hPhaseAOffset_130;
s16 motor2_hPhaseBOffset_132;



void self_checking(void);
void vlot_cmp1_regulation(void);//̤���ٶȵ���
void get_motor_state(void);
#endif 

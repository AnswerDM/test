#ifndef __PID_H__
#define __PID_H__

#define VV_MAX  1024 		 //
#define VV_MIN  0  	   //
#define VV_DEADLINE 0	   //




//struct
typedef struct PID			
{
	int vi_Ref;	         //�ٶ��趨ֵ
	int vi_FeedBack;     //�ٶȷ�����
  int vi_PreError;	   //�ٶ����ֵ,vi_Ref - vi_FeedBack
  int vi_PreDerror;	   //�ٶ��������,d_error-PreDerror;
	float v_Kp;		       //????,Kp = Kp
	float v_Ki;		       //????,Ki = Kp * ( T / Ti )
	float v_Kd;		       //????,Kd = KP * Td * T
	float vl_PreU;		     //PID???
}PID;
// Function prototypes
extern void PIDInit(void);  
extern int v_PIDCalc( PID *pp );

//extern

extern PID sPID_Near;
extern PID sPID_Far;



extern int motor_speed_near_val ; //PID��������ֵ
extern int motor_speed_far_val ;  //PID��������ֵ

extern int motor_speed_near_set; //�ٶ��趨ֵ
extern int motor_speed_far_set ;  //�ٶ��趨ֵ
#endif /* __SCHEDULE_H__ */

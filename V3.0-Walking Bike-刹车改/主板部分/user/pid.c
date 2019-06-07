#include "pid.h"


PID sPID_Near;
PID sPID_Far;

float SPEED_KP_Near = 8.0;
float SPEED_KI_Near = 120.0;
float SPEED_KD_Near = 80.0;

float SPEED_KP_Far = 0.0;
float SPEED_KI_Far = 0.0;
float SPEED_KD_Far = 0.0;

void PIDInit(void)          
{	
    sPID_Near.vi_Ref = 0 ;	      	 
    sPID_Near.vi_FeedBack = 0 ;		
            
    sPID_Near.vi_PreError = 0 ;	  	
    sPID_Near.vi_PreDerror = 0 ;	  	
    
    sPID_Near.v_Kp = SPEED_KP_Near;       
    sPID_Near.v_Ki = SPEED_KI_Near;    
    sPID_Near.v_Kd = SPEED_KD_Near;     													 
            
    sPID_Near.vl_PreU = 0;		
  /*********************************************/ 
    sPID_Far.vi_Ref = 0 ;	      	 
    sPID_Far.vi_FeedBack = 0 ;		
            
    sPID_Far.vi_PreError = 0 ;	  	
    sPID_Far.vi_PreDerror = 0 ;	  	
    
    sPID_Far.v_Kp = SPEED_KP_Far;       
    sPID_Far.v_Ki = SPEED_KI_Far;    
    sPID_Far.v_Kd = SPEED_KD_Far;     													 
            
    sPID_Far.vl_PreU = 0;		
}
int  error,d_error,dd_error;
int v_PIDCalc( PID *pp )
{
     

     error = (int)(pp->vi_Ref) - (int)(pp->vi_FeedBack);	// 偏差计算
     d_error = error - (int)(pp->vi_PreError);
     dd_error = d_error - (int)pp->vi_PreDerror;

     pp->vi_PreError = error;		//存储当前偏差
     pp->vi_PreDerror = d_error;

     pp->vl_PreU += (pp -> v_Kp * d_error + pp -> v_Ki * error + pp->v_Kd*dd_error)/1000;
     
     if( pp->vl_PreU >= VV_MAX ) 		//速度PID，防止调节最高溢出
     {
          pp->vl_PreU = VV_MAX ;
     }
     else if( pp->vl_PreU <= VV_MIN)	//速度PID，防止调节最低溢出
     {
          pp->vl_PreU = VV_MIN;
     }

     return ((int)pp->vl_PreU);		// 返回预调节占空比


//    int  error;//,d_error,dd_error;
//
//    error = (int)(pp->vi_Ref) - (int)(pp->vi_FeedBack);	// ????
//
//    pp->vl_PreU =  (int)(pp -> v_Kp *error)/10;
//    
//    if( pp->vl_PreU >= VV_MAX ) 		//??PID,????????
//    {
//         pp->vl_PreU = VV_MAX ;
//    }
//    else if( pp->vl_PreU <= VV_MIN)	//??PID,????????
//    {
//         pp->vl_PreU = VV_MIN;
//    }
//
//    return (pp->vl_PreU);		// ????????
}

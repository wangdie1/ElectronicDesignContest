#include "Control.h"
// #include "myglobals.h"

 #include "mytype.h"

PID_Para_t SpeedPID,SpeedPID1;//PositionPID;
s32 SpeedErrorSum=0;//,PositionErrorSum;//A
s32 SpeedErrorSum1=0;//,PositionErrorSum1;//B
s16 SpeedError;//,PositionError;


/*************************PID参数初始化************************/
void PID_Init(void)
{
	
	SpeedPID.Kp = SPEED_KP;
	SpeedPID.Ki = SPEED_KI ;
	SpeedPID.ErrorBond = SPEED_ERROR_BOND ;
	
	SpeedPID1.Kp = SPEED1_KP;
	SpeedPID1.Ki = SPEED1_KI ;
	SpeedPID1.ErrorBond = SPEED1_ERROR_BOND ;
	
// 	PositionPID.Kp = POSITION_KP ;
// 	PositionPID.Ki = POSITION_KI ;
// 	PositionPID.ErrorBond = POSITION_ERROR_BOND ;
 	SpeedErrorSum=0;	

//   PositionErrorSum=0;
}

void ErrorClear(void )
{
	 	SpeedErrorSum=0;	
// 		PositionErrorSum=0;
		 SpeedErrorSum1=0;	
// 		PositionErrorSum1=0;
}


/*********************速度环******************/
s32  SpeedPID_Regulator(s32 SpeedError)
{
	s32 PWM;
 	if(abs(SpeedError )>SpeedPID.ErrorBond )
 	{
//  		if((SpeedErrorSum < (INT32_MAX-abs(SpeedError)))&&(SpeedErrorSum>(INT32_MIN+abs(SpeedError)) ))
		SpeedErrorSum += SpeedError; 
 	}
	PWM = SpeedError *SpeedPID.Kp+SpeedErrorSum *SpeedPID.Ki ;
	if(PWM>=PWM_MAX)
				PWM=PWM_MAX;
	if(PWM<=PWM_MIN)
			PWM=PWM_MIN;
	return PWM;
}
/*********************速度环******************/
s32  SpeedPID1_Regulator(s32 SpeedError)
{
	s32 PWM;
 	if(abs(SpeedError )>SpeedPID1.ErrorBond )
 	{
//  		if((SpeedErrorSum < (INT32_MAX-abs(SpeedError)))&&(SpeedErrorSum>(INT32_MIN+abs(SpeedError)) ))
		SpeedErrorSum1 += SpeedError; 
 	}
	PWM = SpeedError *SpeedPID1.Kp+SpeedErrorSum1 *SpeedPID1.Ki ;
	if(PWM>=PWM_MAX)
				PWM=PWM_MAX;
	if(PWM<=PWM_MIN)
			PWM=PWM_MIN;
	return PWM;
}



// /***************************位置换*****************************/
// s32 PositionPID_Regulator(s32 PositionError)
// {
// 	s32 Speed;
// 	if(abs(PositionError)>=PositionPID.ErrorBond )
// 	{
// 		//防止积分误差溢出
//  		if((PositionErrorSum <(INT32_MAX-abs(PositionError)))&&(PositionErrorSum >(INT32_MIN+abs(PositionError))) )
// 		PositionErrorSum += PositionError ;
// 	}
// 	Speed=PositionPID.Kp*PositionError+PositionPID.Ki * PositionErrorSum;
// // 	if(Speed>=SPEED_MAX)
// // 	{
// // 		Speed = SPEED_MAX;
// // 	}
// // 	if(Speed<=SPEED_MIN)
// // 		Speed = SPEED_MIN;
// 	return Speed;
// }
// /*************************PID_Regulator*********************/




#include "Control.h"

/*************************控制器参数初始化************************/
void Controller_Init(void)
{
	/* PID 反馈控制器参数初始化 */
	/*速度环*/
	SpeedPID.Kp = MAXON_RE25_SPEED_KP; //#define MAXON_RE25_SPEED_KP 			(float)			1
	SpeedPID.Ki = MAXON_RE25_SPEED_KI; //define MAXON_RE25_SPEED_KI 			(float)			0.05
	SpeedPID.Kd = 0;
	SpeedPID.ErrorBond = 0 ;
	SpeedPID.ErrorPre =0;
	SpeedPID.OutputMax = PWM_MAX;       //#define PWM_MAX			999 
	SpeedPID.OutputMin = PWM_MIN;       //#define PWM_MIN			-999
	SpeedPID.ErrorSum =  0;
	SpeedPID.ErrorSumMax = INT32_MAX;   //32位的最大值
	SpeedPID.ErrorSumMin = INT32_MIN;   //32位的最小值
	
	/*位置环*/
	PositionPID.Kp = MAXON_RE25_POSITION_KP ;  //#define MAXON_RE25_POSITION_KP  	(float)			30
	PositionPID.Ki = 0 ;
	PositionPID.Kd = MAXON_RE25_POSITION_KD;   //#define MAXON_RE25_POSITION_KD  	(float)			5
	PositionPID.ErrorBond = 0;
	PositionPID.ErrorPre  = 0;
	PositionPID.OutputMax = SPEED_MAX;   //#define SPEED_MAX   MAXON_RE25_SPEED_MAX  ..  #define MAXON_RE25_SPEED_MAX	 3600    rmp * 10
	PositionPID.OutputMin = SPEED_MIN;   //#define SPEED_MIN		MAXON_RE25_SPEED_MIN   ..
	PositionPID.ErrorSum  = 0;
	PositionPID.ErrorSumMax = INT32_MAX;
	PositionPID.ErrorSumMin = INT32_MIN;
	
	/* FeedForward 前馈控制器参数初始化 */
	PositionFF.Kv = 1.5;//1.6;
	PositionFF.Ka = 0;
	PositionFF.FFmax = SPEED_MAX;
	PositionFF.FFmin = SPEED_MIN;
}

/* 清除积分误差 */
void ErrorClear(PID_Typedef *PID )
{
	PID->ErrorSum=0;
	
}

/*********************速度环*0*****************/
s32  SpeedPI_Regulator(s32 SpeedError,PID_Typedef *PID)//只需要PI
{
	s32 output;
 
	PID->ErrorSum += SpeedError; 
	/* 抗积分饱和 */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = SpeedError*PID->Kp + PID->ErrorSum *PID->Ki ;//计算输出
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}



/***************************位置环0*****************************/
s32 PositionPID_Regulator(s32 PositionError,PID_Typedef *PID)
{
	s32 output;
 
	PID->ErrorSum += PositionError; 
	/* 抗积分饱和 */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = PositionError*PID->Kp + PID->ErrorSum *PID->Ki ;//计算输出
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}

/*P控制器*/
double P_Controller(float Error,PID_Typedef *PID)
{
	double output;
	
	output = PID->Kp * Error;
	/*输出限制幅度*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	
	return output;
}

/*PD 控制器*/
double PD_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double dTerm;
	
	pTerm = PID->Kp * Error;
	dTerm = PID->Kd * (Error - PID->ErrorPre);
	PID->ErrorPre = Error;
	output = pTerm + dTerm;
	/*输出限制幅度*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	
	return output;
}

/*PI 控制器*/
double PI_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	
	PID->ErrorSum += Error;					//累计误差
	/*避免积分饱和溢出*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum = PID->ErrorSumMin;
	}
	iTerm = PID->Ki * PID->ErrorSum;//积分作用
	pTerm = PID->Kp * Error;				//比例作用
	output=iTerm+pTerm;
	/*输出限制幅度*/
	if(output > PID->OutputMax)
	{
		output = PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output = PID->OutputMin;
	}
	
	return output;
}

/* 一般的PID Controller  */
double PID_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	double dTerm;
	if(abs(Error) < PID->KiBond)//积分分离 ,小误差是开始积分作用
	{
		PID->ErrorSum+=Error;	//计算误差累计积分
	}
	/* 抗饱和积分*/
	if(PID->ErrorSum>PID->ErrorSumMax)
	{
		PID->ErrorSum=PID->ErrorSumMax;
	}
	else if(PID->ErrorSum<PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
	/*  */
	pTerm=PID->Kp*Error;//P
	iTerm=PID->Ki*PID->ErrorSum;//I
	dTerm=PID->Kd*(Error-PID->ErrorPre);//D
	PID->ErrorPre=Error;//记录前一次误差
	output=  pTerm+iTerm+dTerm;
	
	/* 限幅度输出 */
	if(output>PID->OutputMax)
	{
		output=PID->OutputMax;
	}
	else if(output<PID->OutputMin)
	{
		output=PID->OutputMin;
	}
	
	return output ;
}

double FF_Controller(double rin,FForward_Typedef *FF )
{
	double output;
	
	FF->rinV = rin - FF->rinPre; //一阶微分
	FF->rinA = FF->rinV - FF->rinV_Pre;//二阶微分
	FF->rinPre = rin;
	FF->rinV_Pre = FF->rinV;
	output = FF->rinV * FF->Kv + FF->rinA * FF->Ka ;//
	if(output > FF->FFmax)
	{
		output = FF->FFmax;
	}
	else if(output < FF->FFmin)
	{
		output =  FF->FFmin;
	}
	
	return output;
}


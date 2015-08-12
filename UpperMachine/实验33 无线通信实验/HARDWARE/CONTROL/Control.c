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
/*******************************************************************************************************/

/*********************速度环******************/
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


/*******************************************************************************************************/

/***************************位置环*****************************/
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

/*******************************************************************************************************/

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

/*******************************************************************************************************/

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


/*******************************************************************************************************/

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
/*******************************************************************************************************/

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

/*******************************************************************************************************/

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

/*******************************************************************************************************/

//绝对式PID算法
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{
	if(PID->kp      < 0)
		PID->kp      = -PID->kp;
	if(PID->ki      < 0)
		PID->ki      = -PID->ki;
	if(PID->kd      < 0)
		PID->kd      = -PID->kd;
	if(PID->errILim < 0)
		PID->errILim = -PID->errILim;

	PID->errP = PID->errNow;  //读取现在的误差，用于kp控制

	PID->errI += PID->errNow; //误差积分，用于ki控制

	if(PID->errILim != 0)	   //微分上限和下限
	{
	if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
	else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
	}

	PID->errD = PID->errNow - PID->errOld;//误差微分，用于kd控制

	PID->errOld = PID->errNow;	//保存现在的误差

	PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//计算绝对式PID输出

}

/*******************************************************************************************************/

//增量式PID算法
void PID_IncrementMode(PID_IncrementType* PID)
	{
	float dErrP, dErrI, dErrD;

	if(PID->kp < 0) 
		PID->kp = -PID->kp;
	if(PID->ki < 0)
		PID->ki = -PID->ki;
	if(PID->kd < 0)    PID->kd = -PID->kd;

	dErrP = PID->errNow - PID->errOld1;

	dErrI = PID->errNow;

	dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

	PID->errOld2 = PID->errOld1; //二阶误差微分
	PID->errOld1 = PID->errNow;  //一阶误差微分

	/*增量式PID计算*/
	PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;

	if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

	else PID->ctrOut += PID->dCtrOut;
}





/*****************************************电机速度环伺服***********************************************/
s32 spdTag, spdNow, control;//定义一个目标速度，采样速度，控制量

PID_IncrementType PID_Control;//定义PID算法的结构体    绝对式PID算法
//
void User_PidPositionControl(u16 spdNow)
{
	
	//实际速度
  // spdNow = V2;
	//目标速度
   spdTag = 400;

	//误差值
   PID_Control.errNow = spdTag - spdNow; //计算并写入速度误差
   	
   //PID_Control.kp      = 182.04444145;             //写入比例系数为15  60 ~ 70 %
	PID_Control.kp = 118;
   PID_Control.ki      = 17;              //写入积分系数为5
   PID_Control.kd      = 0;              //写入微分系数为5
   //PID_Control.errILim = 1000;           //写入误差积分上限为1000 下限为-1000

	//把结构体传人
   PID_IncrementMode(&PID_Control);       //执行绝对式PID算法
	
   //读取PID返回值
   control = PID_Control.ctrOut;         //读取控制值

	//把PID得到的速度电机A的PWM中
//   MotorA_PWM_Update(control);        //放入PWM，用于收敛速度的控制中
//	//把PID得到的速度电机B的PWM中
	MotorB_PWM_Update(control);        //放入PWM，用于收敛速度的控制中
}


//s32 wzTag, wzNow, wzcontrol;//定义一个目标速度，采样速度，控制量
//float errNow;
//PID_Typedef PID_WZControl;//定义PID算法的结构体    绝对式PID算法

//void User_wzControl(u16 wzNow)
//{
//	
//	//实际速度
//  // spdNow = V2;
//	//目标位置
//   wzTag = 180;

//	//误差值
//   errNow = wzTag - wzNow; //计算并写入速度误差
//   	
//   PID_WZControl.Kp      = 2;             //写入比例系数为15
//   PID_WZControl.Ki      = 3;              //写入积分系数为5
//   PID_WZControl.Kd      = 0;              //写入微分系数为5
//   PID_WZControl.ErrorBond = 1000;           //写入误差积分上限为1000 下限为-1000

//	//把结构体传人
// control =  PositionPID_Regulator(errNow,&PID_WZControl);       //执行绝对式PID算法
//	
//   //读取PID返回值
////   control = PID_WZControl.ctrOut;         //读取控制值

//	//把PID得到的速度电机A的PWM中
//   MotorB_PWM_Update(control);        //放入PWM，用于收敛速度的控制中
////	//把PID得到的速度电机B的PWM中
////	MotorB_PWM_Update(control);        //放入PWM，用于收敛速度的控制中
//}

#include "Control.h"

/*************************������������ʼ��************************/
void Controller_Init(void)
{
	/* PID ����������������ʼ�� */
	/*�ٶȻ�*/
	SpeedPID.Kp = MAXON_RE25_SPEED_KP; //#define MAXON_RE25_SPEED_KP 			(float)			1
	SpeedPID.Ki = MAXON_RE25_SPEED_KI; //define MAXON_RE25_SPEED_KI 			(float)			0.05
	SpeedPID.Kd = 0;
	SpeedPID.ErrorBond = 0 ;
	SpeedPID.ErrorPre =0;
	SpeedPID.OutputMax = PWM_MAX;       //#define PWM_MAX			999 
	SpeedPID.OutputMin = PWM_MIN;       //#define PWM_MIN			-999
	SpeedPID.ErrorSum =  0;
	SpeedPID.ErrorSumMax = INT32_MAX;   //32λ�����ֵ
	SpeedPID.ErrorSumMin = INT32_MIN;   //32λ����Сֵ
	
	/*λ�û�*/
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
	
	/* FeedForward ǰ��������������ʼ�� */
	PositionFF.Kv = 1.5;//1.6;
	PositionFF.Ka = 0;
	PositionFF.FFmax = SPEED_MAX;
	PositionFF.FFmin = SPEED_MIN;
}

/* ���������� */
void ErrorClear(PID_Typedef *PID )
{
	PID->ErrorSum=0;
	
}
/*******************************************************************************************************/

/*********************�ٶȻ�******************/
s32  SpeedPI_Regulator(s32 SpeedError,PID_Typedef *PID)//ֻ��ҪPI
{
	s32 output;
 
	PID->ErrorSum += SpeedError; 
	/* �����ֱ��� */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = SpeedError*PID->Kp + PID->ErrorSum *PID->Ki ;//�������
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}


/*******************************************************************************************************/

/***************************λ�û�*****************************/
s32 PositionPID_Regulator(s32 PositionError,PID_Typedef *PID)
{
	s32 output;
 
	PID->ErrorSum += PositionError; 
	/* �����ֱ��� */
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
 	
	output = PositionError*PID->Kp + PID->ErrorSum *PID->Ki ;//�������
	if(output > PID->OutputMax)
				output = PID->OutputMax;
	else if(output < PID->OutputMin)
			output = PID->OutputMin;
	return output;
}

/*******************************************************************************************************/

/*P������*/
double P_Controller(float Error,PID_Typedef *PID)
{
	double output;
	
	output = PID->Kp * Error;
	/*������Ʒ���*/
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

/*PD ������*/
double PD_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double dTerm;
	
	pTerm = PID->Kp * Error;
	dTerm = PID->Kd * (Error - PID->ErrorPre);
	PID->ErrorPre = Error;
	output = pTerm + dTerm;
	/*������Ʒ���*/
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

/*PI ������*/
double PI_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	
	PID->ErrorSum += Error;					//�ۼ����
	/*������ֱ������*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum = PID->ErrorSumMin;
	}
	iTerm = PID->Ki * PID->ErrorSum;//��������
	pTerm = PID->Kp * Error;				//��������
	output=iTerm+pTerm;
	/*������Ʒ���*/
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

/* һ���PID Controller  */
double PID_Controller(float Error,PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	double dTerm;
	if(abs(Error) < PID->KiBond)//���ַ��� ,С����ǿ�ʼ��������
	{
		PID->ErrorSum+=Error;	//��������ۼƻ���
	}
	/* �����ͻ���*/
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
	PID->ErrorPre=Error;//��¼ǰһ�����
	output=  pTerm+iTerm+dTerm;
	
	/* �޷������ */
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
	
	FF->rinV = rin - FF->rinPre; //һ��΢��
	FF->rinA = FF->rinV - FF->rinV_Pre;//����΢��
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

//����ʽPID�㷨
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

	PID->errP = PID->errNow;  //��ȡ���ڵ�������kp����

	PID->errI += PID->errNow; //�����֣�����ki����

	if(PID->errILim != 0)	   //΢�����޺�����
	{
	if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
	else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
	}

	PID->errD = PID->errNow - PID->errOld;//���΢�֣�����kd����

	PID->errOld = PID->errNow;	//�������ڵ����

	PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//�������ʽPID���

}

/*******************************************************************************************************/

//����ʽPID�㷨
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

	PID->errOld2 = PID->errOld1; //�������΢��
	PID->errOld1 = PID->errNow;  //һ�����΢��

	/*����ʽPID����*/
	PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;

	if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

	else PID->ctrOut += PID->dCtrOut;
}





/*****************************************����ٶȻ��ŷ�***********************************************/
s32 spdTag, spdNow, control;//����һ��Ŀ���ٶȣ������ٶȣ�������

PID_IncrementType PID_Control;//����PID�㷨�Ľṹ��    ����ʽPID�㷨
//
void User_PidPositionControl(u16 spdNow)
{
	
	//ʵ���ٶ�
  // spdNow = V2;
	//Ŀ���ٶ�
   spdTag = 400;

	//���ֵ
   PID_Control.errNow = spdTag - spdNow; //���㲢д���ٶ����
   	
   //PID_Control.kp      = 182.04444145;             //д�����ϵ��Ϊ15  60 ~ 70 %
	PID_Control.kp = 118;
   PID_Control.ki      = 17;              //д�����ϵ��Ϊ5
   PID_Control.kd      = 0;              //д��΢��ϵ��Ϊ5
   //PID_Control.errILim = 1000;           //д������������Ϊ1000 ����Ϊ-1000

	//�ѽṹ�崫��
   PID_IncrementMode(&PID_Control);       //ִ�о���ʽPID�㷨
	
   //��ȡPID����ֵ
   control = PID_Control.ctrOut;         //��ȡ����ֵ

	//��PID�õ����ٶȵ��A��PWM��
//   MotorA_PWM_Update(control);        //����PWM�����������ٶȵĿ�����
//	//��PID�õ����ٶȵ��B��PWM��
	MotorB_PWM_Update(control);        //����PWM�����������ٶȵĿ�����
}


//s32 wzTag, wzNow, wzcontrol;//����һ��Ŀ���ٶȣ������ٶȣ�������
//float errNow;
//PID_Typedef PID_WZControl;//����PID�㷨�Ľṹ��    ����ʽPID�㷨

//void User_wzControl(u16 wzNow)
//{
//	
//	//ʵ���ٶ�
//  // spdNow = V2;
//	//Ŀ��λ��
//   wzTag = 180;

//	//���ֵ
//   errNow = wzTag - wzNow; //���㲢д���ٶ����
//   	
//   PID_WZControl.Kp      = 2;             //д�����ϵ��Ϊ15
//   PID_WZControl.Ki      = 3;              //д�����ϵ��Ϊ5
//   PID_WZControl.Kd      = 0;              //д��΢��ϵ��Ϊ5
//   PID_WZControl.ErrorBond = 1000;           //д������������Ϊ1000 ����Ϊ-1000

//	//�ѽṹ�崫��
// control =  PositionPID_Regulator(errNow,&PID_WZControl);       //ִ�о���ʽPID�㷨
//	
//   //��ȡPID����ֵ
////   control = PID_WZControl.ctrOut;         //��ȡ����ֵ

//	//��PID�õ����ٶȵ��A��PWM��
//   MotorB_PWM_Update(control);        //����PWM�����������ٶȵĿ�����
////	//��PID�õ����ٶȵ��B��PWM��
////	MotorB_PWM_Update(control);        //����PWM�����������ٶȵĿ�����
//}

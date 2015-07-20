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

/*********************�ٶȻ�*0*****************/
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



/***************************λ�û�0*****************************/
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


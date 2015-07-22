#include "Control.h"

/*************************������������ʼ��************************/
void Controller_Init(void)
{
	/* PID ����������������ʼ�� */
	SpeedPID.Kp = MAXON_RE25_SPEED_KP;
	SpeedPID.Ki = MAXON_RE25_SPEED_KI;
	SpeedPID.Kd = 0;
	SpeedPID.ErrorBond = 0 ;
	SpeedPID.ErrorPre =0;
	SpeedPID.OutputMax = PWM_MAX;
	SpeedPID.OutputMin = PWM_MIN;
	SpeedPID.ErrorSum =  0;
	SpeedPID.ErrorSumMax = INT32_MAX;
	SpeedPID.ErrorSumMin = INT32_MIN;
	
	
	PositionPID.Kp = MAXON_RE25_POSITION_KP ;
	PositionPID.Ki = 0 ;
	PositionPID.Kd = MAXON_RE25_POSITION_KD;
	PositionPID.ErrorBond = 0;
	PositionPID.ErrorPre  = 0;
	PositionPID.OutputMax = SPEED_MAX;
	PositionPID.OutputMin = SPEED_MIN;
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
	if(abs(Error)<PID->KiBond)//���ַ��� ,С����ǿ�ʼ��������
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


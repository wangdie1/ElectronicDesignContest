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



//����ȫ�ֱ���
float PID_P = 35.0;
float PID_I = 0.00;
float PID_D = 0.00;

void set_PID(u16 P,u16 I,u16 D)
{
	PID_P = P/100.0;
	PID_I = I/100.0;
	PID_D = D/100.0;
}

//PI������
float PI_P = 10;
float PI_I = 0;
void set_PI(u16 P,u16 I)
{
	PI_P = P/100.0;
	PI_I = I/100.0;
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
double PI_Controller(PID_Typedef *PID)
{
	double output;
	double pTerm;
	double iTerm;
	
	//
	if(abs_Double(PID->errNow) < PID->KiBond)//
	{
		PID->ErrorSum+=PID->errNow;	//
	}
	/*������ֱ������*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum = PID->ErrorSumMin;
	}
	
	pTerm = PID->Kp * PID->errNow;				//��������
	iTerm = PID->Ki * PID->ErrorSum;//��������
	
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

//PI������������
PID_Typedef PI_control;
int User_PIControl(float spdNow)
{
	double output;
	PI_control.spdTag = 0;
	if(360 - spdNow < spdNow)
	{
		spdNow = spdNow - 360;
	}
	PI_control.errNow = PI_control.spdTag - spdNow;
	
	//�趨pid����
	PI_control.Kp = PI_P;
	PI_control.Ki = PI_I;
	
	PI_control.ErrorBond = 0;
	PI_control.OutputMax = 979;
	PI_control.OutputMin = -979;
	
	PI_control.ErrorSum = 0;
	PI_control.KiBond = 1000;
	PI_control.ErrorSumMax = INT32_MAX;
	PI_control.ErrorSumMin = INT32_MIN;

	output=PI_Controller(&PI_control);     //?'DD????�?PID??��
	
//	PI_control.control = (int)output;       	//???????��??? ??�?�??��?pwm
//	
//	MotorB_PWM_Update(-PI_control.control); 	
//	
//	return 0;
	return output;
}




/**************************************λ��ʽpid*************************************************/
/* һ���λ��ʽPID  */
double PID_Pos_Controller(PID_Pos_Typedef *PID)
{
	double output;
	double pTerm;//��������
	double iTerm;//��������
	double dTerm;//΢������
	
	//���ַ���
	if(abs_Double(PID->errNow) < PID->KiBond)//���ַ��� ,С����ǿ�ʼ��������
	{
		PID->ErrorSum+=PID->errNow;	//��������ۼƻ���
	}
	
	/* �����ͻ���*/
	if(PID->ErrorSum > PID->ErrorSumMax)
	{
		PID->ErrorSum = PID->ErrorSumMax;
	}
	else if(PID->ErrorSum < PID->ErrorSumMin)
	{
		PID->ErrorSum=PID->ErrorSumMin;
	}
	/*  */
	pTerm=PID->Kp*PID->errNow;//��������
	iTerm=PID->Ki*PID->ErrorSum;//��������
	dTerm=PID->Kd*(PID->errNow-PID->ErrorPre);//΢������
	output=  pTerm+iTerm+dTerm;//pid�����ֵ
	
	PID->ErrorPre=PID->errNow;//��¼ǰһ�����
	
	/* �޷������ */
	if(output > PID->OutputMax)
	{
		output=PID->OutputMax;
	}
	else if(output < PID->OutputMin)
	{
		output=PID->OutputMin;
	}
	return output ;
}

/***************λ�ÿ���**************/
PID_Pos_Typedef PID_Pos;//����PID�㷨�Ľṹ��

//һ���pid�����㷨

//int User_PidPosControl(u16 spdNow,u16 spdTag)
//{
//	double output;
//  // spdNow = 180;
//	PID_Pos.spdTag = spdTag;

//	PID_Pos.errNow =  PID_Pos.spdTag - spdNow; //���㲢д���ٶ����
//   
//   //�޸�pid����
//	PID_Pos.Kp = 35;			   //����ϵ������
//	PID_Pos.Ki = 0; 	           //����ϵ������
//	PID_Pos.Kd = 1;      	       //΢��ϵ������
//	
//	PID_Pos.ErrorBond = 0;
//	PID_Pos.ErrorPre  = 0;
//	PID_Pos.OutputMax = 979;
//	PID_Pos.OutputMin = -979;
//	PID_Pos.ErrorSum  = 0;
//	PID_Pos.KiBond = 1000;
//	PID_Pos.ErrorSumMax = INT32_MAX;
//	PID_Pos.ErrorSumMin = INT32_MIN;
// 
//	output=PID_Pos_Controller(&PID_Pos);     //ִ�о���ʽPID�㷨
//	
////	PID_Pos.control = (int)output;       	//�Կ���ֵȡ�� ��ȡ��ֵ��pwm
////	
////	MotorB_PWM_Update(PID_Pos.control); 	 //����pwm���������ٶȵĿ���
////	
////	return 0;
//	return output;
//}
/**************************************************************************************************/




/**************************************����ʽpid*************************************************/
/* һ�������ʽPID  */
int PID_Inc_Controller(PID_Inc_Typedef *PID_INC)
{
	
	double pTerm,iTerm,dTerm;  //PID����ֵ
	float dErrP, dErrI, dErrD;

	//��������ۼƻ���
	if(abs_Double(PID_INC->errNow) < PID_INC->KiBond)//���ַ��� ,С����ǿ�ʼ��������
	{
		PID_INC->ErrorSum+=PID_INC->errNow;	//��������ۼƻ���
	}
	
	// �����ͻ���
	if(PID_INC->ErrorSum > PID_INC->ErrorSumMax)
	{
		PID_INC->ErrorSum = PID_INC->ErrorSumMax;
	}
	else if(PID_INC->ErrorSum < PID_INC->ErrorSumMin)
	{
		PID_INC->ErrorSum=PID_INC->ErrorSumMin;
	}

	
	dErrP = PID_INC->errNow - PID_INC->errOld1;
	dErrI = PID_INC->errNow;
	dErrD = PID_INC->errNow - 2 * PID_INC->errOld1 + PID_INC->errOld2;

	pTerm = PID_INC ->Kp * dErrP;
	iTerm = PID_INC ->Ki * dErrI;
	dTerm = PID_INC ->Kd * dErrD;	

	/*����ʽPID����*/
	PID_INC->dCtrOut=  pTerm+iTerm+dTerm; 
	
	PID_INC->errOld2 = PID_INC->errOld1; //�������΢��
	PID_INC->errOld1 = PID_INC->errNow;  //һ�����΢��

	
	if(PID_INC->Kp == 0 && PID_INC->Ki == 0 && PID_INC->Kd == 0)
		PID_INC->dCtrOut = 0;
	else
		PID_INC->ctrOut += PID_INC->dCtrOut;
	
	/* �޷������ */
	if(PID_INC->ctrOut>PID_INC->OutputMax)
	{
		PID_INC->ctrOut=PID_INC->OutputMax;
	}
	else if(PID_INC->ctrOut<PID_INC->OutputMin)
	{
		PID_INC->ctrOut=PID_INC->OutputMin;
	}
	
	return (int)PID_INC->ctrOut ;
}


/***************��������**************/
//PID_Inc_Typedef PID_Inc;//����PID�㷨�Ľṹ��

////һ���pid�����㷨
//int User_PidIncControl(u16 spdNow)
//{
//	double output;
//	// spdNow = V2;
//	PID_Inc.spdTag = 400;

//	PID_Inc.errNow =  PID_Pos.spdTag - spdNow; //���㲢д���ٶ����

//	//�޸�pid����
//	PID_Inc.Kp = PID_P;			   //����ϵ������
//	PID_Inc.Ki = PID_I; 	           //����ϵ������
//	PID_Inc.Kd = PID_D;      	       //΢��ϵ������
//	
//	PID_Inc.ErrorBond = 1000;
//	//PID_Inc.ErrorPre  = 0;
//	PID_Inc.OutputMax = 979;
//	PID_Inc.OutputMin = -979;
//	PID_Inc.ErrorSum  = 0;
//	PID_Inc.ErrorSumMax = INT32_MAX;
//	PID_Inc.ErrorSumMin = INT32_MIN;

//	output=PID_Inc_Controller(&PID_Inc);     //ִ�о���ʽPID�㷨

//	PID_Inc.control = (int)output;       //�Կ���ֵȡ�� ��ȡ��ֵ��pwm

//	MotorB_PWM_Update(PID_Inc.control);  //����pwm���������ٶȵĿ���
//	
//	return 0;
//}



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

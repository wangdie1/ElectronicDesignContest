typedef struct PID
{
	int SetAngle;//�趨�Ƕ�
	long aSumError;//����ۼ�
	double aProportion;//��������P
	double aIntegral;//���ֳ���I
	double aDerivative;//΢�ֳ��� D
	int aLastError;//Error[-1]
	int aPrevError;//Error[-2]
	
	int SetSpeed;//�趨�ٶ�
	long sSumError;//����ۼ�
	double sProportion;//��������P
	double sIntegral;//���ֳ���I
	double sDerivative;//΢�ֳ��� D
	int sLastError;//Error[-1]
	int sPrevError;//Error[-2]
}PID;
static PID sPID;
static PID *sptr = &sPID;
//PID��ʼ��//
void IncPIDInit(void) 
{ 
sptr->aSumError = 0; 
sptr->aLastError = 0; //Error[-1] 
sptr->aPrevError = 0; //Error[-2] 
sptr->aProportion = 4.2; //Proportional Const 
sptr->aIntegral = 1.8; //Integral Const 
sptr->aDerivative = 1.7; //Derivative Const 
sptr->SetAngle = 2553;	
	
sptr->sSumError = 0; 
sptr->sLastError = 0; //Error[-1] 
sptr->sPrevError = 0; //Error[-2] 
sptr->sProportion = 4.2; //Proportional Const //4.2  1.8 2.2
sptr->sIntegral = 1.8; //Integral Const 
sptr->sDerivative = 1.7; //Derivative Const 
sptr->SetSpeed =0;	
}

//����ʽPID���㲿��//
float IncPIDCalcaSpeed(int NextSpeed) 
{ 
register float sError, sIncpid;//��ǰ���	
sError = sptr->SetSpeed - NextSpeed; //��������
sIncpid = sptr->sProportion * sError  //E[K]��
- sptr->sIntegral * sptr->sLastError   //E[K-1]��
+ sptr->sDerivative * sptr->sPrevError;//E[K-2]�� 
//�洢�������´μ���
sptr->sPrevError = sptr->sLastError; 
sptr->sLastError = sError; 
//��������ֵ
// if((iError>0)&(iIncpid>iError))
// 		iIncpid=iError;
// if((iError<0)&(iIncpid<iError))
// 		iIncpid=iError;
return(sIncpid); 
}

float IncPIDCalcaAngle(int NextAngle) 
{ 
register float aError, aIncpid;//��ǰ��� 
aError = sptr->SetAngle - NextAngle; //��������
aIncpid = sptr->Proportion * aError  //E[K]��
- sptr->aIntegral * sptr->aLastError   //E[K-1]��
+ sptr->aDerivative * sptr->aPrevError;//E[K-2]�� 
//�洢�������´μ���
sptr->aPrevError = sptr->aLastError; 
sptr->aLastError = aError; 
return(aIncpid); 
}
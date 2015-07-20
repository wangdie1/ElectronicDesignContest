typedef struct PID
{
	int SetAngle;//设定角度
	long aSumError;//误差累计
	double aProportion;//比例常数P
	double aIntegral;//积分常数I
	double aDerivative;//微分常数 D
	int aLastError;//Error[-1]
	int aPrevError;//Error[-2]
	
	int SetSpeed;//设定速度
	long sSumError;//误差累计
	double sProportion;//比例常数P
	double sIntegral;//积分常数I
	double sDerivative;//微分常数 D
	int sLastError;//Error[-1]
	int sPrevError;//Error[-2]
}PID;
static PID sPID;
static PID *sptr = &sPID;
//PID初始化//
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

//增量式PID计算部分//
float IncPIDCalcaSpeed(int NextSpeed) 
{ 
register float sError, sIncpid;//当前误差	
sError = sptr->SetSpeed - NextSpeed; //增量计算
sIncpid = sptr->sProportion * sError  //E[K]项
- sptr->sIntegral * sptr->sLastError   //E[K-1]项
+ sptr->sDerivative * sptr->sPrevError;//E[K-2]项 
//存储误差，用于下次计算
sptr->sPrevError = sptr->sLastError; 
sptr->sLastError = sError; 
//返回增量值
// if((iError>0)&(iIncpid>iError))
// 		iIncpid=iError;
// if((iError<0)&(iIncpid<iError))
// 		iIncpid=iError;
return(sIncpid); 
}

float IncPIDCalcaAngle(int NextAngle) 
{ 
register float aError, aIncpid;//当前误差 
aError = sptr->SetAngle - NextAngle; //增量计算
aIncpid = sptr->Proportion * aError  //E[K]项
- sptr->aIntegral * sptr->aLastError   //E[K-1]项
+ sptr->aDerivative * sptr->aPrevError;//E[K-2]项 
//存储误差，用于下次计算
sptr->aPrevError = sptr->aLastError; 
sptr->aLastError = aError; 
return(aIncpid); 
}
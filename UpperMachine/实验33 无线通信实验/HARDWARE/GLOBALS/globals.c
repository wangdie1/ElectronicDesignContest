#include "globals.h"

Motor_TypeDef MotorA,MotorB;
SysStatus_t State;
SysStatus_t PreStatus;
// PID_Typedef TemperaturePID;
PID_Typedef SpeedPID,SpeedPID1,PositionPID,PositionPID1,PositionPID_WV;
FForward_Typedef PositionFF;
float TemperatureAim=0;
float TemperatureAimTemp=0;
float TemperatureTest=0;
float pwm_duty=0;
s32 SpeedBuffer[BUFFER_SIZE];
s32 PositionBuffer[BUFFER_SIZE];
s32 BufferNum=0;
u8 	IsInputOK=0;
u8 IsCycleOK =0;
int Diec =1;
double theta;//�ڸ˽Ƕ�
double alpha;//���۽Ƕ�
double alpha_pi;//������
double v_alpha_pi ;//�ٶȻ���
double v_alpha;//�ٶ�
double v_theta;
int AimAngle=0;//�����˶�Ŀ��Ƕ�
double AimTheta =0;//Ŀ��ֹͣλ��
double StopTheta =0;
double ThetaDelta=0;
double DeltaNum =0;
int flag2=0;
double E;
double E0;

char str[10]; 


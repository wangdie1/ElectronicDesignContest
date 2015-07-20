#include "MyType.h"
#include "led.h"
#include "MYCONST.H"
#include "MyGlobals.h"

volatile SystStatus_t  STATE;//ϵͳ״̬

/*****����LED����***/
volatile     LED_TypeDef 		LED;
volatile int LED_Time;

/*****KEY���ر���*****/

/*******�г̿��ر�־********/
volatile uint8_t SW0_IsTouched=0;
volatile uint8_t SW1_IsTouched=0;

/***�������ȫ�ֱ���***/
volatile Motor_TypeDef  MotorA;

/*******���ʹ洢���ݱ���**********/
volatile s16   SpeedStore[SPEED_STORE_MAX]={0};				//�ٶ��ٶȴ洢
volatile s16   CCRStore[CCR_STORE_MAX]={0};						//ռ�ձȵ�ѹ�洢
volatile s32   PositionStore[POSITION_STORE_MAX]={0};	//λ�ô洢

//��������
volatile s32 SpeedSampleNum=0;
volatile s32 CCRNum=0;
volatile s16 SampleNum=0;
/**���ڷ�������***/
volatile s32 s=0;
volatile s32 c=0;
volatile s32 a=0;
/***PID��������***/

volatile PID_Typedef 	SpeedPID_WC,PositionPID_WC;
/***Control������**/
volatile 	s32	SpeedErrorSum=0;
volatile s32 PositionErrorSum=0;
volatile   s16 PWM_B=0;

/*******����ٶȿ��Ʊ���*********/

volatile int SpeedMax = 0;
volatile int SpeedMin = 0;
/** INIT ����***/
volatile  u32 INIT_Delay = 0;

/***���Ʊ�־λ***/
volatile int IsPositionArrived = 0;
volatile int IsSpeedArrived  =0;
volatile int IsReport = 1;
volatile int PosFrameReceivedFlag = 0;
volatile  	int bIs_First_Measurement = 1;
void GloableVariableInit(void)
{
 MotorA.CurrentTest=0;
 MotorA.CurrentTest =0;
 MotorA.PositionExpected =0;
 MotorA.PositionTest =0;
 MotorA.SpeedExpected =0;
 MotorA.SpeedTest =0;
MotorA.M_State = MOTOR_STOP;
 
 
  SpeedSampleNum=0;
  CCRNum=0;
  SampleNum=0;
	
	INIT_Delay = 0;
	IsPositionArrived =0;
	IsSpeedArrived = 0;
	IsReport =0;
	
}
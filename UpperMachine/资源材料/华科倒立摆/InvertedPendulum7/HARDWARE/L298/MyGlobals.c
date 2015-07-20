#include "MyType.h"
#include "led.h"
#include "MYCONST.H"
#include "MyGlobals.h"

volatile SystStatus_t  STATE;//系统状态

/*****测试LED变量***/
volatile     LED_TypeDef 		LED;
volatile int LED_Time;

/*****KEY返回变量*****/

/*******行程开关标志********/
volatile uint8_t SW0_IsTouched=0;
volatile uint8_t SW1_IsTouched=0;

/***电机控制全局变量***/
volatile Motor_TypeDef  MotorA;

/*******发送存储数据变量**********/
volatile s16   SpeedStore[SPEED_STORE_MAX]={0};				//速度速度存储
volatile s16   CCRStore[CCR_STORE_MAX]={0};						//占空比电压存储
volatile s32   PositionStore[POSITION_STORE_MAX]={0};	//位置存储

//采样序列
volatile s32 SpeedSampleNum=0;
volatile s32 CCRNum=0;
volatile s16 SampleNum=0;
/**用于发送数据***/
volatile s32 s=0;
volatile s32 c=0;
volatile s32 a=0;
/***PID参数变量***/

volatile PID_Typedef 	SpeedPID_WC,PositionPID_WC;
/***Control误差变量**/
volatile 	s32	SpeedErrorSum=0;
volatile s32 PositionErrorSum=0;
volatile   s16 PWM_B=0;

/*******电机速度控制变量*********/

volatile int SpeedMax = 0;
volatile int SpeedMin = 0;
/** INIT 变量***/
volatile  u32 INIT_Delay = 0;

/***控制标志位***/
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
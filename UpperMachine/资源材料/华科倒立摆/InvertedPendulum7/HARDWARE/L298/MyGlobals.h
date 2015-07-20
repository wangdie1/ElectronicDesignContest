#include "MyType.h"
#include "led.h"
#include "MYCONST.H"
extern volatile SystStatus_t  STATE;//系统状态


/*****测试LED变量***/
extern volatile LED_TypeDef 		LED;
extern volatile int LED_Time;

/*******行程开关标志********/
extern volatile uint8_t SW0_IsTouched;
extern volatile uint8_t SW1_IsTouched;

/***电机控制全局变量***/
extern volatile Motor_TypeDef  MotorA;

/*******发送存储数据变量**********/
extern volatile s16 SpeedStore[SPEED_STORE_MAX];				//速度速度存储
extern volatile s16 CCRStore[CCR_STORE_MAX];						//占空比电压存储
extern volatile s32 PositionStore[POSITION_STORE_MAX];	//位置存储

//采样序列
extern volatile s32 SpeedSampleNum;
extern volatile s32 CCRNum;
extern volatile s16 SampleNum;
/**用于发送数据***/
extern volatile s32 s;
extern volatile s32 c;
extern volatile s32 a;

/***PID参数变量***/
extern volatile PID_Typedef 	SpeedPID_WC,PositionPID_WC;
/***Control误差变量**/
extern volatile 	s32	SpeedErrorSum;
extern volatile s32 PositionErrorSum;
extern volatile   s16 PWM_B;

extern volatile  u32 INIT_Delay ;

/********电机速度控制变量********/
extern volatile int SpeedMax;
extern volatile int SpeedMin;

/***控制标志位***/
extern volatile int IsPositionArrived ;
extern volatile int IsSpeedArrived  ;
extern volatile int IsReport;
extern volatile int PosFrameReceivedFlag;

/***速度促使标志*/
extern volatile  	int bIs_First_Measurement ;

/******全局变量初始化*********/
void GloableVariableInit(void);

#ifndef _MyType_H
#define _MyType_H

#define FALSE 	0
#define TRUE  	1

typedef enum
{
	IDLE,
	INIT,//初始化 归零
	TRACK,
	TEST_LED,
	TEST_USART,
	TEST_MOTOR,
	TEST_SPEED,
	TEST_KEY,
	TEST_IR,
	TEST_KEY_AND_IR,
	TEST_LOCATION,
	TEST_PLAY,
	TEST_LCD,
	TEST_DELAY,
	TEST_SWITCH,
	TEST_ST168,
	TEST_DS18B20,
	TEST_ENCODER,
	TEST_MOTION,
	TEST_ADC,
	TEST_ADC1,
	TEST_ADC2,
	TEST_HX711,
	SPEED,
	POSITION,
	V_RETURN,
	TRACK_MOTION,
	MENU,//菜单选择
	RECIPROCATE_INPUT,//
	RECIPROCATE,//往复运动模式，可输入摆动角度
	FREE_LQR,//自由LQR运动，用于测试基本要求3
	LQR_CONTROL,//保持倒立状态
	LQR_CIRCULAR_INPUT,//倒立运动输入角度
	LQR_CIRCULAR,//倒立状态下圆周运动 
	LQR_TEST,//测试稳定的0点
	POSITION_MEASURE,//
	POSITION_CONTROL,
	POSITION_INPUT,
	SPEED_CONTROL,
	LOCATION,
	BUFFER_SEND,
	OTHER //其他运动
}
SysStatus_t;


/**电机参式***/
typedef struct 
{
	float CurrentExpected;
	float CurrentTest;
	float SpeedExpected;
	float	 SpeedTest;
	double 	PositionExpected;
	double	PositionTest;
//	s32 	PWM;
}Motor_TypeDef;


typedef struct
{
	float x;//单位0.1mm
	float y;
	float a;
	float b;

}Point_t;
// typedef enum {FALSE = 0, TRUE = !FALSE} bool;


/* 一般的PID Controller  */
typedef struct
{
	float  Kp;				//比例系数
	float  Ki;				//积分系数
	float  Kd;				//微分系数
	float  ErrorBond;	//误差界限
	float  KiBond;		//积分作用误差
	float  KpBond;		//比例作用误差范围
	 float errNow;//当前的误差
	double ErrorSum;	//累计误差
	double ErrorSumMax;//累计误差最大值
	double ErrorSumMin;//累计误差最小值
	double ErrorPre;	//上次误差
	double OutputMax;	//输出最大
	double OutputMin;	//输出最小
}PID_Typedef;


typedef struct 
{
	float Kv; 					//一阶微分增益系数
	float Ka;					//二阶微分增益系数
	
	double rinV;				//输入一阶微分
	double rinA;				//输入二阶微分
	double rinPre;				//上一次的输入
	double rinPrePre;			//上上次的输入
	double rinV_Pre;			//上次的输入微分
	double FFmax;
	double FFmin;
}FForward_Typedef;


/*绝对式PID算法，接口参数结构类型*/

typedef struct 
{
 /*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
 float kp;     //比例系数
 float ki;     //积分系数
 float kd;     //微分系数
 float errILim;//误差积分上限
 
 float errNow;//当前的误差
 float ctrOut;//控制量输出
 
 /*PID算法内部变量，其值不能修改*/
 float errOld;
 float errP;
 float errI;
 float errD;
 
}PID_AbsoluteType;


/*增量式PID算法，接口参数结构类型*/

typedef struct 
{
 /*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
 float kp;     //比例系数
 float ki;     //积分系数
 float kd;     //微分系数
 
 float errNow; //当前的误差
 float dCtrOut;//控制增量输出
 float  ctrOut;//控制输出
 
 /*PID算法内部变量，其值不能修改*/
 float errOld1;
 float errOld2;
 
}PID_IncrementType;	

#endif

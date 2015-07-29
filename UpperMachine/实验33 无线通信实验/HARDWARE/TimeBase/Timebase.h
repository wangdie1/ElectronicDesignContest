#ifndef __TIMEBASE_H
#define __TIMEBASE_H
#include "stm32f10x.h"
#include "stdbool.h"
//#include "Encoder.h"
 
///////////////////////////////////////////////////////////////////////////
//#include "stm32f10x_systick.h"
//SystemFrequency /1000 1ms 中断一次  10000 100us
//SystemFrequency /100000 10us中断一次
//SystemFrequency /1000000 1us 中断一次
#define TB_1MS 	 	1000 		//1KHz
#define TB_100US 	10000 		//10KHz
#define TB_10US 	100000 		//100KHz
#define TB_1US 		1000000 	//1MHz
////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////
#define TIME_BASE_FREQ TB_100US
//////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
//#define FREQ_BASE TIME_BASE
//定义时间的频率
#define DT_100US  	(u16)		(TIME_BASE_FREQ/10000)			//  1
#define DT_200US	(u16)		(TIME_BASE_FREQ/5000)			//  2
#define DT_500US	(u16)		(TIME_BASE_FREQ/2000)			//  5
#define DT_1MS		(u16)		(TIME_BASE_FREQ/1000)			//  10
#define DT_2MS		(u16)		(TIME_BASE_FREQ/500)			//  20
#define DT_5MS 		(u16)		(TIME_BASE_FREQ/200)			//  50
#define DT_10MS		(u16)		(TIME_BASE_FREQ/100)			//  100
#define DT_50MS		(u16)		(TIME_BASE_FREQ/20)				//  500
#define DT_100MS	(u16)		(TIME_BASE_FREQ/10)				//  1000
#define DT_200MS  	(u16)   	(TIME_BASE_FREQ/5)				//  2000
#define DT_500MS  	(u16)  		(TIME_BASE_FREQ/2)				//  5000
#define DT_1S		(u16)		(TIME_BASE_FREQ/1)     			//  10000     
////////////////////////////////////////////////////////////////////////////



////////////////////////////定义延时时间///////////////////////////////////////
#define SPEED_DELAY	 				DT_10MS//10////40//100	 //单位见TIMEBASE100us
#define CURRENT_DELAY  			DT_100US//40
#define POSITION_DELAY 			DT_10MS 

#define POSITION_PID_DELAY		DT_10MS//DT_2MS//DT_100MS
#define SPEED_PID_DELAY 		DT_1MS//DT_1MS//80//200
#define CURRENT_PID_DELAY 	DT_20US//DT_500US//40//40

#define CAN_SEND_DELAY 			DT_1S

#define LED_TEST_DELAY 			DT_500MS

#define LCD_DISPLAY_DELAY		DT_500MS

#define ADC_DELAY						DT_10US

//定义流水灯的采样时间为1s
#define LED_DELAY           	 DT_1S
//////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////
//#define SPEED_SAMPLING_TIME	 SPEED_DELAY
//速度采样频率变为速度环频率
#define SPEED_SAMPLING_FREQ 		(u16) 	SPEED_LOOP_FREQ//(TIME_BASE_FREQ/(SPEED_DELAY+1))
#define SPEED_LOOP_FREQ  			(u16)  	(TIME_BASE_FREQ / (SPEED_PID_DELAY+1))          //10us    1000
#define CURRENT_SAMPLING_FREQ 		(u16)   (TIME_BASE_FREQ / (CURRENT_DELAY+1))            //         10000
#define CURRENT_LOOP_FREQ 			(u16)	(TIME_BASE_FREQ / (CURRENT_PID_DELAY+1))		//         50000
#define POSITION_SAMPLING_FREQ		(u16)	(TIME_BASE_FREQ / (POSITION_DELAY+1))           //         100
#define POSITION_LOOP_FREQ			(u16)	(TIME_BASE_FREQ / (POSITION_PID_DELAY+1))       //         100
//流水灯的采样频率
#define LED_FREQ					(u16)	(TIME_BASE_FREQ / (LED_DELAY+1))       			//         1	
extern  volatile u32 hSysTick_OverNum;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////
//系统时钟的初始化
void TB_Init(u16 arr,u16 psc);

/************任务时钟设置*******************/
void  TB_SetDelay_Time(u16 hDelay);
bool TB_Delay_IsElapsed(void );

void TB_SetCAN_SendDelay_Time(u16 hDelay);
bool  TB_CAN_SendDelay_IsElapsed(void );

void TB_SetPositionDelay_Time(u16 hDelay);
bool TB_PositionDelay_IsElapsed(void);

void TB_SetPositionPIDDelay_Time(u16 hDelay);
bool TB_PositionPIDDelay_IsElapsed(void );

void TB_SetCurrentDelay_Time(u16 hDelay );
bool TB_CurrentDelay_IsElapsed(void);

void TB_SetSpeedDelay_Time(u16 hDelay );
bool TB_SpeedDelay_IsElapsed(void);

void TB_SetSpeedPIDDelay_Time(u16 hDelay );
bool TB_SpeedPIDDelay_IsElapsed(void);

void TB_SetCurrentPIDDelay_Time(u16 hDelay);
bool TB_CurrentPIDDelay_IsElapsed(void);


void TB_SetDisplayDelay_Time(u16 hDelay);
bool TB_DisplayDelay_IsElapsed(void);

void TB_SetADC_Time(u16 hDelay);
bool TB_ADC_Delay_IsElapsed(void);

void TB_SetLed_Time(u32 hDelay);
bool TB_SetLed_IsElapsed(void);
//////////////////////////////////////////////////////////////////////////////////

#endif

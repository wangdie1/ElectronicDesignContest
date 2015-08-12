#ifndef	__ENCODER1_H
#define __ENCODER1_H

#include "stm32f10x.h"
#include "stdbool.h"
//#include  "Encoder.h"
// #include "TimeBase.h"
#include "encoder_param.h"

#define ENCODER1_PPR (u16) 	4000//码盘线数
#define REDUCTION1_RATIO 1//减速比 

//TIM3  -----------------------------------   
//#define COUNTER_RESET   (u16)0
#define RADIOUS1	36//单位mm
#define LENGTH1 1980 //单位mm

//#define LED0_PWM_VAL TIM2->CCR2 

#define ENCODER1_TIM_PERIOD (u16)(65000)   // number of pulses per revolution

//TIM3  -----------------------------------   
//#define COUNTER_RESET   (u16)0
#define MAX_COUNT 3000
#define B_Dir PBout(5)	// PB5
//------------------------------------------

#define	ENC1_TIMER 						TIM4
#define ENC1_TIMER_IRQn					TIM4_IRQn
#define ENC1_TIMER_CLK					RCC_APB1Periph_TIM4
#define ENC1_GPIO_PORT					GPIOB
#define ENC1_GPIO_CLK					RCC_APB2Periph_GPIOB 
#define ENC1_GPIO_PIN_A					GPIO_Pin_6
#define ENC1_GPIO_PIN_B					GPIO_Pin_7

#define ENC1_ANFULAR_UNIT      			(800/9.0)	//90//1度  16000/360  == 4000  : 90    400 : 9
#define ENC1_SPPED_UNIT					600//RPM/10

#define SPEED_BUFFER_SIZE 				7
#define COUNTER_RESET (u16)				0
#define ICx_FILTER (u8) 				6
#define TIMx_PRE_EMPTION_PRIORITY 		1
#define TIMx_SUB_PRIORITY 				0
#define U32_MAX 						0XFFFFFFFF
#define U16_MAX 						0XFFFF
#define double_MAX						INT32_MAX
#define S32_MIN 						INT32_MIN



//900 0.1度
//90  1度
//9000 0.01度
#define ENC_ANGULAR_UNIT					90//1度
#define ENC_SPEED_UNIT						600//RPM/10

/*----------------Exported functions -------------------------------------*/
//void   ENC1_Init(void);
//编码器的基础功能
void   Encoder1_Init(void);
u16    Encoder1_Get_Counter(void);
double ENC1_Get_Speed(void);
//获取编码器的角度
double ENC1_Get_Electrical_Angle(void);
//定时器的中断服务程序
void   TIM4_IRQHandler(void);

void   ENC1_Clear_Speed_Buffer(void);
double ENC1_Get_TimerCounter(void);
double ENC1_Calc_Average_Speed(void);
double ENC1_Calc_Rot_Speed(void);

double ENC1_Calc_Position(void);
double ENC1_Get_AnglularPosition(void);

#endif

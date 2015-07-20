
#include "stm32f10x.h"
#include "stdbool.h"
//#include "TimeBase.h"
#include "encoder_param.h"

#define ENCODER_PPR (u16) MAXON_RE25_CPR		//码盘线数
#define REDUCTION_RATIO 	MAXON_RE25_RATIO	//减速比

#define RADIOUS	 36   //单位mm
#define LENGTH  1980 //单位mm

/**
移植时注意修改
***/
#define	ENC_TIMER 							TIM3
#define ENC_TIMER_IRQn					    TIM3_IRQn
#define ENC_TIMER_CLK						RCC_APB1Periph_TIM3
#define ENC_GPIO_PORT						GPIOC
#define ENC_GPIO_CLK						RCC_APB2Periph_GPIOC 
#define ENC_GPIO_PIN_A					    GPIO_Pin_6
#define ENC_GPIO_PIN_B					    GPIO_Pin_7 

#define SPEED_BUFFER_SIZE 					7
#define COUNTER_RESET (u16)					0
#define ICx_FILTER (u8) 					6
#define TIMx_PRE_EMPTION_PRIORITY 			1
#define TIMx_SUB_PRIORITY 					0
#define U32_MAX 										0XFFFFFFFF
#define U16_MAX 										0XFFFF
#define double_MAX											INT32_MAX
#define S32_MIN 										INT32_MIN
//900 0.1度
//90  1度
//9000 0.01度
#define ENC_ANGULAR_UNIT							90//1度
#define ENC_SPEED_UNIT								600//RPM/10

/* Exported functions ------------------------------------------------------- */
void 	ENC_Init(void);
double 	ENC_Get_Electrical_Angle(void);
void 	ENC_Clear_Speed_Buffer(void);
double 	ENC_Get_TimerCounter(void);
double 	ENC_Calc_Average_Speed(void);
double 	ENC_Get_Speed(void);
double 	ENC_Calc_Rot_Speed(void);
void 	TIM3_IRQHandler(void);
double 	ENC_Calc_Position(void);
double 	ENC_Get_AnglularPosition(void);


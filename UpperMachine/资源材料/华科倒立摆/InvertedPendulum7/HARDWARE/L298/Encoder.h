#include "stm32f10x.h"
#include "stdbool.h"
// #include "TimeBase.h"
#include "encoder_param.h"

/**
ÒÆÖ²Ê±×¢ÒâÐÞ¸Ä
***/
#define	ENC_TIMER 							TIM3
#define ENC_TIMER_IRQn					TIM3_IRQn
#define ENC_TIMER_CLK						RCC_APB1Periph_TIM3
#define ENC_GPIO_PORT						GPIOA
#define ENC_GPIO_CLK						RCC_APB2Periph_GPIOA 
#define ENC_GPIO_PIN_A					GPIO_Pin_6
#define ENC_GPIO_PIN_B					GPIO_Pin_7 


#define SPEED_BUFFER_SIZE 					8

#define COUNTER_RESET (u16)					0
#define ICx_FILTER (u8) 						6

#define TIMx_PRE_EMPTION_PRIORITY 	1
#define TIMx_SUB_PRIORITY 					0

#define U32_MAX 										0XFFFFFFFF
#define U16_MAX 										0XFFFF
#define S32_MAX											INT32_MAX
#define S32_MIN 										INT32_MIN

#define SPEED_MAX									1000
#define SPEED_MIN									-1000



/* Exported functions ------------------------------------------------------- */
void ENC_Init(void);


s16 ENC_Get_Electrical_Angle(void);
void ENC_Clear_Speed_Buffer(void);
s32 ENC_Get_TimerCounter(void);
s16 ENC_Calc_Average_Speed(void);
s16 ENC_Get_Speed(void);
s16 ENC_Calc_Rot_Speed(void);
void TIM3_IRQHandler(void);
s32 ENC_Calc_Position(void);
s32 ENC_Get_AnglularPosition(void);


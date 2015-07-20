#include "stm32f10x.h"
#include "TIM1_PWM.h"
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel4Pulse = 0;

void TIM1_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = TIM1_PWM_CH4_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA |
                       RCC_APB2Periph_AFIO, ENABLE);
	
	 /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock /TIM1_PWM_FREQ ) - 1;
	/* Compute CCR4 value to generate a duty cycle at 50%  for channel 4 */
//   Channel4Pulse = (uint16_t) (((uint32_t) TIM1_PWM_DUTY * (TimerPeriod - 1)) / 100);
	 Channel4Pulse = (uint16_t) (((uint32_t) TIM1_PWM_DUTY * (TimerPeriod - 1)) / 100);
	  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	 TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	 /* TIM1 counter enable */
   TIM_Cmd(TIM1, ENABLE);

   /* TIM1 Main Output Enable */
   TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
void TIM1_PWM_ON()
{
		TIM1->CCR4 = 0;//占空比都设为0
}

void TIM1_PWM_OFF()
{
		TIM1->CCR4 = Channel4Pulse;//占空比都设为0
}
void TIM1_PWM_Update(float duty)
{
	/* Compute CCR4 value to generate a duty cycle at 50%  for channel 4 */
  Channel4Pulse = (uint16_t) (( duty * (TimerPeriod - 1)) / 100);
	
	TIM1->CCR4=Channel4Pulse;
}
	
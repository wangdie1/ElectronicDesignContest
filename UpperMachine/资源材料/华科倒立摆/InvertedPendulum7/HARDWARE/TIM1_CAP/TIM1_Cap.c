#include "TIM1_CAP.H"
#include "led.h"
volatile int flag=0;
volatile u32 time_over_num=0;
__IO int IC1ReadValue = 0, IC2ReadValue = 0 , IC3ReadValue = 0,IC4ReadValue=0;
// u8 TIM4CH1_CAPTURE_STA=0;
// u16 TIM4CH1_CAPTURE_VAL;
vu8 capnum=0;
void TIM1_CapInit(void)
{
	 u16 PrescalerValue = 72-1;//工作于9Mhz;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//时钟开启
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//引脚初始化
//TIM4 IC1--PB6 IC2--PB7 IC3--PB8 IC4--PB9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_9 | GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
//中断设置
  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
	
	
	
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM1, PrescalerValue, TIM_PSCReloadMode_Immediate);
// 	TIM_ARRPreloadConfig(TIM1, ENABLE);   //??ARR??????
// //IC1
// 	  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//   TIM_ICInitStructure.TIM_ICFilter = 0x0;

//   TIM_ICInit(TIM1, &TIM_ICInitStructure);
//IC2	
		  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM1, &TIM_ICInitStructure);
//IC3	
		  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM1, &TIM_ICInitStructure);
	//IC4
	  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	//中断使能
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM1, TIM_IT_CC4 | TIM_IT_CC2 | TIM_IT_CC3 , ENABLE);
	
	  /* TIM enable counter */
  TIM_Cmd(TIM1, ENABLE);
	

	
}


void TIM1_CC_IRQHandler(void)
{ 	
	if(TIM_GetITStatus(TIM1, TIM_IT_CC3) == SET)
	{
			TIM_ITConfig(TIM1, TIM_IT_CC1, DISABLE);
			/* Clear TIM4 Capture compare interrupt pending bit */
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
			 /* Disable the CC1 Interrupt Request */
		/* Get the Input Capture value */
			IC3ReadValue = TIM_GetCapture3(TIM1)+time_over_num*0xffff; 
		capnum++;
		LED0_Toggle();
	}
	else if(TIM_GetITStatus(TIM1, TIM_IT_CC2) == SET)
 	{

		/* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
			 /* Disable the CC1 Interrupt Request */
		TIM_ITConfig(TIM1, TIM_IT_CC2, DISABLE);
				/* Get the Input Capture value */
    IC2ReadValue = TIM_GetCapture2(TIM1)+time_over_num*0xffff; 
		capnum++;
// 		time_over_num=0;

		LED1_Toggle();
	}
// 	LED0_Toggle();
// 	LED1_Toggle();
	 flag=1;
}

void TIM1_UP_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);
	time_over_num++;
// 	LED0_Toggle();
}
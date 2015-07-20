#include "switch.h"
__IO int is_ready=0;

void Switch_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//????
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
		//connect KEY EXTI line to KEY GPIO pin
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
		//configure KEY EXTI line
		EXTI_InitStructure.EXTI_Line=EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//…œ…˝—ÿ
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		//enable and set KEY EXTI Interrupt to the lowest priority
		NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x0f;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
}

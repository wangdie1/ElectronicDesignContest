#include "extikey.h"
volatile  u8 KeyFlag = 0;
void EXTI_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//????????


  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//ÉÏÉýÑØ³ö·¢
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//????KEY0?????????
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//?????2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//????0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//????????
  	NVIC_Init(&NVIC_InitStructure);  	  //??NVIC_InitStruct???????????NVIC???

}

void EXTI4_IRQHandler(void)
{
// 	delay_ms(10);//??
  KeyFlag = 1;
	EXTI_ClearITPendingBit(EXTI_Line4);  //??LINE4???????  
}
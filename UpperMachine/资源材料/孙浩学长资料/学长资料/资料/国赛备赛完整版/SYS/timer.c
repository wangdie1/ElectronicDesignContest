
//Email:ykee@outlook.com
#include <stm32f10x.h>
#include "timer.h"
	  
u32 count=0;       //脉冲计数
u32 count_val=0;   //计数值


void TIM4_Init(u16 arr, u16 psc ,u32 count)
{
	RCC->APB1ENR |= 1<<2;       //TIM4时钟使能    
	RCC->APB2ENR |= 1<<3;       //使能PORTB时钟
	  	
	GPIOB->CRL &= 0XF0FFFFFF;//PB6输出
	GPIOB->CRL |= 0X0B000000;//复用功能输出 	  
	GPIOB->ODR |= 1<<6;//PB6上拉	

	TIM4->ARR = arr;//设定计数器自动重装值 
	TIM4->PSC = psc;//预分频器不分频
	TIM4->CCR1 = arr/2; //占空比为50%
	count_val=count-1;	   //脉冲输出个数

	TIM4->CCMR1 |= 7<<4;  //CH1 PWM2模式		 
	TIM4->CCMR1 |= 1<<3;  //CH1预装载使能   	   
  
	TIM4->CCER |= 1<<0;        //TIM4 OC1 PB6 输出使能	   
	
	TIM4->DIER|=1<<0;   //允许更新中断				
	TIM4->DIER|=1<<6;   //允许触发中断
	TIM4->EGR |=1<<1; 	//允许产生比较捕获事件
	//MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//抢占1，子优先级3，组2

	TIM4->CR1 |= 0x0080;   //ARPE使能 
	TIM4->CR1 |= 0x0001;    //使能定时器4
	
	TIM4->CCMR1 |= 7<<4;  //CH1 PWM2模式		 
	TIM4->CCMR1 |= 1<<3;  //CH1预装载使能   	   

	TIM4->CR1 |= 0x0080;   //ARPE使能 
	TIM4->CR1 |= 0x0001;    //使能定时器3 	
}
 	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//产生更新中断
	{
		count++;
		if(count==count_val)
		{
			TIM4->CR1&=~(0x01);    //CEN=0，禁止定时器3	
			count=0;
		}		    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}

void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//浮空输入
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//浮空输入

	/* Enable the TIM3 Update Interrupt */
	//这两个东东要同时设置才可以使用中断
	TIM3->DIER|=1<<0;   //允许更新中断				
	TIM3->DIER|=1<<6;   //允许触发中断
	//MY_NVIC_Init(1,3,TIM3_IRQChannel,2);

	/* Timer configuration in Encoder mode */ 
	TIM3->PSC = 0x0;//预分频器
	TIM3->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
	TIM3->CR1 &=~(3<<8);// 选择时钟分频：不分频
	TIM3->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
		
	TIM3->CCMR1 |= 1<<0; //CC1S='01' IC1FP1映射到TI1
	TIM3->CCMR1 |= 1<<8; //CC2S='01' IC2FP2映射到TI2
	TIM3->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2不反相，IC2FP2=TI2
	TIM3->CCMR1 |= 3<<4; //	IC1F='1000' 输入捕获1滤波器
	TIM3->SMCR |= 3<<0;	 //SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1，使能定时器
}


















//Email:ykee@outlook.com
#include <stm32f10x.h>
#include "timer.h"
	  
u32 count=0;       //�������
u32 count_val=0;   //����ֵ


void TIM4_Init(u16 arr, u16 psc ,u32 count)
{
	RCC->APB1ENR |= 1<<2;       //TIM4ʱ��ʹ��    
	RCC->APB2ENR |= 1<<3;       //ʹ��PORTBʱ��
	  	
	GPIOB->CRL &= 0XF0FFFFFF;//PB6���
	GPIOB->CRL |= 0X0B000000;//���ù������ 	  
	GPIOB->ODR |= 1<<6;//PB6����	

	TIM4->ARR = arr;//�趨�������Զ���װֵ 
	TIM4->PSC = psc;//Ԥ��Ƶ������Ƶ
	TIM4->CCR1 = arr/2; //ռ�ձ�Ϊ50%
	count_val=count-1;	   //�����������

	TIM4->CCMR1 |= 7<<4;  //CH1 PWM2ģʽ		 
	TIM4->CCMR1 |= 1<<3;  //CH1Ԥװ��ʹ��   	   
  
	TIM4->CCER |= 1<<0;        //TIM4 OC1 PB6 ���ʹ��	   
	
	TIM4->DIER|=1<<0;   //��������ж�				
	TIM4->DIER|=1<<6;   //�������ж�
	TIM4->EGR |=1<<1; 	//��������Ƚϲ����¼�
	//MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//��ռ1�������ȼ�3����2

	TIM4->CR1 |= 0x0080;   //ARPEʹ�� 
	TIM4->CR1 |= 0x0001;    //ʹ�ܶ�ʱ��4
	
	TIM4->CCMR1 |= 7<<4;  //CH1 PWM2ģʽ		 
	TIM4->CCMR1 |= 1<<3;  //CH1Ԥװ��ʹ��   	   

	TIM4->CR1 |= 0x0080;   //ARPEʹ�� 
	TIM4->CR1 |= 0x0001;    //ʹ�ܶ�ʱ��3 	
}
 	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//���������ж�
	{
		count++;
		if(count==count_val)
		{
			TIM4->CR1&=~(0x01);    //CEN=0����ֹ��ʱ��3	
			count=0;
		}		    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}

void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//��������
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//��������

	/* Enable the TIM3 Update Interrupt */
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�
	//MY_NVIC_Init(1,3,TIM3_IRQChannel,2);

	/* Timer configuration in Encoder mode */ 
	TIM3->PSC = 0x0;//Ԥ��Ƶ��
	TIM3->ARR = ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ 
	TIM3->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM3->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
	TIM3->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
	TIM3->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
	TIM3->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
	TIM3->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
	TIM3->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}

















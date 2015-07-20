#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "timer.h"	 	 
	  
int main(void)
{			
 	u16 currentCount;
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	Encoder_Init();
	delay_ms(10);
	B_Dir = 1;
	TIM4_Init(199, 71 , 56885);
   	while(1)
	{
 		delay_ms(1000);
		currentCount = TIM3 -> CNT;
		printf("����������ֵΪ��%d \n",currentCount+1);	   
	}	 
}


























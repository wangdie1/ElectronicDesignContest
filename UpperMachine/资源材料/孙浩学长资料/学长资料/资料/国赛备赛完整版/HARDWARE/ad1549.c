#include <stm32f10x.h>
#include "ad1549.h"
#include "delay.h"
//AD���ų�ʼ��
void AD1549_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);		     //��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		// 	GPIO_InitTypeDef GPIO_InitStructure;
	// 	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);		     //��������ʱ��
	// 	
	// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 	
	// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//AD��ȡģ�������ѹ
unsigned int AD_Read(void)
{
	unsigned int value=0;
	unsigned int i;
	ADCS(1);
	delay_us(5);
	ADCS(0);
	delay_us(5);
	for(i=0;i<10;i++)
	{
		ADCLK(0);
		
		delay_us(5);
		value=value<<1;
		if(ADDATA)
			value++;
			ADCLK(1);
			delay_us(5);
	}
	ADCS(1);
	delay_us(25);
	return(value);
}


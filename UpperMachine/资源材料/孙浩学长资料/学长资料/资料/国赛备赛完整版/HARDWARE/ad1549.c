#include <stm32f10x.h>
#include "ad1549.h"
#include "delay.h"
//AD引脚初始化
void AD1549_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);		     //开启总线时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		// 	GPIO_InitTypeDef GPIO_InitStructure;
	// 	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);		     //开启总线时钟
	// 	
	// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 	
	// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//AD读取模拟输入电压
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


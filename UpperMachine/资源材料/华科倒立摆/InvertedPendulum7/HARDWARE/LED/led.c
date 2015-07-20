#include "stm32f10x.h"
#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/5/27
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved											  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = LED0_GPIO_Pin;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(LED0_GPIO_Port, &GPIO_InitStructure);
 GPIO_SetBits(LED0_GPIO_Port,LED0_GPIO_Pin);						 //PA.8 输出高


 RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);   //使能PD端口时钟

 GPIO_InitStructure.GPIO_Pin = LED1_GPIO_Pin;	    		 //LED1-->PD.2 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);	
 GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin); 						 //PD.2 输出高 
	
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);   //使能PD端口时钟

 GPIO_InitStructure.GPIO_Pin = LED2_GPIO_Pin;	    		 //LED1-->PD.2 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(LED2_GPIO_Port, &GPIO_InitStructure);	
 GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin); 	
}
void LED0_Toggle()
{
	LED0_GPIO_Port->ODR ^=LED0_GPIO_Pin;//此处注意修改
}
void LED0_ON()
{
	GPIO_ResetBits(LED0_GPIO_Port,LED0_GPIO_Pin);
}
void LED0_OFF()
{
	GPIO_SetBits(LED0_GPIO_Port,LED0_GPIO_Pin);
}

void LED1_Toggle()
{
	LED1_GPIO_Port->ODR ^=LED1_GPIO_Pin;
}
void LED1_ON()
{
	GPIO_ResetBits(LED1_GPIO_Port,LED1_GPIO_Pin);
}
void LED1_OFF()
{
	GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin);
}
 
void LED2_Toggle()
{
	LED2_GPIO_Port->ODR ^=LED2_GPIO_Pin;
}
void LED2_ON()
{
	GPIO_ResetBits(LED2_GPIO_Port,LED2_GPIO_Pin);
}
void LED2_OFF()
{
	GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin);
}

#include "GPIO.h"
#include "stm32f10x.h"
void EnableGPIO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(GPIO_PORT_CLK, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_PIN;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
 GPIO_ResetBits(GPIO_PORT,GPIO_PIN);						 //PA.8 输出高

}
void Disable(void)
{
	GPIO_ResetBits(GPIO_PORT,GPIO_PIN);
// 	GPIO_InitTypeDef  GPIO_InitStructure;
//  	
//  RCC_APB2PeriphClockCmd(GPIO_PORT_CLK, ENABLE);	 //使能PA端口时钟
// 	
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN;				 //LED0-->PA.8 端口配置
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
	
}
void Enable(void)
{
GPIO_SetBits(GPIO_PORT,GPIO_PIN);
// 	GPIO_InitTypeDef  GPIO_InitStructure;	
//   RCC_APB2PeriphClockCmd(GPIO_PORT_CLK, ENABLE);	 //使能PA端口时钟
// 	
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN;				 //LED0-->PA.8 端口配置
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
// GPIO_ResetBits(GPIO_PORT,GPIO_PIN);
	
}
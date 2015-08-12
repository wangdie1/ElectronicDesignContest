#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "voice.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//语音模块初始化函数
void Voice_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP; //PA1~5 设置成浮空输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);						 //PB.5 输出高
}


//播放第a段语音
//播放语音模块的

u8 now,last;
void set_Voice(u8 a)
{
	now = a;
	if( now != last)
	{
		
		u8 i=0,rem;
		u8 s[5];
		//默认为高电平
		for(i=0;i<8;i++)
		{
			s[i]=1;
		}
		i=0;
		do
		{
			rem =a %2;
			a=a/2;
			if(rem == 0)
			{
				s[i] = 1;
			}
			else
			{
				s[i] = 0;
			}
			i++;
			
		}while(a!=0);
		
		voice1 = s[0];
		voice2 = s[1];
		voice3 = s[2];
		voice4 = s[3];
		voice5 = s[4];
		printf("\r\n%d,%d,%d,%d,%d\r\n",s[0],s[1],s[2],s[3],s[4]);
	}
	last = now;
}

void set_Voice_by_one(u8 i)
{
	if(i==1)
	{
		voice1 = 0;
		voice2 = 1;
		voice3 = 1;
		voice4 = 1;
		voice5 = 1;
	}
	else if(i == 2)
	{
		voice1 = 1;
		voice2 = 0;
		voice3 = 1;
		voice4 = 1;
		voice5 = 1;
	}
	else if(i == 3)
	{
		voice1 = 1;
		voice2 = 1;
		voice3 = 0;
		voice4 = 1;
		voice5 = 1;
	}
		else if(i == 4)
	{
		voice1 = 1;
		voice2 = 1;
		voice3 = 1;
		voice4 = 0;
		voice5 = 1;
	}
		else if(i == 5)
	{
		voice1 = 1;
		voice2 = 1;
		voice3 = 1;
		voice4 = 1;
		voice5 = 0;
	}
		
}

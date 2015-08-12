#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "voice.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//����ģ���ʼ������
void Voice_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP; //PA1~5 ���óɸ������ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);						 //PB.5 �����
}


//���ŵ�a������
//��������ģ���

u8 now,last;
void set_Voice(u8 a)
{
	now = a;
	if( now != last)
	{
		
		u8 i=0,rem;
		u8 s[5];
		//Ĭ��Ϊ�ߵ�ƽ
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

/*
	ZLG7290.c
	�������ʾ����̹���оƬZLG7290�ı�׼80C51��������C�ļ�
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/


#include "ZLG7290.h"
extern  unsigned char zlg_key;
extern unsigned char ZLK_KeyRead();

vu8 IsKeyPressed = 0;//�������±�־

void EXTIX_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
  RCC_APB2PeriphClockCmd(KEY_INT_PORT_CLK|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = KEY_INT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(KEY_INT_PORT, &GPIO_InitStructure);
	
	  //GPIOA.0	  �ж����Լ��жϳ�ʼ������
 	GPIO_EXTILineConfig(KEY_EXTI_PORT_SOURCE,KEY_EXTI_PIN_SOURCE);

		EXTI_InitStructure.EXTI_Line=KEY_EXTI_LINE;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
 	NVIC_InitStructure.NVIC_IRQChannel = KEY_EXTI_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
}



void EXTI0_IRQHandler(void)
{	
	if(KEY_INT==0)
	{
	
		zlg_key=ZLK_KeyRead();
		if((zlg_key!=0xff)&(zlg_key!=0x00))//��������ж�
		IsKeyPressed = 1;
		
		while(!KEY_INT);
	}		
	EXTI_ClearITPendingBit(KEY_EXTI_LINE);
// 	EXTI->PR=1<<0;     //���LINE0�ϵ��жϱ�־λ	
}
/*
������ZLG7290_WriteReg()
���ܣ���ZLG7290��ĳ���ڲ��Ĵ���д������
������
	RegAddr��ZLG7290���ڲ��Ĵ�����ַ
	dat��Ҫд�������
���أ�
	0������
	1������ZLG7290ʱ�����쳣
*/

u8 ZLG7290_WriteReg(u8 RegAddr, u8 dat)
{
	u8 b;
	b = I2C_Puts(ZLG7290_I2C_ADDR,RegAddr,1,&dat,1);
	return b;
}

/*
������ZLG7290_ReadReg()
���ܣ���ZLG7290��ĳ���ڲ��Ĵ�����������
������
	RegAddr��ZLG7290���ڲ��Ĵ�����ַ
	*dat���������������
���أ�
	0������
	1������ZLG7290ʱ�����쳣
*/
u8 ZLG7290_ReadReg(u8 RegAddr, u8 *dat)
{
	u8 b;
	b = I2C_Gets(ZLG7290_I2C_ADDR,RegAddr,1,dat,1);
	return b;
}

/*
������ZLG7290_cmd()
���ܣ���ZLG7290���Ϳ�������
������
	cmd0��д��CmdBuf0�Ĵ����������֣���1�ֽڣ�
	cmd1��д��CmdBuf1�Ĵ����������֣���2�ֽڣ�
���أ�
	0������
	1������ZLG7290ʱ�����쳣
*/
u8 ZLG7290_cmd(u8 cmd0, u8 cmd1)
{
	u8 b;
	u8 buf[2];
	buf[0] = cmd0;
	buf[1] = cmd1;
	b = I2C_Puts(ZLG7290_I2C_ADDR,ZLG7290_CmdBuf,1,buf,2);
	return b;
}

/*
������ZLG7290_SegOnOff()
���ܣ���Ѱַ������������Ϩ������ܣ���LED���е�ĳһ��
������
	seg��ȡֵ0��63����ʾ����ܣ���LED���Ķκ�
	b��0��ʾϨ��1��ʾ����
���أ�
	0������
	1������ZLG7290ʱ�����쳣
˵����
	��ÿһλ������У��κ�˳���ա�a,b,c,d,e,f,g,dp������
*/
u8 ZLG7290_SegOnOff(u8 seg, u8 b)
{
	u8 cmd;
	cmd = seg & 0x3F;
	if ( b ) cmd |= 0x80;
	return ZLG7290_cmd(0x01,cmd);
}

/*
������ZLG7290_Download()
���ܣ��������ݲ�����
������
	addr��ȡֵ0��7����ʾ����DpRam0��DpRam7�ı��
	dp���Ƿ������λ��С���㣬0��Ϩ��1������
	flash�����Ƹ�λ�Ƿ���˸��0������˸��1����˸
	dat��ȡֵ0��31����ʾҪ��ʾ������
���أ�
	0������
	1������ZLG7290ʱ�����쳣
˵����
	��ʾ���ݾ�������뷽ʽ��μ�ZLG7290�������ֲ�
*/
u8 ZLG7290_Download(u8 addr, u8 dp, u8 flash, u8 dat)
{
	u8 cmd0;
	u8 cmd1;
	cmd0 = addr & 0x0F;
	cmd0 |= 0x60;
	cmd1 = dat & 0x1F;
	if ( dp ) cmd1 |= 0x80;
	if ( flash ) cmd1 |= 0x40;
	return ZLG7290_cmd(cmd0,cmd1);
}


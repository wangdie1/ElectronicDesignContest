/*
	ZLG7290.h
	�������ʾ����̹���оƬZLG7290�ı�׼STM32��������ͷ�ļ�
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/


#ifndef _ZLG7290_H_
#define _ZLG7290_H_

#include <sys.h>
#include "I2C.h"
#define KEY_INT PCin(0)   //PA3
#define KEY_INT_PORT GPIOC
#define KEY_INT_PORT_CLK RCC_APB2Periph_GPIOC
#define KEY_INT_PIN		GPIO_Pin_0
#define KEY_EXTI_PORT_SOURCE GPIO_PortSourceGPIOC
#define KEY_EXTI_PIN_SOURCE GPIO_PinSource0
#define KEY_EXTI_LINE EXTI_Line0
#define KEY_EXTI_IRQn	EXTI0_IRQn
extern	vu8 IsKeyPressed;
//����ZLG7290��I2C����Э���еĴӻ���ַ
//����7λ����ַ��������дλ
#define ZLG7290_I2C_ADDR	0x38

//����ZLG7290�ڲ��Ĵ�����ַ���ӵ�ַ��
#define ZLG7290_SystemReg		0x00		//ϵͳ�Ĵ���
#define ZLG7290_Key			0x01		//��ֵ�Ĵ���
#define ZLG7290_RepeatCnt		0x02		//���������Ĵ���
#define ZLG7290_FunctionKey		0x03		//���ܼ��Ĵ���
#define ZLG7290_CmdBuf			0x07		//���������ʼ��ַ
#define ZLG7290_CmdBuf0			0x07		//�������0
#define ZLG7290_CmdBuf1			0x08		//�������1
#define ZLG7290_FlashOnOff		0x0C		//��˸���ƼĴ���
#define ZLG7290_ScanNum			0x0D		//ɨ��λ���Ĵ���
#define ZLG7290_DpRam			0x10		//��ʾ������ʼ��ַ
#define ZLG7290_DpRam0			0x10		//��ʾ����0
#define ZLG7290_DpRam1			0x11		//��ʾ����1
#define ZLG7290_DpRam2			0x12		//��ʾ����2
#define ZLG7290_DpRam3			0x13		//��ʾ����3
#define ZLG7290_DpRam4			0x14		//��ʾ����4
#define ZLG7290_DpRam5			0x15		//��ʾ����5
#define ZLG7290_DpRam6			0x16		//��ʾ����6
#define ZLG7290_DpRam7			0x17		//��ʾ����7
//STM32�жϳ�ʼ��
void EXTIX_Init(void);

//��ZLG7290��ĳ���ڲ��Ĵ���д������
u8 ZLG7290_WriteReg(u8 RegAddr, u8 dat);

//��ZLG7290��ĳ���ڲ��Ĵ�����������
u8 ZLG7290_ReadReg(u8 RegAddr, u8 *dat);

//��ZLG7290���Ϳ�������
u8 ZLG7290_cmd(u8 cmd0, u8 cmd1);

//��Ѱַ������������Ϩ������ܣ���LED���е�ĳһ��
u8 ZLG7290_SegOnOff(u8 seg, u8 b);

//�������ݲ�����
u8 ZLG7290_Download(u8 addr, u8 dp, u8 flash, u8 dat);

//��˸����ָ�FnӦ�����ֽ��ͣ�
//Fn��8��λ�ֱ��������ܵ�8��λ�Ƿ���˸��0������˸��1����˸
#define ZLG7290_Flash(Fn) 	ZLG7290_cmd(0x70,(Fn))

#endif  //_ZLG7290_H_

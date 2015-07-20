/*
	I2C.h
	��׼80C51��Ƭ��ģ��I2C���ߵ���������ͷ�ļ�
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/

#ifndef _I2C_H_
#define _I2C_H_

#include "sys.h"

//ģ��I2C���ߵ����Ŷ���
#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO��������	 
#define I2C_SCL    PCout(12) //SCL
#define I2C_SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //����SDA

//����I2C����ʱ�ӵ���ʱֵ��Ҫ����ʵ������޸ģ�ȡֵ1��255
//SCL�ź�����ԼΪ(I2C_DELAY_VALUE*4+15)����������
#define I2C_DELAY_VALUE		60

//����I2C����ֹͣ������һ�ο�ʼ֮ǰ�ĵȴ�ʱ�䣬ȡֵ1��65535
//�ȴ�ʱ��ԼΪ(I2C_STOP_WAIT_VALUE*8)����������
//���ڶ�������ȡֵΪ1���ɣ�������ĳЩ������˵���ϳ�����ʱ�Ǳ����
#define I2C_STOP_WAIT_VALUE	600

//I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
void I2C_Init_me(void);

//I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
u8 I2C_Puts
(
	u8 SlaveAddr,
	u16 SubAddr,
	u8 SubMod,
	u8 *dat,
	u16 Size
);

//I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
u8 I2C_Gets
(
	u8 SlaveAddr,
	u16 SubAddr,
	u8 SubMod,
	u8 *dat,
	u16 Size
);

#endif	//_I2C_H_

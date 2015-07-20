/*
	I2C.c
	��׼80C51��Ƭ��ģ��I2C���ߵ���������
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/

#include "I2C.h"
#include "delay.h"



/*
�궨�壺I2C_Delay()
���ܣ���ʱ��ģ��I2C����ר��
*/
#define I2C_Delay()\
delay_us(I2C_DELAY_VALUE)

/*
������I2C_Init()
���ܣ�I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
˵������main()�����Ŀ�ʼ����ͨ��Ӧ��Ҫִ��һ�α�����
*/
void I2C_Init_me(void)
{					     
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED0-->PA.11 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 GPIO_SetBits(GPIOC,GPIO_Pin_11);						 //PA.11 �����


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //LED1-->PA.12 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOC,GPIO_Pin_12); 
	
}

/*
������I2C_Start()
���ܣ�����I2C���ߵ���ʼ״̬
˵����
	SCL���ڸߵ�ƽ�ڼ䣬��SDA�����½���ʱ����I2C����
	����SDA��SCL����ʲô��ƽ״̬��������������ȷ������ʼ״̬
	������Ҳ�������������ظ���ʼ״̬
	������ִ�к�I2C���ߴ���æ״̬
*/
void I2C_Start()
{
	SDA_OUT();
	I2C_SDA = 1;
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 0;
	I2C_Delay();
}

/*
������I2C_Write()
���ܣ���I2C����д1���ֽڵ�����
������
	dat��Ҫд�������ϵ�����
*/
void I2C_Write(char dat)
{
	unsigned char t = 8;
	SDA_OUT();
	do
	{
		I2C_SDA = (dat & 0x80)>>7;
		dat <<= 1;
		I2C_SCL = 1;
		I2C_Delay();
		I2C_SCL = 0;
		I2C_Delay();
	} while ( --t != 0 );
}

/*
������I2C_Read()
���ܣ��Ӵӻ���ȡ1���ֽڵ�����
���أ���ȡ��һ���ֽ�����
*/
char I2C_Read()
{
	char dat;
	unsigned char t = 8;
	SDA_IN();
	do
	{
		I2C_SCL = 1;
		I2C_Delay();
		dat <<= 1;
		if ( READ_SDA ) dat |= 0x01;
		I2C_SCL = 0;
		I2C_Delay();
	} while ( --t != 0 );
	return dat;
}

/*
������I2C_GetAck()
���ܣ���ȡ�ӻ�Ӧ��λ
���أ�
	0���ӻ�Ӧ��
	1���ӻ���Ӧ��
˵����
	�ӻ����յ�ÿ���ֽڵ����ݺ�Ҫ����Ӧ��λ
	�ӻ����յ����1���ֽڵ����ݺ�һ��Ҫ������Ӧ��λ
*/
u8 I2C_GetAck()
{
	u8 ack;
	SDA_IN();      //SDA����Ϊ���� 
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
	ack = READ_SDA;
	I2C_SCL = 0;
	I2C_Delay();
	return ack;
}

/*
������I2C_PutAck()
���ܣ���������Ӧ��λ���Ӧ��λ
������
	ack=0����������Ӧ��λ
	ack=1������������Ӧ��λ
˵����
	�����ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ
	�����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ
*/
void I2C_PutAck(u8 ack)
{
	SDA_OUT();      //SDA����Ϊ���
	I2C_SDA = ack;
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
	I2C_SCL = 0;
	I2C_Delay();
}

/*
������I2C_Stop()
���ܣ�����I2C���ߵ�ֹͣ״̬
˵����
	SCL���ڸߵ�ƽ�ڼ䣬��SDA����������ʱֹͣI2C����
	����SDA��SCL����ʲô��ƽ״̬��������������ȷ����ֹͣ״̬
	������ִ�к�I2C���ߴ��ڿ���״̬
*/
void I2C_Stop()
{
	SDA_OUT();      //SDA����Ϊ���
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
	I2C_SDA = 1;
	I2C_Delay();
	delay_us(I2C_STOP_WAIT_VALUE);		//����һ�β���Start֮ǰ��Ҫ��һ������ʱ
}

/*
������I2C_Puts()
���ܣ�I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
������
	SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
	SubAddr���ӻ����ӵ�ַ
	SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
	*dat��Ҫ���͵�����
	Size�����ݵ��ֽ���
���أ�
	0�����ͳɹ�
	1���ڷ��͹����г����쳣
˵����
	�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
	���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
*/
u8 I2C_Puts
(
	u8 SlaveAddr,
	u16 SubAddr,
	u8 SubMod,
	u8 *dat,
	u16 Size
)
{
//������ʱ����
	u8 i;
	u8 a[3];
//��鳤��
	if ( Size == 0 ) return 0;
//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
//ȷ���ӵ�ַ
	switch ( SubMod )
	{
	case 0:
		break;
	case 1:
		a[1] = (char)(SubAddr);
		break;
	case 2:
		a[1] = (char)(SubAddr >> 8);
		a[2] = (char)(SubAddr);
		break;
	default:
		break;
	}
//���ʹӻ���ַ�����ŷ����ӵ�ַ��������ӵ�ַ�Ļ���
	SubMod++;
	I2C_Start();
	for ( i=0; i<SubMod; i++ )
	{
		I2C_Write(a[i]);
		if ( I2C_GetAck() )
		{
			I2C_Stop();
			return 1;
		}
	}
//��������
	do
	{
		I2C_Write(*dat++);
		if ( I2C_GetAck() ) break;
	} while ( --Size != 0 );
//������ϣ�ֹͣI2C���ߣ������ؽ��
	I2C_Stop();
	if ( Size == 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
������I2C_Gets()
���ܣ�I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
������
	SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
	SubAddr���ӻ����ӵ�ַ
	SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
	*dat��������յ�������
	Size�����ݵ��ֽ���
���أ�
	0�����ճɹ�
	1���ڽ��չ����г����쳣
˵����
	�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
	���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
*/
u8 I2C_Gets
(
	u8 SlaveAddr,
	u16 SubAddr,
	u8 SubMod,
	u8 *dat,
	u16 Size
)
{
//������ʱ����
	u8 i;
	u8 a[3];
//��鳤��
	if ( Size == 0 ) return 0;
//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
//��������ӵ�ַ�Ĵӻ�����Ҫ�ȷ��ʹӻ���ַ���ӵ�ַ
	if ( SubMod != 0 )
	{
	//ȷ���ӵ�ַ
		if ( SubMod == 1 )
		{
			a[1] = (char)(SubAddr);
		}
		else
		{
			a[1] = (char)(SubAddr >> 8);
			a[2] = (char)(SubAddr);
		}
	//���ʹӻ���ַ�����ŷ����ӵ�ַ
		SubMod++;
		I2C_Start();
		for ( i=0; i<SubMod; i++ )
		{
			I2C_Write(a[i]);
			if ( I2C_GetAck() )
			{
				I2C_Stop();
				return 1;
			}
		}
	}
//�����I2C_Start()�������ӵ�ַ�Ĵӻ����ظ���ʼ״̬
//�������ӵ�ַ�Ĵӻ�������������ʼ״̬
	I2C_Start();
//���ʹӻ���ַ
	I2C_Write(a[0]+1);
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
//��������
	for (;;)
	{
		*dat++ = I2C_Read();
		if ( --Size == 0 )
		{
			I2C_PutAck(1);
			break;
		}
		I2C_PutAck(0);
	}
//������ϣ�ֹͣI2C���ߣ������ؽ��
	I2C_Stop();
	return 0;
}

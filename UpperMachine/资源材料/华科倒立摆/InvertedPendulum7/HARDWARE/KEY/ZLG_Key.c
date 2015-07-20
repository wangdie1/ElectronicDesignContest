#include "ZLG_Key.h"
// #include "lcd.h"
#include "usart.h"
volatile  unsigned char zlg_key;
volatile  unsigned char KeyValue;
volatile	unsigned char RepeatCnt;
volatile	unsigned char FnKeyValue;


void SystemInit_key()
{
	I2C_Init_me();

	delay_ms(300);		//�ȴ�ZLG7290��λ���
	
	ClearAll();
	EXTIX_Init();
	
}

/*
������ClearAll()
���ܣ����������ʾ
*/
void ClearAll()
{
	unsigned char x;
	for ( x=0; x<8; x++ )
	{
		ZLG7290_Download(x,0,0,31);
	}
}

/*
������Test_DispBuf()
���ܣ�����ֱ��д�Դ�
*/

/*
������Disp_Led(u8	dat,u8	b)
���ܣ�����LED
*/

void Disp_Led(u8	dat,u8	b)
{	
	u8 temp;
	if(dat>=0&&dat<=4)
	{
		temp=dat<<2;
	ZLG7290_SegOnOff( temp,  b);
	}
	else
	{
		temp=dat<<2+1;
	ZLG7290_SegOnOff( temp,  b);
	}
}

/*
������DispValue()
���ܣ���ʾ100���ڵ���ֵ
������
	x����ʾλ�ã�ȡֵ0��6
	dat��Ҫ��ʾ�����ݣ�ȡֵ0��99
*/
void DispValue(char x, unsigned char dat)
{
	unsigned char d;
	d = dat / 10;
	ZLG7290_Download(x,0,0,d);
	d = dat - d * 10;
	ZLG7290_Download(x+1,0,0,d);
}

/*
������DispHexValue()
���ܣ���16���Ʒ�ʽ��ʾ��ֵ
������
	x����ʾλ�ã�ȡֵ0��6
	dat��Ҫ��ʾ�����ݣ�ȡֵ0��255
*/
void DispHexValue(char x, unsigned char dat)
{
	unsigned char d;
	d = dat / 16;
	ZLG7290_Download(x,0,0,d);
	d = dat - d * 16;
	ZLG7290_Download(x+1,0,0,d);
}
/*	x	��ʾλ�ã�ȡ0�ͷ�0	ȡ0ʱ��ʾ��01�����
		ȡ��0ʱ��ʾ��23�����
		datȡ0~99
*/


/*
������Test_Key()
���ܣ����԰�������
*/
void Test_Key()
{
	for (;;)
	{
		if ( IsKeyPressed )		//����м�����
		{
		//����жϱ�־
			IsKeyPressed = 0;
			DispValue(0,zlg_key);
			DispHexValue(3,RepeatCnt);
			DispHexValue(6,FnKeyValue);
		}
		
	}
}
unsigned char ZLK_KeyRead()
{
	//��ȡ��ֵ������������ֵ�����ܼ�ֵ
		ZLG7290_ReadReg(ZLG7290_Key,&KeyValue);
		ZLG7290_ReadReg(ZLG7290_RepeatCnt,&RepeatCnt);
		ZLG7290_ReadReg(ZLG7290_FunctionKey,&FnKeyValue);
		
		if(KeyValue!=0x00)
		{
// 			DispValue(0,KeyValue);
			return KeyValue;
		}
		else if((FnKeyValue!=0xff)&(FnKeyValue!=0x00))
		{
// 			DispValue(0,FnKeyValue);
			return FnKeyValue;
		}
		else 	return 0;
}


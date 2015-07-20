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

	delay_ms(300);		//等待ZLG7290复位完毕
	
	ClearAll();
	EXTIX_Init();
	
}

/*
函数：ClearAll()
功能：清除所有显示
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
函数：Test_DispBuf()
功能：测试直接写显存
*/

/*
函数：Disp_Led(u8	dat,u8	b)
功能：点亮LED
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
函数：DispValue()
功能：显示100以内的数值
参数：
	x：显示位置，取值0～6
	dat：要显示的数据，取值0～99
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
函数：DispHexValue()
功能：以16进制方式显示数值
参数：
	x：显示位置，取值0～6
	dat：要显示的数据，取值0～255
*/
void DispHexValue(char x, unsigned char dat)
{
	unsigned char d;
	d = dat / 16;
	ZLG7290_Download(x,0,0,d);
	d = dat - d * 16;
	ZLG7290_Download(x+1,0,0,d);
}
/*	x	显示位置，取0和非0	取0时显示在01数码管
		取非0时显示在23数码管
		dat取0~99
*/


/*
函数：Test_Key()
功能：测试按键功能
*/
void Test_Key()
{
	for (;;)
	{
		if ( IsKeyPressed )		//如果有键按下
		{
		//清除中断标志
			IsKeyPressed = 0;
			DispValue(0,zlg_key);
			DispHexValue(3,RepeatCnt);
			DispHexValue(6,FnKeyValue);
		}
		
	}
}
unsigned char ZLK_KeyRead()
{
	//读取键值、连击计数器值、功能键值
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


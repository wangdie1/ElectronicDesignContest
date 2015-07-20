#include "yaokongqi.h"
#include <stm32f10x.h>
#include "delay.h"
#include "lcd.h"

void yaokongqi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE, ENABLE);		     //开启总线时钟
	 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
unsigned int key_scan(void)
{
	unsigned int value=0;
	if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1))
			value=1;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2))
			value=2;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3))
			value=3;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4))
			value=4;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5))
			value=5;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6))
			value=6;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7))
			value=7;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8))
			value=8;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9))
			value=9;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10))
			value=10;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
			value=11;	
		}
	}
	else if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
	{
		delay_us(10);
		if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
		{
			delay_us(10);
			while(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
			value=12;	
		}
	}
	else 
		value=0;
	return value;
}

void huanyingjiemian(void)
{
		u8 initmenu1[]="欢迎使用";
		u8 initmenu2[]="简易旋转倒立摆及";
		u8 initmenu3[]="控制装置";
	  u8 queren[]="确定";
// 	LCD_ShowString(60,80,200,16,16,"OV7670 Init OK");
// 	Lcd_WriteChineseString(40,40,CharBackColor,b);
		LCD_Clear(BLUE);
		Lcd_WriteChineseString(128,96,WHITE,initmenu1);
		Lcd_WriteChineseString(56,128,WHITE,initmenu2);
		Lcd_WriteChineseString(184,128,WHITE,initmenu3);
	  Lcd_WriteChineseString(8,224,WHITE,queren);
}
void xuanzejiemian(void)
{
	u8 xuanze[]="请选择演示功能";
	u8 gongneng1[]="基本要求";
	u8 gongneng2[]="基本要求";
	u8 gongneng3[]="基本要求";
	u8 gongneng4[]="发挥部分";
	u8 gongneng5[]="发挥部分";
	u8 gongneng6[]="发挥部分";
	LCD_Clear(BLUE);
	Lcd_WriteChineseString(104,16,WHITE,xuanze);
	Lcd_WriteChineseString(60,48,WHITE,gongneng1);
	LCD_ShowString(124,48,24,16,16,"(1)");
	Lcd_WriteChineseString(60,80,WHITE,gongneng2);
	LCD_ShowString(124,80,24,16,16,"(2)");
	Lcd_WriteChineseString(60,112,WHITE,gongneng3);
	LCD_ShowString(124,112,24,16,16,"(3)");
	Lcd_WriteChineseString(60,144,WHITE,gongneng4);
	LCD_ShowString(124,144,24,16,16,"(1)");
	Lcd_WriteChineseString(60,176,WHITE,gongneng5);
	LCD_ShowString(124,176,24,16,16,"(2)");
	Lcd_WriteChineseString(60,208,WHITE,gongneng6);
	LCD_ShowString(124,208,24,16,16,"(3)");
	LCD_ShowString(30,48,16,16,16,">>");
}
void querenjiemian(void)
{
	u8 queren[]="确定"; 
	u8 quxiao[]="取消";
	u8 tishi[]="是否确认演示";
	LCD_Clear(BLUE);
	Lcd_WriteChineseString(120,106,WHITE,tishi);
	Lcd_WriteChineseString(64,208,WHITE,queren);
	Lcd_WriteChineseString(208,208,WHITE,quxiao);
}
void yanshijiemian(void)
{
	u8 yanshi[]="正在演示请注意观看";
	LCD_Clear(BLUE);
	Lcd_WriteChineseString(52,112,WHITE,yanshi);
	delay_ms(1000);
}
void jieshujiemian(void)
{
	u8 jieshu[]="演示结束请稍等";
	LCD_Clear(BLUE);
	Lcd_WriteChineseString(84,112,WHITE,jieshu);
	delay_ms(2000);
}
void Lcd_Part_Clear(u16 x,u16 y,u16 width,u16 height,u16 CharBackColor)
{
	unsigned int i,j;
	for(j=y;j<=(y+height);j++)
	{
		for(i=x;i<=(x+width);i++)
		{
			LCD_SetCursor(i,j);	//设置光标位置 
			LCD_WriteRAM_Prepare();     //开始写入GRAM
			LCD->LCD_RAM=CharBackColor;	
		}
	}
}

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usmart.h" 
#include "lcd.h"
#include "usart.h"
#include "24l01.h" 	 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "mytask.h"

/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


//主菜单
void MUSE_TASK()
{
	u8 t=0;
	LCD_Clear(WHITE);
	Show_Str(20,30,200,24,"主菜单:",24,0);
	Show_Str(20,60,200,24,"任务1:",24,0);
	Show_Str(20,90,200,24,"任务2:",24,0);
	Show_Str(20,120,200,24,"任务3:",24,0);
	Show_Str(20,150,200,24,"任务4:",24,0);
	Show_Str(20,180,200,24,"任务5:",24,0);
	Show_Str(20,210,200,24,"任务6:",24,0);
	Show_Str(20,240,200,24,"任务7:",24,0);
	Show_Str(20,270,200,24,"任务8:",24,0);
	
	t++;
	if(t==100)
		//LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //闪烁显示提示信息
		Show_Str(10,150,230,24,"按任意键选择",24,0);
	if(t==200)
	{	
		LCD_Fill(10,150,240,150+50,WHITE);
		t=0; 
	}
	delay_ms(5);
}


//任务0
// 首先发送数据，然后接收数据
void KEY0_TASK()
{
	u8 key,mode;
	u8 time ; //计算发送次数
	u16 t=0;			 
	u8 tmp_buf[33];	
	
	u8 key_buf[33] = "key0_pres";
	
	
	LCD_Clear(WHITE);
	Show_Str(50,50,200,24,"当前任务0 :",24,0);

	NRF24L01_TX_Mode();
	mode=' ';//从空格键开始  
	
	//发送命令 key0_pres
	while(NRF24L01_TxPacket(tmp_buf)==TX_OK && time != 3)
	{
		time ++;
		LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
		LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
		for(t=0;t<32;t++)
		{
			
			tmp_buf[t]=key_buf[t];	
		}	  
		tmp_buf[32]=0;//加入结束符		   
	}
	time = 0;

	//LED0=!LED0;
	//delay_ms(1500);		
	
	//然后接收数据 读取一次按键，接收两次信息
	NRF24L01_RX_Mode();		  
	while(1)
	{	 
		Show_Str(50,70,200,24,"biaozhiwei :",24,0);
		if(t%2==0)
		{
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
			}
			else
				delay_us(100);	
		}
		if(t%4==0)
		{
			t=0;
			key=KEY_Scan(0);
			if(key==WKUP_PRES)
			{
				Show_Str(50,100,200,24,"当前任务 :",24,0);
				break;
			}
		}
		t++;    
	}	
	
}




//任务1
void KEY1_TASK()
{
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];	
	
	u8 key_buf[33] = "key1_pres";
	
	
	LCD_Clear(WHITE);
	Show_Str(50,50,200,24,"当前任务1 :",24,0);

	NRF24L01_TX_Mode();
	mode=' ';//从空格键开始  
	
	while(NRF24L01_TxPacket(tmp_buf)==TX_OK)
	{
		LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
		LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
		for(t=0;t<32;t++)
		{
			
			tmp_buf[t]=key_buf[t];	
		}	  
		tmp_buf[32]=0;//加入结束符		   
	}

//	LED0=!LED0;
//	delay_ms(1500);
	NRF24L01_RX_Mode();		  
	while(1)
	{	 
		if(t%2==0)
		{
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
			}
			else
				delay_us(100);	
		}
		else if(t%4==0)
		{
			t=0;
			key=KEY_Scan(0);
			if(key==WKUP_PRES)
			{
				break;
			}
		}
		t++;    
	}		
}





//任务2
void KEY2_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务2",24,0);
}

//任务3
void KEY3_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务3:",24,0);
}

//任务4
void KEY4_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务4:",24,0);
}

//任务5
void KEY5_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务5:",24,0);
}

//任务6
void KEY6_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务6:",24,0);
}

//任务7
void KEY7_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务7:",24,0);
}

//任务8
void KEY8_TASK()
{
	LCD_Clear(WHITE);
	Show_Str(20,50,200,24,"当前任务8",24,0);
}
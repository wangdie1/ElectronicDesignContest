#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
//#include "usmart.h" 
#include "lcd.h"
#include "usart.h"
#include "24l01.h" 	 
//#include "malloc.h"
//#include "sdio_sdcard.h"  
//#include "w25qxx.h"    
//#include "ff.h"  
//#include "exfuns.h"   
//#include "text.h"
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
//int MUSE_TASK(void)
//{
//	u8 t=0;
//	LCD_Clear(WHITE);
//	Show_Str(20,30,200,24,"主菜单:",24,0);
//	Show_Str(20,60,200,24,"任务1:",24,0);
//	Show_Str(20,90,200,24,"任务2:",24,0);
//	Show_Str(20,120,200,24,"任务3:",24,0);
//	Show_Str(20,150,200,24,"任务4:",24,0);
//	Show_Str(20,180,200,24,"任务5:",24,0);
//	Show_Str(20,210,200,24,"任务6:",24,0);
//	Show_Str(20,240,200,24,"任务7:",24,0);
//	Show_Str(20,270,200,24,"任务8:",24,0);
//	
//	t++;
//	if(t==100)
//		Show_Str(10,150,230,24,"按任意键选择",24,0);
//	if(t==200)
//	{	
//		LCD_Fill(10,150,240,150+50,WHITE);
//		t=0; 
//	}
//	delay_ms(5);
//	return 0;
//}


////任务0
//// 首先发送数据，然后接收数据
//int KEY0_TASK()
//{
//	u8 key;
//	u8 time ; //计算发送次数
//	u16 t=0;			 
//	u8 tmp_buf[33];	
//	
//	u8 key_buf[33] = "key0_pres"; //要发送的命令
//	
//	
//	LCD_Clear(WHITE);
//	Show_Str(50,50,200,24,"当前任务0 :",24,0);

//	NRF24L01_TX_Mode();

//	
//	//发送命令 key0_pres
//	while(NRF24L01_TxPacket(tmp_buf)==TX_OK && time != 3)
//	{
//		time ++;
//		LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
//		LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
//		for(t=0;t<32;t++)
//		{
//			
//			tmp_buf[t]=key_buf[t];	
//		}	  
//		tmp_buf[32]=0;//加入结束符	

//		if(KEY_Scan(0)==WKUP_PRES)
//		{
//			break;
//		}
//	}
//	time = 0;
//	
//	//然后接收数据 读取一次按键，接收两次信息
//	NRF24L01_RX_Mode();		  
//	while(1)
//	{	 
//		if(t%2==0)
//		{
//			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
//			{
//				tmp_buf[32]=0;//加入字符串结束符
//				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
//			}
//			else
//				delay_us(100);	
//		}
//		if(t%4==0)
//		{
//			t=0;
//			key=KEY_Scan(0);
//			if(key==WKUP_PRES)
//			{
//				Show_Str(50,100,200,24,"当前任务0 :",24,0);
//				break;
//			}
//		}
//		t++;    
//	}

//	return 0;
//	
//}



//int QJ_TASK(u16 pwm)
//pwm 小车的速度
int QJ_TASK(void)
{
	return 0;
}

int HT_TASK(void)
{
	return 0;
}

int ZZ_TASK(void)
{
	return 0;
}

int YZ_TASK(void)
{
	
	return 0;
}

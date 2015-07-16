#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usmart.h" 
#include "lcd.h"
#include "usart.h"
#include "mytask.h"

#include "24l01.h" 	 

#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"

 
 
/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 int main(void)
 {	 
	//定义全局变量
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];	

	 
	//函数初始化
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART	
	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	
	NRF24L01_Init();    		//初始化NRF24L01 
	 
	W25QXX_Init();				//初始化W25Q128
	my_mem_init(SRAMIN);		//初始化内部内存池
	LCD_Init();			   		//初始化LCD 
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.	 
 
	//检查中文字库
	while(font_init()) 			//检查字库
	{
		LCD_Clear(WHITE);		   	//清屏
 		POINT_COLOR=RED;			//设置字体为红色	   	   	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32");
		while(SD_Init())			//检测SD卡
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//更新字库
		while(key)//更新失败		
		{			 		  
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}  
	
	//检查无线通信
	while(NRF24L01_Check())
	{
		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}

	//初始化界面
	POINT_COLOR = MAGENTA; 
	Show_Str(20,20,200,24,"第十一届全国电子",24,0);
	Show_Str(80,50,200,24,"设计大赛",24,0);	
	
 	while(1)
	{	
		//按键扫描
		key=KEY_Scan(0);
		
		if(key!=0)
		{
			LCD_Clear(WHITE);
			Show_Str(60,20,200,24,"旋转倒立摆",24,0);
			Show_Str(20,50,200,24,"任务1:",24,0);
			Show_Str(20,80,200,24,"任务2:",24,0);
			Show_Str(20,110,200,24,"任务3:",24,0);
			Show_Str(20,140,200,24,"任务4:",24,0);
			Show_Str(20,170,200,24,"任务5:",24,0);
			Show_Str(20,200,200,24,"任务6:",24,0);
			
			while(1)
			{
				key=KEY_Scan(0);
				//WKUP_PRES  功能:返回主界面
				if(key==WKUP_PRES)
				{
					MUSE_TASK();
				}
				
				//KEY1_PRES 功能:执行任务1
				else if(key==KEY0_PRES)
				{
					KEY0_TASK();
				}
//				//KEY1_PRES 功能:执行任务1
//				else if(key==KEY1_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY2_PRES 功能:执行任务2
//				else if(key==KEY2_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY3_PRES 功能:执行任务3
//				else if(key==KEY3_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY4_PRES 功能:执行任务4
//				else if(key==KEY4_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY5_PRES 功能:执行任务5
//				else if(key==KEY5_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY6_PRES 功能:执行任务6
//				else if(key==KEY6_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY7_PRES 功能:执行任务7
//				else if(key==KEY7_PRES)
//				{
//					mode=1;
//					break;
//				}
//				//KEY8_PRES 功能:执行任务8
//				else if(key==KEY8_PRES)
//				{
//					mode=1;
//					break;
//				}
//				
			}
		}
		
		t++;
		if(t==100)
			//LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //闪烁显示提示信息
			Show_Str(10,150,230,24,"按任意键进入主菜单",24,0);
 		if(t==200)
		{	
			LCD_Fill(10,150,240,150+50,WHITE);
			t=0; 
		}
		delay_ms(5);
	} 
}	
   	
//	if(mode==3)//RX模式
//	{
//		LCD_ShowString(30,150,200,16,16,"NRF24L01 RX_Mode");	
//		LCD_ShowString(30,170,200,16,16,"Received DATA:");	
//		NRF24L01_RX_Mode();		  
//		while(1)
//		{	  		    		    				 
//			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
//			{
//				tmp_buf[32]=0;//加入字符串结束符
//				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf);    
//			}else delay_us(100);	   
//			t++;
//			if(t==10000)//大约1s钟改变一次状态
//			{
//				t=0;
//				LED0=!LED0;
//			} 				    
//		};	
//	}
//	else//TX模式
//	{							    
//		LCD_ShowString(30,150,200,16,16,"NRF24L01 TX_Mode");	
//		NRF24L01_TX_Mode();
//		mode=' ';//从空格键开始  
//		while(1)
//		{	  		   				 
//			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//			{
//				LCD_ShowString(30,170,239,32,16,"Sended DATA:");	
//				LCD_ShowString(0,190,lcddev.width-1,32,16,tmp_buf); 
//				key=mode;
//				for(t=0;t<32;t++)
//				{
//					key++;
//					if(key>('~'))key=' ';
//					tmp_buf[t]=key;	
//				}
//				mode++; 
//				if(mode>'~')mode=' ';  	  
//				tmp_buf[32]=0;//加入结束符		   
//			}else
//			{										   	
// 				LCD_Fill(0,170,lcddev.width,170+16*3,WHITE);//清空显示			   
//				LCD_ShowString(30,170,lcddev.width-1,32,16,"Send Failed "); 
//			};
//			LED0=!LED0;
//			delay_ms(1500);				    
//		};
//	} 




#include "led.h"
#include "rtc.h"
#include "Encoder.h"
#include "Control.h"
#include "delay.h"
#include "Motor.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24l01.h"
#include "mytask.h"
#include "UltrasonicWave.h"
#include "timer4_cap.h"
#include "TimeBase.h"
#include "usmart.h"
 
 
/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
void led_set(u8 sta)
{
	LED1 = sta;
	LED0 = sta;
}

void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
} 

 int main(void)
 {	 
	//全局变量
	double mm,ff;
	u8 key,x;
	 u8 i=0;
	u16 time = 350;
	u8 mode;
	 u8 state;
	u16 t=0;			 
	u8 tmp_buf[33];		    
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200   
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按
	RTC_Init();
//	usmart_dev.init(72);		//初始化USMART
//	TIM_PWM_Init();
	 MotorInit();
	//ENC_Init();
	 Encoder_Init();
//	UltrasonicWave_Configuration();
//	TIM4_Cap_Init(65535,72-1); //以1Mhz的频率计数  1/1M = 1/1,000,000   f 72M/72 = 1M  ,T  1us  计数到65536
	LCD_Init();			   		//初始化LCD  
 	NRF24L01_Init();    		//初始化NRF24L01 
 	POINT_COLOR=RED;			//设置字体为红色 
	TB_Init(10-1,719);
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"NRF24L01 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/17"); 

	//无线通信模块的检查
//	while(NRF24L01_Check())
//	{
//		LCD_ShowString(30,130,200,16,16,"NRF24L01 Error");
//		delay_ms(200);
//		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}
//	LCD_ShowString(30,130,200,16,16,"NRF24L01 OK");
	

	while(1) //主任务
	{
		if(TB_SetLed_IsElapsed() == true)
		{
//			LED1 = ~LED1;
//			LED0 = ~LED0;
			if(LED1 == 0)
			{
				LED1 = 1;
				LED0 = 0;
			}
			else 
			{
				LED1 = 0;
				LED0 = 1;
			}
			TB_SetLed_Time(LED_DELAY);
		}
		
//		LED0 = ~LED0;
//		LED1 = ~LED1;
//		delay_ms(1000);
	}	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	主控制
// 	while(1)
//	{	
//		key=KEY_Scan(0);
//		
//		if(key==KEY0_PRES)
//		{
//			mode=0;   
//			break;
//		}
//		else if(key==KEY1_PRES)
//		{
//			mode=1;
//			break;
//		}
//		t++;
//		if(t==100)LCD_ShowString(10,150,230,16,16,"KEY0:RX_Mode  KEY1:TX_Mode"); //闪烁显示提示信息
// 		if(t==200)
//		{	
//			LCD_Fill(10,150,230,150+16,WHITE);
//			t=0; 
//		}
//		delay_ms(5);	  
//	}   
// 	LCD_Fill(10,150,240,166,WHITE);//清空上面的显示		  
// 	POINT_COLOR=BLUE;//设置字体为蓝色	   
//	if(mode==0)//RX模式
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

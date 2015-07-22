#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "UltrasonicWave.h"
#include "timer4_cap.h"


//广州市星翼电子科技有限公司 
 	
 int main(void)
 {	 
 	u8 x=0;
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	TIM4_Cap_Init(0xffff,72-1); //以1Mhz的频率计数
	
	
	UltrasonicWave_Configuration();    //对超声波模块初始化
	 
	 LCD_Init();
	POINT_COLOR=RED;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。				 	
  
	 POINT_COLOR=RED;	  
		LCD_ShowString(30,50,200,16,16,"WarShip STM32 ^_^");	
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");	

 		LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(30,130,200,16,16,"2014/10/5");	  
	
	while(1) 
	{		 
		UltrasonicWave_StartMeasure(); 
		//LED2_TOGGLE;
		LCD_ShowxNum(60,190,tempup1,3,16,0X80);	//显示数据
		printf("Channel 1 : %d cm\r\n",tempup1);
//		delay_ms(10);
//		printf("Channel 2 : %d cm\r\n",tempup2);
//		delay_ms(10);
//		printf("Channel 3 : %d cm\r\n",tempup3);
//		delay_ms(10);
//		printf("Channel 4 : %d cm\r\n",tempup4);
		    					 
	    x++;
		if(x==12)x=0;
		LED0=!LED0;					 
	//	delay_ms(1000);	
	} 
}

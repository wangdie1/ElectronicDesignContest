#include "menu.h"
#include "ili9320.h"
#include "lcd.h"

/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


//界面菜单


//void Control_fanA(void)
//{
//	u8 key,i=0;
//	u16 pwm;//pwm的重转载值为1000
//	while(1)
//	{
//		key=KEY_Scan(0);
//		if(key==KEY1_PRES)
//		{
//			LED0 =!LED0;
//			i++;
//			pwm = 100*i;
//			FanA_Forward(pwm);
//			if(i > 10)
//				i = 10;
//		}
//		if(key == KEY2_PRES)
//		{
//			LED1=!LED1;
//			i--;
//			pwm = 100 * i;
//			FanA_Forward(i*100);
//			if(i<1)
//				i = 0;
//		}
//	}	
//}

void MainMenu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(10,20,200,16,16,"SCHOOL:");
	LCD_ShowString(10,60,200,16,16,"TITLE:"); 
	LCD_ShowString(10,100,200,16,16,"TIME:");
	 
	POINT_COLOR=RED;
	LCD_ShowString(20,40,200,16,16,"WuChang ShouYi University");
	LCD_ShowString(20,80,200,16,16,"Wind pendulum");	
	LCD_ShowString(20,120,200,16,16,"2015/8/12 - 2015/8/15"); 
	
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  140,  235, 140);
	LCD_DrawLine(5 ,  10,   235, 10);
	LCD_DrawLine(5 ,  10,   5,   140);
	LCD_DrawLine(235 ,10,   235, 140);
}

//状态菜单栏
void StateMenu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(10,160,200,16,16,"STATE");
	LCD_ShowString(10,260,200,16,16,"PROMPR"); 
//	LCD_ShowString(10,100,200,16,16,"TIME:");
	 
	POINT_COLOR=RED;
	LCD_ShowString(20,200,200,16,16,"ROMOTE     OK"); 
	LCD_ShowString(20,220,200,16,16,"LM298      OK "); 
	LCD_ShowString(20,240,200,16,16,"NRF24L01   OK"); 
	
	LCD_ShowString(20,280,200,16,16,"press any key to perform "); 
	
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}


void TASTMenu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(100,160,200,16,16,"MENU");
	LCD_ShowString(20,180,200,16,16,"1:");
	LCD_ShowString(20,200,200,16,16,"2:"); 
	LCD_ShowString(20,220,200,16,16,"3:"); 
	LCD_ShowString(20,240,200,16,16,"4:"); 
	LCD_ShowString(20,260,200,16,16,"5:");
	LCD_ShowString(20,280,200,16,16,"6:");	
	
	 
	POINT_COLOR=RED;
	LCD_ShowString(40,180,200,16,16,"Draw a line segment");
	LCD_ShowString(40,200,200,16,16,"Set a line segment"); 
	LCD_ShowString(40,220,200,16,16,"Draw a line segment direction can be set");
	LCD_ShowString(40,240,200,16,16,"Eli put the winds pendulum reach disabled"); 
	LCD_ShowString(40,260,200,16,16,"Draw a circle radius can be set");
	 
	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}

void TAST1_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	LCD_ShowString(80,160,200,16,16,"BASETAST1");
	LCD_ShowString(20,180,200,16,16,"MPU6050-STATE:");
	LCD_ShowString(20,280,200,16,16,"BREAK(Press any key):");
	 
	POINT_COLOR=RED;
 	LCD_ShowString(30,200,200,16,16,"Temp :");	
 	LCD_ShowString(30,220,200,16,16,"Pitch:");	
 	LCD_ShowString(30,240,200,16,16,"Roll :");	 
 	LCD_ShowString(30,260,200,16,16,"Yaw  :");	

	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}


void TAST2_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(80,160,200,16,16,"BASETAST2");
	LCD_ShowString(20,180,200,16,16,"SET LENGTH:"); 
//	LCD_ShowString(20,220,200,16,16,"3:"); 
//	LCD_ShowString(20,240,200,16,16,"BREAK"); 

	POINT_COLOR=RED; 
	LCD_ShowString(20,200,200,16,16,"length:    cm"); 
//	LCD_ShowString(50,260,200,16,16,"E:");
//	LCD_ShowString(50,280,200,16,16,"F:");	 
	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}

void TAST3_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(80,160,200,16,16,"BASETAST3");
	LCD_ShowString(20,180,200,16,16,"SET ANGER:");
//	LCD_ShowString(20,200,200,16,16,"2:"); 
//	LCD_ShowString(20,220,200,16,16,"3:"); 
//	LCD_ShowString(20,240,200,16,16,"BREAK"); 
//	LCD_ShowString(20,260,200,16,16,"5:");
//	LCD_ShowString(20,280,200,16,16,"6:");	
	
	 
	POINT_COLOR=RED;
	LCD_ShowString(20,200,200,16,16,"anger:     "); 
//	LCD_ShowString(50,180,200,16,16,"A:");
//	LCD_ShowString(50,200,200,16,16,"B:"); 
//	LCD_ShowString(50,220,200,16,16,"C:"); 
//	LCD_ShowString(50,240,200,16,16,"D:"); 
//	LCD_ShowString(50,260,200,16,16,"E:");
//	LCD_ShowString(50,280,200,16,16,"F:");	 
	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}
void TAST4_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(80,160,200,16,16,"BASETAST4");
	LCD_ShowString(20,180,200,16,16,"REQURE:");
	LCD_ShowString(20,240,200,16,16,"NOW STATE:"); 
//	LCD_ShowString(20,220,200,16,16,"3:"); 
	LCD_ShowString(20,280,200,16,16,"BREAK"); 
//	LCD_ShowString(20,260,200,16,16,"5:");
//	LCD_ShowString(20,280,200,16,16,"6:");	
	
	 
	POINT_COLOR=RED;
	LCD_ShowString(50,200,200,16,16,"Pull the pendulum to ");
	LCD_ShowString(20,220,200,16,16,"30 - 45 degrees"); 
//	LCD_ShowString(50,240,200,16,16,"D:"); 
	LCD_ShowString(50,260,200,16,16,"Not completed");
//	LCD_ShowString(50,280,200,16,16,"F:");	 
//	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}

void TAST5_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(80,160,200,16,16,"EXERTTAST1");
	LCD_ShowString(20,180,200,16,16,"SET THE RADIUS");
	LCD_ShowString(20,200,200,16,16,"RADIUS:    cm"); 
//	LCD_ShowString(20,220,200,16,16,"3:"); 
//	LCD_ShowString(20,240,200,16,16,"BREAK"); 
//	LCD_ShowString(20,260,200,16,16,"5:");
	LCD_ShowString(20,280,200,16,16,"BREAK:");	
	
	 
	POINT_COLOR=RED;
//	LCD_ShowString(50,180,200,16,16,"A:");
//	LCD_ShowString(50,200,200,16,16,"B:"); 
//	LCD_ShowString(50,220,200,16,16,"C:"); 
//	LCD_ShowString(50,240,200,16,16,"D:"); 
//	LCD_ShowString(50,260,200,16,16,"E:");
//	LCD_ShowString(50,280,200,16,16,"F:");	 
//	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}

void END_Menu(void)
{
	POINT_COLOR=BLUE;			//设置字体为红色 
	
	LCD_ShowString(100,160,200,16,16,"END");
//	LCD_ShowString(20,180,200,16,16,"THANK YOU");
//	LCD_ShowString(20,200,200,16,16,"2:"); 
	LCD_ShowString(80,220,200,16,16,"THANK YOU"); 
//	LCD_ShowString(20,240,200,16,16,"BREAK"); 
//	LCD_ShowString(20,260,200,16,16,"5:");
//	LCD_ShowString(20,280,200,16,16,"6:");	
	
	 
	POINT_COLOR=RED;
//	LCD_ShowString(50,180,200,16,16,"A:");
//	LCD_ShowString(50,200,200,16,16,"B:"); 
//	LCD_ShowString(50,220,200,16,16,"C:"); 
//	LCD_ShowString(50,240,200,16,16,"D:"); 
//	LCD_ShowString(50,260,200,16,16,"E:");
//	LCD_ShowString(50,280,200,16,16,"F:");	 
//	LCD_ShowString(20,280,200,16,16,"BREAK:");
	POINT_COLOR=BLACK;
	LCD_DrawLine(5 ,  310,  235, 310);
	LCD_DrawLine(5 ,  150,   235, 150);
	LCD_DrawLine(5 ,  150,   5,   310);
	LCD_DrawLine(235 ,150,   235, 310);
}





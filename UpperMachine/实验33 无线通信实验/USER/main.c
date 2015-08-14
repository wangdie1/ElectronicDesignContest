#include "init.h"
#include "ili9320.h"
#include "menu.h"

 
 
/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//extern float PID_P ;
//extern float PID_I ;
//extern float PID_D ;
//void set_PID(u16 P,u16 I,u16 D)
//{
//	PID_P = P/100.0;
//	PID_I = I/100.0;
//	PID_D = D/100.0;
//}

//void led_set(u16 sta)
//{
//	PID_P = sta;
//	LED0 = sta;
//}

//void test_fun(void(*ledset)(u8),u8 sta)
//{
//	ledset(sta);
//} 


//设置pid的值,精确到小数点后2位



int main(void)
 {	 	 
	u8 key;
//	float pitch,roll,yaw; 		//欧拉角
//	short aacx,aacy,aacz;		//加速度传感器原始数据
//	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
//	short temp;					//温度	
	ili9320_Initializtion();//液晶屏初始化
	Init();                    //部分函数初始化
	
	 //界面初始化
	MainMenu();                 //主菜单栏
	StateMenu();
	while(mpu_dmp_init())       //初始化mpu6050
 	{
		LCD_ShowString(20,160,200,16,16,"MPU6050 Error");
		delay_ms(200);
	}  
	POINT_COLOR=RED;
	LCD_ShowString(20,180,200,16,16,"MPU6050    OK");

//MainMenu();
 	while(1)
	{
		key = KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			LCD_ShowNum(86,220,key,5,16);
			//刷新lcd页面
			LCD_Clear(WHITE);	
			MainMenu();
			TASTMenu();
			while(1)
			{
				key = KEY_Scan(0);
				if(key != 0)
				{
					if(key == KEYA_PRES)   //基础任务1
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST1_Menu();
						Perform_BaseTask1();
					}
					else if(key == KEYB_PRES) //基础任务2
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST2_Menu();
						Perform_BaseTask2();
					}
					else if(key == KEYC_PRES) //基础任务3
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST3_Menu();
						Perform_BaseTask3();
					}
					else if(key == KEYD_PRES) //基础任务4
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST4_Menu();
						Perform_BaseTask4();
					}
					else if(key == KEYE_PRES) //发挥任务1
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST5_Menu();
						Perform_ExertTask1();
					}
					
					else if(key == WKUP_PRES)  //演示结束
					{
						LCD_Clear(WHITE);	
						MainMenu();
						END_Menu();
						break;
					}
				}
			}

		}
	}
}
		
		

		
//红外遥糠绞截
//		if(Remote_Scan()!=0)
//		{
//			delay_ms(10);
//			LCD_Clear(WHITE);	
//			MainMenu();
//			TASTMenu();
//			while(1)
//			{
//				if(Remote_Scan()!=0)
//				{
//					key=Remote_Scan();
//					stri = Remote_Read(key);
//					
//					if(stri == 1)  //执行任务1
//					{
//						LCD_Clear(WHITE);	
//						MainMenu();
//						TAST1_Menu();
//						Perform_Task1();
//					}
//					else if(stri == 2)//执行任务2
//					{
//						LCD_Clear(WHITE);	
//						MainMenu();
//						TAST2_Menu();
//						Perform_Task2();
//					}
//					else if(stri == 3 )//执行任务3
//					{
//						LCD_Clear(WHITE);	
//						MainMenu();
//						TAST3_Menu();
//						Perform_Task3();
//					}
//					else if(stri == DELETE )
//					{
//						break;
//					}
//				}
//				else 
//					delay_ms(1);
//			}
//		}
//		else
//		{
//			delay_ms(1);
//		}
//	}
//}
		

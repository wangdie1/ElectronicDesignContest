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
//	u8 t=0,report=1;			//默认开启上报
//	u8 key;
	 
	u8 key;
	u8 t=0;	
	u8 stri=0;
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	
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
//	BEEP = 1;
//	LCD_ShowString(30,200,200,16,16,"KEY0:UPLOAD ON/OFF");
//	POINT_COLOR=BLUE;//设置字体为蓝色 
// 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
// 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
// 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
// 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
// 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");

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
					if(key == KEYA_PRES)
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST1_Menu();
						Perform_BaseTask1();
					}
					else if(key == KEYB_PRES)
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST2_Menu();
						Perform_BaseTask2();
					}
					else if(key == KEYC_PRES)
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST3_Menu();
						Perform_BaseTask3();
					}
					else if(key == KEYD_PRES)
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST4_Menu();
						Perform_BaseTask4();
					}
					else if(key == KEYE_PRES)
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST5_Menu();
						Perform_ExertTask1();
					}
					
					else if(key == WKUP_PRES)  //退出该层界面
					{
						delay_ms(10);
						key = 0;
						break;
					}
				}
			}

		}
//		delay_ms(100);
		
		

		
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
	}
}
		


//int main(void)
// {	 
//	u8 t=0,report=1;			//默认开启上报
//	u8 key;
//	float pitch,roll,yaw; 		//欧拉角
//	short aacx,aacy,aacz;		//加速度传感器原始数据
//	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
//	short temp;					//温度	
//	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	uart_init(500000);	 	//串口初始化为500000
//	delay_init();	//延时初始化 
//	usmart_dev.init(72);		//初始化USMART
//	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
////	LCD_Init();			   		//初始化LCD
//	ili9320_Initializtion();	 
//	MPU_Init();					//初始化MPU6050
// 	POINT_COLOR=RED;			//设置字体为红色 
//	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
//	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
//	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(30,110,200,16,16,"2015/1/17"); 
//	while(mpu_dmp_init())
// 	{
//		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
//		delay_ms(200);
////		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}  
//	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
//	LCD_ShowString(30,150,200,16,16,"KEY0:UPLOAD ON/OFF");
//	POINT_COLOR=BLUE;//设置字体为蓝色 
// 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
// 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
// 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
// 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
// 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");	 
// 	while(1)
//	{
//		key=KEY_Scan(0);

//		if(key==KEYA_PRES)
//		{
//			report=!report;
//			if(report)LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");
//			else LCD_ShowString(30,170,200,16,16,"UPLOAD OFF");
//		}
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0) //处理dma处理后的数据
//		{
//			//mpu6050的采样频率
//			temp=MPU_Get_Temperature();	//得到温度值
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//			
//			//把处理后的值发送给匿名上位机
//			if(report)
//				mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//用自定义帧发送加速度和陀螺仪原始数据
//			if(report)
//				usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
//			
//			
//			           if((t%10)==0)
//			{ 
//				//温度值
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,200,'-',16,0);		//显示负号
//					temp=-temp;		//转为正数
//				}
//				else LCD_ShowChar(30+48,200,' ',16,0);		//去掉负号 
//				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//显示整数部分	    
//				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//显示小数部分 
//				printf("%d\r\n",temp);
//				//欧拉角 pitch
//				temp=pitch*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,220,'-',16,0);		//显示负号
//					temp=-temp;		//转为正数
//				}
//				else LCD_ShowChar(30+48,220,' ',16,0);		//去掉负号 
//				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//显示整数部分	    
//				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//显示小数部分 
//				printf("%d\r\n",temp);
//				//欧拉角 roll
//				temp=roll*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,240,'-',16,0);		//显示负号
//					temp=-temp;		//转为正数
//				}
//				else LCD_ShowChar(30+48,240,' ',16,0);		//去掉负号 
//				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//显示整数部分	    
//				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//显示小数部分 
//				printf("%d\r\n",temp);
//				//欧拉角 yaw
//				temp=yaw*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,260,'-',16,0);		//显示负号
//					temp=-temp;		//转为正数
//				}else LCD_ShowChar(30+48,260,' ',16,0);		//去掉负号 
//				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//显示整数部分	    
//				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//显示小数部分  
//				printf("%d\r\n",temp);
//				t=0;
//				LED0=!LED0;//LED闪烁
//			}
//		}
//		t++; 
//	} 	
//}
// 

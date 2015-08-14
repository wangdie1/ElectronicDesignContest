#include "mytask.h"
#include "init.h"
#include "menu.h"
#include "math.h"


/************************************************
 ALIENTEK战舰STM32开发板实验33
 无线通信 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


//执行任务1的方法一
void function_A(void)
{
	int i=0;
	LCD_ShowString(150,200,200,16,16,"start");
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;

	FanAB_Backward(1000);
	delay_ms(450);
	for( i = 0;i<5;i++)
	{
	//单摆周期起荡   -- 2πv(L/g)    
		FanAB_Forward(1000);
		delay_ms(850);
		FanAB_Backward(1000);
		delay_ms(850);	
	}
	for( i = 0;i<12;i++)
	{
	//单摆周期起荡   -- 2πv(L/g)    
		FanAB_Forward(920);
		delay_ms(900);
		FanAB_Backward(920);
		delay_ms(900);	
	}
	
	for( i = 0;i<5;i++)
	{
	//单摆周期起荡   -- 2πv(L/g)    
		FanCD_Backward(920);
		delay_ms(450);
		FanCD_Forward(920);
		delay_ms(450);		
	}
	
	FanAB_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}



//任务一的方法二
void function_A2(void)
{
	u8 preRoll = 0,lastRoll = 0;
	u8 prepitch = 0,lastpitch = 0;
	u8 target = 80;
	int sign=-1;
	int i=0;
	float pitch,roll,yaw; 		//欧拉角
	LCD_ShowString(150,200,200,16,16,"start");
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
    
	//快速起荡
	for( i = 0;i<4;i++)
	{
		//单摆周期起荡   -- 2πv(L/g)    
		FanAB_Forward(1000);
		delay_ms(850);
		FanAB_Backward(1000);
		delay_ms(850);
		
	}
	
	mpu_dmp_get_data(&pitch,&roll,&yaw);
	prepitch  = pitch; 
	
	//进入任务1中
    while(1)
	{
		if(TB_Main_isElapsed()==true)
		{
			TB_SetMain_Time(MAIN_DELAY);
			//设定采样周期   T = 5ms
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			//x轴，y轴   pitch roll

            lastpitch = pitch;
			LCD_ShowNum(30+48+8,240,lastpitch-prepitch,3,16);		
			if(lastpitch * sign < prepitch *sign)// || lastpitch * sign > target * sign)
			{		
				sign *= -1;
				MotorAB_PWM_Update(sign*1000);
				
			}	
			prepitch = lastpitch;
			delay_ms(10);
			LCD_ShowNum(30+48+8,220,pitch,3,16);	
				
			//把pitch roll传入pid
			
			//把pid得出的值放入pwm中
			
		}
	}

}



//执行基础部分任务一
void Perform_BaseTask1(void)
{
	u8 key;
	
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;

	while(1)
	{
		//-----------------按键扫描部分
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)     //返回上一层菜单
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
//			LCD_ShowNum(86,240,key,5,16);
			else if(key ==KEYCF_PRES)
			{
				function_A(); //进入任务的执行阶段
			}
		}

		//--------------------mpu6050检测部分-----------------------------
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0) //处理dma处理后的数据
		{
		//mpu6050的采样频率
			temp=MPU_Get_Temperature();	//得到温度值
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
		}	
		
		
		if(temp>=0)
		{
			LCD_ShowChar(30+48,200,' ',16,0);
			LCD_ShowNum(30+48+8,200,temp/100,3,16);		//显示整数部分
		}
		else 
		{
			LCD_ShowChar(30+48,200,'-',16,0);		//显示负号
			temp = -pitch;
			LCD_ShowNum(30+48+8,200,temp/100,3,16);		//显示整数部分
		}
		if(pitch>=0)
		{
			LCD_ShowChar(30+48,220,' ',16,0);
			LCD_ShowNum(30+48+8,220,pitch,3,16);		//显示整数部分
		}
		else 
		{
			LCD_ShowChar(30+48,220,'-',16,0);		//显示负号
			pitch = -pitch;
			LCD_ShowNum(30+48+8,220,pitch,3,16);		//显示整数部分
		}
		
		//显示roll
		if(roll>=0)
		{
			LCD_ShowChar(30+48,240,' ',16,0);
			LCD_ShowNum(30+48+8,240,roll,3,16);		//显示整数部分
		}
		else
		{
			LCD_ShowChar(30+48,240,'-',16,0);		//显示负号
			roll = -roll;
			LCD_ShowNum(30+48+8,240,roll,3,16);		//显示整数部分
		}
		//显示yaw
		if(aacz>=0)
		{
			LCD_ShowChar(30+48,260,' ',16,0);
			LCD_ShowNum(30+48+8,260,yaw,3,16);		//显示整数部分
		}
		else
		{
			LCD_ShowChar(30+48,260,'-',16,0);		//显示负号
			yaw = -yaw;
			LCD_ShowNum(30+48+8,260,yaw,3,16);		//显示整数部分
		}

		//数据处理部分  dealdate
		//delay_ms(100);
	}
}


//执行任务2的自动控制部分  -- 方式一 画表 建立长度与pwm的关系
void function_B(u8 length)
{
	int i=0;
	u16 pwm = 1000;
//	u16 T;
//	T=2*3.1415*
	
	//长度对应的pwm表
	int length_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	LCD_ShowString(150,200,200,16,16,"two start");
	//开始的声音提示
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//求得对应角度对应的pwm的值
	pwm = length_pwm[length-30];
						
	//单摆周期起荡   快速到达15cm
	for(i = 0;i<4;i++)
	{
		FanAB_Forward(1000);
		delay_ms(840);
		FanAB_Backward(1000);
		delay_ms(840);	
	}
	
	//30-60,预测45cm的周期
	for( i = 0;i<10;i++)
	{
	//单摆周期起荡   -- 2πv(L/g)    
		FanAB_Forward(pwm);
		delay_ms(840);
		FanAB_Backward(pwm);
		delay_ms(840);	
	}
	
	//速度反向,快速停止  3
	for(i = 0;i<3;i++)
	{
		FanAB_Backward(1000);
		delay_ms(840);
		FanAB_Forward(1000);
		delay_ms(840);
	}
	
	FanAB_Backward(1000);
	delay_ms(400);
	
	//结束声音提示停止
	FanAB_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}
//执行基础部分任务二
void Perform_BaseTask2(void)
{
	int LineLength = 45;
//	u8 mm;
	u8 key;
//	LCD_ShowNum(86,240,111,5,16);
	while(1)
	{
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)	//返回上一层菜单
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
//			LCD_ShowNum(86,240,key,5,16);
			//设定划线长度
			if(key == KEYADD_PRES)
			{
				if(LineLength>=60)
				{
					LineLength=30;	
				}
				else
				{
					LineLength++;
				}
			}
			else if(key == KEYDCS_PRES)
			{
				if(LineLength<=30)
				{
					LineLength=60;	
				}
				else
				{
					LineLength--;
				}
			}
			//按确认键执行任务2
			if(key == KEYCF_PRES)
			{
				function_B(LineLength);
			}
		}
		
		LCD_ShowNum(74,200,LineLength,4,16);
	}
}	

//执行任务3的自动控制部分
//不需要规定指定方向的线段长度
void function_C(u8 anger)
{
	int i=0;
	//定义四个风机的pwm
	u16 pwm = 1000;
	u16 ABpwm,CDpwm;
	double Anger = 0;
	double PI = 3.1415926535;
	float CosAnger,SinAnger;
	float length = 40;
	
	//x轴角度对应的pwm表
	int x_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	
	//y轴角度对应的pwm表
	int y_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	
	
	LCD_ShowString(150,200,200,16,16,"three start");
	//开始的声音提示
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//求得对应角度对应的pwm的值
//	pwm = anger_pwm[length-30];
	Anger = anger*PI/180;  //求得角度值
	CosAnger = cos(Anger);    //
	SinAnger = sin(Anger);
//	LCD_ShowNum(86,240,anger,5,16);
	
	//求得各项的pwm值
	ABpwm = pwm*CosAnger;
	CDpwm = pwm*SinAnger;
	
	for( i = 0;i<12;i++)     //12 * (840* 2) 12 * 16 = 20s左右;
	{
	//单摆周期起荡   -- 2πv(L/g) 
		FanCD_Backward(1000);  
		FanAB_Backward(1000);
		
		delay_ms(900);	
		FanCD_Forward(1000);
		FanAB_Forward(1000);
		
		delay_ms(900);
		
	}
	//减速缓冲
//	FanAB_Backward(1000);
//	delay_ms(400);
//	
	//结束声音提示停止
	FanABCD_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}


//执行基础部分任务三
void Perform_BaseTask3(void)
{
	u8 LineAnger = 0;
	u8 key;
	LCD_ShowNum(86,240,111,5,16);
	while(1)
	{
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)	//返回上一层菜单
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
//			LCD_ShowNum(86,240,key,5,16);
			
			if(key == KEYADD_PRES)
			{
				if(LineAnger>=36)
				{
					LineAnger=36;	
				}
				else
				{
					LineAnger++;
				}
			}
			else if(key == KEYDCS_PRES)
			{
				if(LineAnger<=0)
				{
					LineAnger=0;	
				}
				else
				{
					LineAnger--;
				}
			}
			//按确认键执行任务3
			if(key == KEYCF_PRES)
			{
				function_C(LineAnger);
			}
		}
		LCD_ShowNum(74,200,LineAnger*10,4,16);
		
	}
}	


////执行任务4的自动控制部分
void function_D(void)
{
	while(1)
	{
		
	}
}

//执行基础部分任务四
void Perform_BaseTask4(void)
{
	//						LCD_ShowNum(86,240,5000,5,16);
	u8 key;
	while(1)
	{
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)	//返回上一层菜单
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
			else if(key == KEYCF_PRES)
			{
				function_D();
			}
//			LCD_ShowNum(86,240,key,5,16);
		}	
	}
}	


//发挥部分 -- 
void function_E(u8 radius)
{
	int i=0;
	u16 pwm = 1000;
	
	//长度对应的pwm表
//	int length_pwm[30]={ 1000,1000,1000,1000,1000,
//					    1000,1000,1000,1000,1000,
//					    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000 };
	
	LCD_ShowString(150,200,200,16,16,"six start");
	//开始的声音提示
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//求得对应角度对应的pwm的值
//	pwm = length_pwm[length-30];
	
	for( i = 0;i<120;i++)
	{
	//单摆周期起荡   -- 2πv(L/g) 
		FanABCD_Brk();		
		FanAB_Forward(pwm);
		delay_ms(420);
		
		FanABCD_Brk();	
		FanCD_Forward(pwm);
		delay_ms(420);
		
		FanABCD_Brk();	
		FanAB_Backward(pwm);
		delay_ms(420);
		
		FanABCD_Brk();	
		FanCD_Backward(pwm);
		delay_ms(420);		
	}
	//结束声音提示停止
	FanABCD_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}

//执行发挥部分(一二)
void Perform_ExertTask1(void)
{
	//						LCD_ShowNum(86,240,5000,5,16);
	u8 key;
	u8 RouldRadius = 25;
	while(1)
	{
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)	//返回上一层菜单
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
			LCD_ShowNum(86,240,key,5,16);
			
			if(key == KEYADD_PRES)
			{
				if(RouldRadius>=35)
				{
					RouldRadius=15;	
				}
				else
				{
					RouldRadius++;
				}
			}
			else if(key == KEYDCS_PRES)
			{
				if(RouldRadius<=15)
				{
					RouldRadius=35;	
				}
				else
				{
					RouldRadius--;
				}
			}
			//按确认键执行任务3
			if(key == KEYCF_PRES)
			{
				function_E(RouldRadius);
			}
		}
		
		LCD_ShowNum(74,200,RouldRadius,4,16);	
	}
}





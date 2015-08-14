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
//int QJ_TASK(void)
//{
//	return 0;
//}

//int HT_TASK(void)
//{
//	return 0;
//}

//int ZZ_TASK(void)
//{
//	return 0;
//}

//int YZ_TASK(void)
//{
//	
//	return 0;
//}


////倒立摆任务集

//void Dlb_TASK_1(void)
//{
//	 while(1)
//	 {
//		 MotorB_Backward(450);
//		delay_ms(80);
//		 MotorB_Brk();
//		delay_ms(340);
//		
//		MotorB_Forward(450);
//		delay_ms(80);
//		MotorB_Brk();
//		delay_ms(340);
//	 }
//}

////圆周运动
//void Dlb_TASK_2(void)
//{
//	 while(1)
//	 {
//		MotorB_Backward(800);
//		delay_ms(80);
//		 MotorB_Brk();
//		delay_ms(340);
//		
//		MotorB_Forward(800);
//		delay_ms(80);
//		MotorB_Brk();
//		delay_ms(340);
//	 }
//}


////倒立摆任务3程序

//void DLB_TASK_3(void)
//{
//	u16 enc;
//	int pwm1;
//	
//	//获得编码器的值
//	enc = Encoder_Get_Counter();
//	
//	//300ms的频率打印到串口
//	if(TB_Delay_IsElapsed() == true)  
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d\r\n",TIM3->CNT);	
//	}
//	
//	//pwm输出
//	if(enc > 360 && enc < 440)
//	{
//		pwm1= User_PidPosControl(enc,400);
//		MotorB_PWM_Update(pwm1);
//	}
//	else
//	{
//		MotorB_Brk();
//	}
//}
//	

////倒立摆任务4程序  --原地起摆 
//void DLB_TASK_4(void)
//{
//	int enc;
//	int pwm1;
//	
//	//获得位置环
//	enc = Encoder1_Get_Counter();
//	if(800-enc < 400)
//		enc = enc - 800;
//	//300ms的频率打印到串口
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d\r\n",enc);	
//	}
//	
//	//pwm输出
//	if(enc>-100 && enc<100)
//	{
//		pwm1 = User_PidPosControl(enc,0);
//		MotorB_PWM_Update(-pwm1);
//	}
//	else	
//	{
//		MotorB_Brk();
//	}
//}


//void DLB_TASK_5(void)
//{
//	int enc,enc1;
//	int pwm,mpwm1;
//	double speed;
//	
//	//位置环
//	enc = Encoder1_Get_Counter();
//	//速度环
//	speed = ENC1_Get_Speed();

//	//300ms的频率打印到串口
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d    enc1:%lf\r\n",enc,speed);	
//	}
//	
//	
//	//pwm输出
////	if(enc>-100 && enc<100)
////	{
////		pwm1 = User_PidPosControl(enc,0);
////		MotorB_PWM_Update(-pwm1);
////	}
////	else	
////	{
////		MotorB_Brk();
////	}
//}

//void DLB_TASK_6(void)
//{
//	int enc,enc1;
//	int pwm,mpwm1;
//	double speed;
//	
//	//位置环
//	enc = Encoder1_Get_Counter();
//	//速度环
//	speed = ENC1_Get_Speed();

//	//300ms的频率打印到串口
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d    enc1:%lf\r\n",enc,speed);	
//	}
//	
	
	//pwm输出
//	if(enc>-100 && enc<100)
//	{
//		pwm1 = User_PidPosControl(enc,0);
//		MotorB_PWM_Update(-pwm1);
//	}
//	else	
//	{
//		MotorB_Brk();
//	}
//}
	
//	LCD_ShowxNum(30,190,PID_I,7,16,0);
//	LCD_ShowxNum(30,210,PID_D,7,16,0);
////}


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
//	for( i = 0;i<120;i++)
//	{
//	//单摆周期起荡   -- 2πv(L/g)    
//		FanAB_Forward(920);
//		delay_ms(850);
//		FanAB_Backward(920);
//		delay_ms(850);	
//	}
	FanAB_Forward(1000);
	delay_ms(400);
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
	u8 prepitch = 0,preBpitch=0,lastpitch = 0;
	u8 target = 80;
	int sign=1;
	int i=0;
	float pitch,roll,yaw; 		//欧拉角
	LCD_ShowString(150,200,200,16,16,"start");
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
    
	//快速起荡
	for( i = 0;i<3;i++)
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
			
			//roll的值放入pid中,控制roll的值保持在0  y轴保持
			
			
			//x轴采样
			
//			if(pitch>0)
//			{
//				preApitch = pitch;
//			
//				if(lastpitch > preApitch)
//				{
//					preApitch = lastpitch;
//					FanAB_Forward(1000);
//				}
//				else
//				{
////					preApitch = lastpitch;
//					FanAB_Backward(1000);
//				}
//			}else if(pitch<0)
//			{
//				preBpitch = pitch;
//				if(lastpitch < preBpitch)
//				{
//					preBpitch = lastpitch;
//					FanAB_Backward(1000);
//				}
//				else
//				{
//					FanAB_Forward(1000);
//				}
//			}

            lastpitch = pitch;
			if(lastpitch * sign <= prepitch *sign || lastpitch * sign >= target * sign)
			{
				sign *= -1;
				MotorAB_PWM_Update(sign*1000);
			}	
			prepitch = lastpitch;
			
				
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
		FanAB_Forward(ABpwm);
		FanCD_Forward(CDpwm);
		delay_ms(840);
		FanAB_Backward(ABpwm);
		FanCD_Forward(CDpwm);
		delay_ms(840);	
	}
	//减速缓冲
	FanAB_Backward(1000);
	delay_ms(400);
	
	//结束声音提示停止
	FanAB_Brk();
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





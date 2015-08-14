#include "mytask.h"
#include "init.h"
#include "menu.h"
#include "math.h"


/************************************************
 ALIENTEKս��STM32������ʵ��33
 ����ͨ�� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


//ִ������1�ķ���һ
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
	//����������   -- 2��v(L/g)    
		FanAB_Forward(1000);
		delay_ms(850);
		FanAB_Backward(1000);
		delay_ms(850);	
	}
	for( i = 0;i<12;i++)
	{
	//����������   -- 2��v(L/g)    
		FanAB_Forward(920);
		delay_ms(900);
		FanAB_Backward(920);
		delay_ms(900);	
	}
	
	for( i = 0;i<5;i++)
	{
	//����������   -- 2��v(L/g)    
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



//����һ�ķ�����
void function_A2(void)
{
	u8 preRoll = 0,lastRoll = 0;
	u8 prepitch = 0,lastpitch = 0;
	u8 target = 80;
	int sign=-1;
	int i=0;
	float pitch,roll,yaw; 		//ŷ����
	LCD_ShowString(150,200,200,16,16,"start");
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
    
	//������
	for( i = 0;i<4;i++)
	{
		//����������   -- 2��v(L/g)    
		FanAB_Forward(1000);
		delay_ms(850);
		FanAB_Backward(1000);
		delay_ms(850);
		
	}
	
	mpu_dmp_get_data(&pitch,&roll,&yaw);
	prepitch  = pitch; 
	
	//��������1��
    while(1)
	{
		if(TB_Main_isElapsed()==true)
		{
			TB_SetMain_Time(MAIN_DELAY);
			//�趨��������   T = 5ms
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			//x�ᣬy��   pitch roll

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
				
			//��pitch roll����pid
			
			//��pid�ó���ֵ����pwm��
			
		}
	}

}



//ִ�л�����������һ
void Perform_BaseTask1(void)
{
	u8 key;
	
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;

	while(1)
	{
		//-----------------����ɨ�貿��
		key =KEY_Scan(0);
		if(key!=0)
		{
			delay_ms(10);
			if(key == WKUP_PRES)     //������һ��˵�
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
//			LCD_ShowNum(86,240,key,5,16);
			else if(key ==KEYCF_PRES)
			{
				function_A(); //���������ִ�н׶�
			}
		}

		//--------------------mpu6050��ⲿ��-----------------------------
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0) //����dma����������
		{
		//mpu6050�Ĳ���Ƶ��
			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
		}	
		
		
		if(temp>=0)
		{
			LCD_ShowChar(30+48,200,' ',16,0);
			LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������
		}
		else 
		{
			LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
			temp = -pitch;
			LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������
		}
		if(pitch>=0)
		{
			LCD_ShowChar(30+48,220,' ',16,0);
			LCD_ShowNum(30+48+8,220,pitch,3,16);		//��ʾ��������
		}
		else 
		{
			LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
			pitch = -pitch;
			LCD_ShowNum(30+48+8,220,pitch,3,16);		//��ʾ��������
		}
		
		//��ʾroll
		if(roll>=0)
		{
			LCD_ShowChar(30+48,240,' ',16,0);
			LCD_ShowNum(30+48+8,240,roll,3,16);		//��ʾ��������
		}
		else
		{
			LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
			roll = -roll;
			LCD_ShowNum(30+48+8,240,roll,3,16);		//��ʾ��������
		}
		//��ʾyaw
		if(aacz>=0)
		{
			LCD_ShowChar(30+48,260,' ',16,0);
			LCD_ShowNum(30+48+8,260,yaw,3,16);		//��ʾ��������
		}
		else
		{
			LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
			yaw = -yaw;
			LCD_ShowNum(30+48+8,260,yaw,3,16);		//��ʾ��������
		}

		//���ݴ�����  dealdate
		//delay_ms(100);
	}
}


//ִ������2���Զ����Ʋ���  -- ��ʽһ ���� ����������pwm�Ĺ�ϵ
void function_B(u8 length)
{
	int i=0;
	u16 pwm = 1000;
//	u16 T;
//	T=2*3.1415*
	
	//���ȶ�Ӧ��pwm��
	int length_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	LCD_ShowString(150,200,200,16,16,"two start");
	//��ʼ��������ʾ
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//��ö�Ӧ�Ƕȶ�Ӧ��pwm��ֵ
	pwm = length_pwm[length-30];
						
	//����������   ���ٵ���15cm
	for(i = 0;i<4;i++)
	{
		FanAB_Forward(1000);
		delay_ms(840);
		FanAB_Backward(1000);
		delay_ms(840);	
	}
	
	//30-60,Ԥ��45cm������
	for( i = 0;i<10;i++)
	{
	//����������   -- 2��v(L/g)    
		FanAB_Forward(pwm);
		delay_ms(840);
		FanAB_Backward(pwm);
		delay_ms(840);	
	}
	
	//�ٶȷ���,����ֹͣ  3
	for(i = 0;i<3;i++)
	{
		FanAB_Backward(1000);
		delay_ms(840);
		FanAB_Forward(1000);
		delay_ms(840);
	}
	
	FanAB_Backward(1000);
	delay_ms(400);
	
	//����������ʾֹͣ
	FanAB_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}
//ִ�л������������
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
			if(key == WKUP_PRES)	//������һ��˵�
			{
				LCD_Clear(WHITE);	
				MainMenu();
				TASTMenu();
				break;
			}
//			LCD_ShowNum(86,240,key,5,16);
			//�趨���߳���
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
			//��ȷ�ϼ�ִ������2
			if(key == KEYCF_PRES)
			{
				function_B(LineLength);
			}
		}
		
		LCD_ShowNum(74,200,LineLength,4,16);
	}
}	

//ִ������3���Զ����Ʋ���
//����Ҫ�涨ָ��������߶γ���
void function_C(u8 anger)
{
	int i=0;
	//�����ĸ������pwm
	u16 pwm = 1000;
	u16 ABpwm,CDpwm;
	double Anger = 0;
	double PI = 3.1415926535;
	float CosAnger,SinAnger;
	float length = 40;
	
	//x��Ƕȶ�Ӧ��pwm��
	int x_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	
	//y��Ƕȶ�Ӧ��pwm��
	int y_pwm[30]={ 1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
					    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000,
	                    1000,1000,1000,1000,1000 };
	
	
	LCD_ShowString(150,200,200,16,16,"three start");
	//��ʼ��������ʾ
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//��ö�Ӧ�Ƕȶ�Ӧ��pwm��ֵ
//	pwm = anger_pwm[length-30];
	Anger = anger*PI/180;  //��ýǶ�ֵ
	CosAnger = cos(Anger);    //
	SinAnger = sin(Anger);
//	LCD_ShowNum(86,240,anger,5,16);
	
	//��ø����pwmֵ
	ABpwm = pwm*CosAnger;
	CDpwm = pwm*SinAnger;
	
	for( i = 0;i<12;i++)     //12 * (840* 2) 12 * 16 = 20s����;
	{
	//����������   -- 2��v(L/g) 
		FanCD_Backward(1000);  
		FanAB_Backward(1000);
		
		delay_ms(900);	
		FanCD_Forward(1000);
		FanAB_Forward(1000);
		
		delay_ms(900);
		
	}
	//���ٻ���
//	FanAB_Backward(1000);
//	delay_ms(400);
//	
	//����������ʾֹͣ
	FanABCD_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}


//ִ�л�������������
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
			if(key == WKUP_PRES)	//������һ��˵�
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
			//��ȷ�ϼ�ִ������3
			if(key == KEYCF_PRES)
			{
				function_C(LineAnger);
			}
		}
		LCD_ShowNum(74,200,LineAnger*10,4,16);
		
	}
}	


////ִ������4���Զ����Ʋ���
void function_D(void)
{
	while(1)
	{
		
	}
}

//ִ�л�������������
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
			if(key == WKUP_PRES)	//������һ��˵�
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


//���Ӳ��� -- 
void function_E(u8 radius)
{
	int i=0;
	u16 pwm = 1000;
	
	//���ȶ�Ӧ��pwm��
//	int length_pwm[30]={ 1000,1000,1000,1000,1000,
//					    1000,1000,1000,1000,1000,
//					    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000,
//	                    1000,1000,1000,1000,1000 };
	
	LCD_ShowString(150,200,200,16,16,"six start");
	//��ʼ��������ʾ
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	//��ö�Ӧ�Ƕȶ�Ӧ��pwm��ֵ
//	pwm = length_pwm[length-30];
	
	for( i = 0;i<120;i++)
	{
	//����������   -- 2��v(L/g) 
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
	//����������ʾֹͣ
	FanABCD_Brk();
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
	LCD_ShowString(160,180,200,16,16,"completed");
}

//ִ�з��Ӳ���(һ��)
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
			if(key == WKUP_PRES)	//������һ��˵�
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
			//��ȷ�ϼ�ִ������3
			if(key == KEYCF_PRES)
			{
				function_E(RouldRadius);
			}
		}
		
		LCD_ShowNum(74,200,RouldRadius,4,16);	
	}
}





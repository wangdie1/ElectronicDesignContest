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


//���˵�
//int MUSE_TASK(void)
//{
//	u8 t=0;
//	LCD_Clear(WHITE);
//	Show_Str(20,30,200,24,"���˵�:",24,0);
//	Show_Str(20,60,200,24,"����1:",24,0);
//	Show_Str(20,90,200,24,"����2:",24,0);
//	Show_Str(20,120,200,24,"����3:",24,0);
//	Show_Str(20,150,200,24,"����4:",24,0);
//	Show_Str(20,180,200,24,"����5:",24,0);
//	Show_Str(20,210,200,24,"����6:",24,0);
//	Show_Str(20,240,200,24,"����7:",24,0);
//	Show_Str(20,270,200,24,"����8:",24,0);
//	
//	t++;
//	if(t==100)
//		Show_Str(10,150,230,24,"�������ѡ��",24,0);
//	if(t==200)
//	{	
//		LCD_Fill(10,150,240,150+50,WHITE);
//		t=0; 
//	}
//	delay_ms(5);
//	return 0;
//}


////����0
//// ���ȷ������ݣ�Ȼ���������
//int KEY0_TASK()
//{
//	u8 key;
//	u8 time ; //���㷢�ʹ���
//	u16 t=0;			 
//	u8 tmp_buf[33];	
//	
//	u8 key_buf[33] = "key0_pres"; //Ҫ���͵�����
//	
//	
//	LCD_Clear(WHITE);
//	Show_Str(50,50,200,24,"��ǰ����0 :",24,0);

//	NRF24L01_TX_Mode();

//	
//	//�������� key0_pres
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
//		tmp_buf[32]=0;//���������	

//		if(KEY_Scan(0)==WKUP_PRES)
//		{
//			break;
//		}
//	}
//	time = 0;
//	
//	//Ȼ��������� ��ȡһ�ΰ���������������Ϣ
//	NRF24L01_RX_Mode();		  
//	while(1)
//	{	 
//		if(t%2==0)
//		{
//			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
//			{
//				tmp_buf[32]=0;//�����ַ���������
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
//				Show_Str(50,100,200,24,"��ǰ����0 :",24,0);
//				break;
//			}
//		}
//		t++;    
//	}

//	return 0;
//	
//}



//int QJ_TASK(u16 pwm)
//pwm С�����ٶ�
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


////����������

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

////Բ���˶�
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


////����������3����

//void DLB_TASK_3(void)
//{
//	u16 enc;
//	int pwm1;
//	
//	//��ñ�������ֵ
//	enc = Encoder_Get_Counter();
//	
//	//300ms��Ƶ�ʴ�ӡ������
//	if(TB_Delay_IsElapsed() == true)  
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d\r\n",TIM3->CNT);	
//	}
//	
//	//pwm���
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

////����������4����  --ԭ����� 
//void DLB_TASK_4(void)
//{
//	int enc;
//	int pwm1;
//	
//	//���λ�û�
//	enc = Encoder1_Get_Counter();
//	if(800-enc < 400)
//		enc = enc - 800;
//	//300ms��Ƶ�ʴ�ӡ������
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d\r\n",enc);	
//	}
//	
//	//pwm���
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
//	//λ�û�
//	enc = Encoder1_Get_Counter();
//	//�ٶȻ�
//	speed = ENC1_Get_Speed();

//	//300ms��Ƶ�ʴ�ӡ������
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d    enc1:%lf\r\n",enc,speed);	
//	}
//	
//	
//	//pwm���
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
//	//λ�û�
//	enc = Encoder1_Get_Counter();
//	//�ٶȻ�
//	speed = ENC1_Get_Speed();

//	//300ms��Ƶ�ʴ�ӡ������
//	if(TB_Delay_IsElapsed() == true)
//	{
//		TB_SetDelay_Time(Uart_DELAY);
//		printf("enc:%d    enc1:%lf\r\n",enc,speed);	
//	}
//	
	
	//pwm���
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
//	u16 pwm;//pwm����ת��ֵΪ1000
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
//	for( i = 0;i<120;i++)
//	{
//	//����������   -- 2��v(L/g)    
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

//����һ�ķ�����
void function_A2(void)
{
	u8 preRoll = 0,lastRoll = 0;
	u8 prepitch = 0,preBpitch=0,lastpitch = 0;
	u8 target = 80;
	int sign=1;
	int i=0;
	float pitch,roll,yaw; 		//ŷ����
	LCD_ShowString(150,200,200,16,16,"start");
	BEEP = 1;
	delay_ms(1000);
	BEEP = 0;
    
	//������
	for( i = 0;i<3;i++)
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
			
			//roll��ֵ����pid��,����roll��ֵ������0  y�ᱣ��
			
			
			//x�����
			
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
		FanAB_Forward(ABpwm);
		FanCD_Forward(CDpwm);
		delay_ms(840);
		FanAB_Backward(ABpwm);
		FanCD_Forward(CDpwm);
		delay_ms(840);	
	}
	//���ٻ���
	FanAB_Backward(1000);
	delay_ms(400);
	
	//����������ʾֹͣ
	FanAB_Brk();
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





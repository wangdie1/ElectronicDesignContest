#include "mytask.h"
#include "init.h"
#include "menu.h"


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

//ִ�л�����������һ
void Perform_BaseTask1(void)
{
	u8 key;
	LCD_ShowNum(86,240,111,5,16);
	while(1)
	{
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
			LCD_ShowNum(86,240,key,5,16);
		}
		
	}
}

//ִ�л������������
void Perform_BaseTask2(void)
{
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
			LCD_ShowNum(86,240,key,5,16);
		}
		
	}
}	

//ִ�л�������������
void Perform_BaseTask3(void)
{
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
			LCD_ShowNum(86,240,key,5,16);
		}
		
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
			LCD_ShowNum(86,240,key,5,16);
		}
		
	}
}	

//ִ�з��Ӳ���(һ��)
void Perform_ExertTask1(void)
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
			LCD_ShowNum(86,240,key,5,16);
		}
		
	}
}





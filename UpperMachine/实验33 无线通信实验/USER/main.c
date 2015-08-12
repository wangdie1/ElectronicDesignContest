#include "init.h"
#include "ili9320.h"
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


//����pid��ֵ,��ȷ��С�����2λ



int main(void)
 {	 
//	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
//	u8 key;
	 
	u8 key;
	u8 t=0;	
	u8 stri=0;
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�	
	ili9320_Initializtion();//Һ������ʼ��
	Init();                    //���ֺ�����ʼ��
	
	 //�����ʼ��
	MainMenu();                 //���˵���
	StateMenu();
	while(mpu_dmp_init())       //��ʼ��mpu6050
 	{
		LCD_ShowString(20,160,200,16,16,"MPU6050 Error");
		delay_ms(200);
	}  
	POINT_COLOR=RED;
	LCD_ShowString(20,180,200,16,16,"MPU6050    OK");
//	BEEP = 1;
//	LCD_ShowString(30,200,200,16,16,"KEY0:UPLOAD ON/OFF");
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
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
			//ˢ��lcdҳ��
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
					
					else if(key == WKUP_PRES)  //�˳��ò����
					{
						delay_ms(10);
						key = 0;
						break;
					}
				}
			}

		}
//		delay_ms(100);
		
		

		
//����ң���ʽ�
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
//					if(stri == 1)  //ִ������1
//					{
//						LCD_Clear(WHITE);	
//						MainMenu();
//						TAST1_Menu();
//						Perform_Task1();
//					}
//					else if(stri == 2)//ִ������2
//					{
//						LCD_Clear(WHITE);	
//						MainMenu();
//						TAST2_Menu();
//						Perform_Task2();
//					}
//					else if(stri == 3 )//ִ������3
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
//	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
//	u8 key;
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�	
//	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(500000);	 	//���ڳ�ʼ��Ϊ500000
//	delay_init();	//��ʱ��ʼ�� 
//	usmart_dev.init(72);		//��ʼ��USMART
//	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
////	LCD_Init();			   		//��ʼ��LCD
//	ili9320_Initializtion();	 
//	MPU_Init();					//��ʼ��MPU6050
// 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
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
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
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
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0) //����dma����������
//		{
//			//mpu6050�Ĳ���Ƶ��
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			
//			//�Ѵ�����ֵ���͸�������λ��
//			if(report)
//				mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
//			if(report)
//				usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
//			
//			
//			           if((t%10)==0)
//			{ 
//				//�¶�ֵ
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//��ʾС������ 
//				printf("%d\r\n",temp);
//				//ŷ���� pitch
//				temp=pitch*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,220,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//��ʾС������ 
//				printf("%d\r\n",temp);
//				//ŷ���� roll
//				temp=roll*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//��ʾС������ 
//				printf("%d\r\n",temp);
//				//ŷ���� yaw
//				temp=yaw*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//��ʾС������  
//				printf("%d\r\n",temp);
//				t=0;
//				LED0=!LED0;//LED��˸
//			}
//		}
//		t++; 
//	} 	
//}
// 

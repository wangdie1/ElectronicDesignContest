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
	u8 key;
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�	
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
					if(key == KEYA_PRES)   //��������1
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST1_Menu();
						Perform_BaseTask1();
					}
					else if(key == KEYB_PRES) //��������2
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST2_Menu();
						Perform_BaseTask2();
					}
					else if(key == KEYC_PRES) //��������3
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST3_Menu();
						Perform_BaseTask3();
					}
					else if(key == KEYD_PRES) //��������4
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST4_Menu();
						Perform_BaseTask4();
					}
					else if(key == KEYE_PRES) //��������1
					{
						LCD_Clear(WHITE);	
						MainMenu();
						TAST5_Menu();
						Perform_ExertTask1();
					}
					
					else if(key == WKUP_PRES)  //��ʾ����
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
//	}
//}
		

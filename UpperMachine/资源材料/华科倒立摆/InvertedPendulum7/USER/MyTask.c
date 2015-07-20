#include "mytask.h"
// #include "math.h"


void INIT_Task()
{
	short temp;
	if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
				clear_screen();
				display_GB2312_string(1,1,"��ת������ϵͳ");  
				display_GB2312_string(3,1,"��ص�ԭ��..."); 
				display_GB2312_string(5,1,"");    
				display_GB2312_string(7,1,"Play������˵�"); 
		}
		if(Remote_Rdy)
				{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_PLAY://��ʼ�����
								Controller_Init(); //PID������ʼ��
								ENC_Init();					//��������ʼ��
								ENC1_Init();        //
								State=MENU;//����˵�״̬
								break;
							}
				}
}
void MENU_Task()
{
		if(TB_DisplayDelay_IsElapsed()==TRUE)
			{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();
            display_GB2312_string(1,1,"1,�����˶�"); 
            display_GB2312_string(3,1,"2�̶�λ������");    
            display_GB2312_string(5,1,"3,�´�����"); 
						display_GB2312_string(7,1,"4�����˶�5����");  
				}
					if(Remote_Rdy)
				{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_KEY1://1�����˶�����
								State = RECIPROCATE_INPUT;
								break;
							case IR_KEY2://��������
								clear_screen();
								display_GB2312_string(1,1,"2�̶�λ������");    
								display_GB2312_string(1,1,"��ת����165��"); 
								display_GB2312_string(5,1,"3,Ȼ������"); 
								display_GB2312_string(7,1,"��ע�ⰲȫ");  
								State = FREE_LQR;
								break;
							case IR_KEY3:
								clear_screen();	
								display_GB2312_string(1,1,"3,�´�����");  
								display_GB2312_string(3,1,""); 
								display_GB2312_string(5,1,"");    
								display_GB2312_string(7,1,""); 
// // 								MotorA_Backward(1000);
// // 								delay_ms(10);
								MotorA_Forward(200);//��ʹ�Ŷ�����������
								delay_ms(4);
								MotorA_Backward(1000);
								delay_ms(4);
// 								MotorA_Brk();
								State = LQR_CONTROL;//
								break;
							case IR_KEY4:
								clear_screen();	
								display_GB2312_string(1,1,"4,�����˶�");  
								display_GB2312_string(3,1,""); 
								display_GB2312_string(5,1,"");    
								display_GB2312_string(7,1,""); 
// 								MotorA_Backward(500);
// 								delay_ms(20);
// 								MotorA_Forward(500);//��ʹ�Ŷ�����������
// 								delay_ms(5);
// 								MotorA_Brk();
								State = LQR_CIRCULAR_INPUT;//
								break;
							case IR_KEY5:
								State = OTHER;
								break;
							case IR_KEY6:
								State =LQR_TEST;
							break;
							case IR_PREV://�ص���ʼ��״̬
								State=INIT;
							break;
							case IR_KEY7:
								State =TEST_MOTOR;
							break;
							default:
								break;
						}
				}
}

/***
�����˶�����ڶ�����״̬��PLAY�����
****/
void RECIPROCATE_INPUT_Task(void)
{
	if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();	
            display_GB2312_string(1,1,"1,�����˶�"); 
            display_GB2312_string(3,1,"������Ƕ�");   
						sprintf(str,"Ŀ�꣺%d",AimAngle);
            display_GB2312_string(5,1,str); 
						display_GB2312_string(7,1,"PLAY��ȷ��");  
		}
		if(Remote_Rdy)
				{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_VOL_UP:
								AimAngle += 10;
// 								if(AimAngle > 100)
// 								{
// 									AimAngle =10;
// 								}
// 								else if(AimAngle < 10)
// 								{
// 									AimAngle = 90;
// 								}
								break;
							case IR_VOL_DOWN:
								AimAngle -=10;
// 								if(AimAngle > 100)
// 								{
// 									AimAngle =10;
// 								}
// 								else if(AimAngle < 10)
// 								{
// 									AimAngle = 90;
// 								}
								break;
							case IR_PREV:
								State = MENU;//prev�����ص��˵�
								break;
							case IR_PLAY://PLAY��ȷ�ϣ�����ִ��״̬
								clear_screen();	
								display_GB2312_string(1,1,"1,�����˶�"); 
								display_GB2312_string(3,1,"������Ƕ�");   
								sprintf(str,"Ŀ�꣺%d",AimAngle);
								display_GB2312_string(5,1,str); 
								display_GB2312_string(7,1,"ִ����");  
								MotorA_Forward(200);//��ʹ�Ŷ�����������
								delay_ms(6);
								MotorA_Backward(200);
								delay_ms(6);
								MotorA_Brk();
								State = RECIPROCATE;
							break;
						}
				}
}
/****
�����˶�״̬����һ�������˶�������Ƕ�
****/
void RECIPROCATE_Task(void)
{
	double temp;
		
	if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//��������1ms
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					alpha = ENC1_Get_AnglularPosition()+180;
				/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(alpha)>180)
					{
						  if(alpha>180)
							{
								  alpha=alpha-360;
							}
							else
								  alpha=alpha+360;
					}
					v_alpha = 	0.6*ENC1_Calc_Average_Speed();//��ÿ��
					theta 	= 	ENC_Get_AnglularPosition();
					/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(theta)>180)
					{
						  if(theta>180)
							{
								  theta=theta-360;
							}
							else
								  theta=theta+360;
					}
				v_theta =  0.6*ENC_Calc_Average_Speed();//��ÿ��
				alpha_pi = alpha *PI /180;
				v_alpha_pi = v_alpha * PI/180;
				E = 3*v_alpha_pi*v_alpha_pi+490*(cos(alpha_pi)-1);//�Ŵ���490
				temp = ( 180-AimAngle ) *PI /180;
				E0 = 490*(cos(temp)-1);
				if(v_alpha_pi*cos(alpha_pi)>0)
				{
					MotorA.PWM = -(E-E0)*10;//��������Ƕȴ�С���ı䱶��
				}
				else if(v_alpha_pi*cos(alpha_pi)<0)
				{
						MotorA.PWM =(E-E0)*10;
				}
				else if(v_alpha_pi*cos(alpha_pi)==0)
				{
					MotorA.PWM = 0;
				}
				MotorA_PWM_Update(MotorA.PWM);	
			}
			if(Remote_Rdy)
			{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_PREV:
								MotorA_Brk();
								State = RECIPROCATE_INPUT;//PREV�����ص�ԭ��״̬
								break;
							case IR_PLAY://�����ر�
								MotorA_Brk();
								State = INIT ;		
								break;
							}
			}
}
/*****
���ڸ��ٶȣ����ٶȴ���ĳ��ֵ�ǣ�����LQR���ƻ��ڡ�
��һ��״̬���˵�ѡ����һ���ջ�����
*****/
void FREE_LQR_Task(void)
{

		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//��������1ms
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					alpha = ENC1_Get_AnglularPosition()+180;
			    if(alpha>180)
							{
								  alpha=alpha-360;
							}
							else if(alpha <180)
							{
								  alpha=alpha+360;
							}
				  v_alpha = 	0.6*ENC1_Calc_Rot_Speed();//��ÿ��
					if((abs(alpha) > 17)&(abs(v_alpha)>100))//�ٶȽ��ޡ�����ĳ���ٶȣ�˵�����ɿ���
					{
						State = LQR_CONTROL;//���뵹��
					}
		}
			if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();	
						display_GB2312_string(1,1,"2�̶�λ������");    
						display_GB2312_string(3,1,"��ת����165��"); 
						sprintf(str,"��ǰ��%f",alpha);
						display_GB2312_string(5,1,str); 
						display_GB2312_string(7,1,"����ע�ⰲȫ"); 
		}
		if(Remote_Rdy)
			{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_PREV:
								MotorA_Brk();
								State = MENU;//PREV�����ص��˵�״̬
								break;
							case IR_PLAY://�����ر�
								MotorA_Brk();
								State = INIT ;		
								break;
							}
			}
}
/****
���񲢽���LQR�ջ�����
****/
void LQR_CONTROL_Task(void)
{
	/***1ms*/
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//��������1ms
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					alpha = ENC1_Get_AnglularPosition()+180;
				/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(alpha)>180)
					{
						  if(alpha>180)
							{
								  alpha=alpha-360;
							}
							else
								  alpha=alpha+360;
					}
// 					v_alpha = 	0.6*ENC1_Calc_Rot_Speed();//��ÿ��
					
					//ƽ���ٶ�
					v_alpha=0.6*ENC1_Calc_Average_Speed();
					//��λ��
					theta 	= 	ENC_Get_AnglularPosition();
					/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(theta)>180)
					{
						  if(theta>180)
							{
								  theta=theta-360;
							}
							else
								  theta=theta+360;
					}
					
					v_theta =  0.6*ENC_Calc_Average_Speed();//��ÿ��
// 					v_theta =  0.6*ENC_Calc_Rot_Speed();//��ÿ��
			if((abs(alpha)<30)&(abs(v_alpha)<2000))//����ά���ȶ�״̬������
			{
				//ά���ȶ�
// 	     		MotorA.PWM = -(-3.8730 * theta +72.3887 * alpha    - 3.8824 * v_theta + 6.8216 *v_alpha)/5;//��һ�ò���
// 				MotorA.PWM = -(-3.8730 * theta +81.2340 * (alpha)  - 4.6512 * v_theta + 7.6743 *v_alpha)/6.5;
// 				MotorA.PWM = -(-3.8730 * theta +79.5930 * (alpha)  - 3.9095 * v_theta + 6.8569 *v_alpha)/6.5;		
				MotorA.PWM = -(K1 * theta +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;							
				MotorA_PWM_Update(MotorA.PWM);
			}
			else//������ƣ��ص�ԭ��
			{
				alpha_pi = alpha *PI /180;
				v_alpha_pi = v_alpha * PI/180;
// 				E = 3*v_alpha_pi*v_alpha_pi+490*(cos(alpha_pi)-1);//�Ŵ���490
				E = 3*v_alpha_pi*v_alpha_pi+490*(cos(alpha_pi)-1);//�Ŵ���490
				if(v_alpha_pi*cos(alpha_pi)>0)
				{
					MotorA.PWM = -E*6;
				}
				else if(v_alpha_pi*cos(alpha_pi)<0)
				{
						MotorA.PWM =E*6;
				}
				else if(v_alpha_pi*cos(alpha_pi)==0)
				{
					MotorA.PWM = 0;
				}
				MotorA_PWM_Update(MotorA.PWM);	
			}
		}
		/***ң��***/
		if(Remote_Rdy)
			{
				Remote_Rdy=0;
				ir_key=Remote_Process();
				switch(ir_key)
				{
					case IR_PLAY:
						MotorA_Brk();
						State = INIT ;		
						break;
					case IR_PREV://���ص��˵�״̬
						MotorA_Brk();
						State = MENU;
						break;
					case IR_NEXT:
						AimAngle =180;
						State = LQR_CIRCULAR;
						break;
				}
			}
			if(KeyFlag ==1)
			{
				KeyFlag =0;
				IsCycleOK =0;
				ThetaDelta =0;
				DeltaNum =0;
				State = LQR_CIRCULAR;
					clear_screen();	
						display_GB2312_string(1,1,"����Բ���˶�");    
						display_GB2312_string(3,1,""); 
			
				LED0_Toggle();
			}
}
void LQR_CIRCULAT_INPUT_Task(void)
{
		if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();	
						display_GB2312_string(1,1,"����Բ���˶�");    
						display_GB2312_string(3,1,"����ת�ĽǶ�"); 
						sprintf(str,"��ǰ��%f",AimTheta);
						display_GB2312_string(5,1,str); 
						display_GB2312_string(7,1,"PLAY�����"); 
		}
			if(Remote_Rdy)
			{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_VOL_UP://��10��
								AimTheta +=10;	
								break;
							case IR_VOL_DOWN://��10��
								AimTheta -=10;
							break;
							case IR_CH_UP:
								AimTheta += 360;//��1Ȧ
							break;
							case IR_CH_DOWN:
								AimTheta -= 360;
							break;
							case IR_PLAY:
			        	MotorA_Forward(200);//��ʹ�Ŷ�����������
								delay_ms(4);
								MotorA_Backward(1000);
								delay_ms(4);
								IsCycleOK = 0;
								State = LQR_CIRCULAR;//������ɣ����뵹���˶�״̬
								break;
							case IR_PREV://���ص��˵�״̬
								MotorA_Brk();
								State = MENU;
							break;
							}
			}
}
/***
���ֵ���״̬����Բ���˶�
***/
void LQR_CIRCULAR_Task(void)
{
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//��������1ms
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					LED0_Toggle();
					alpha = ENC1_Get_AnglularPosition()+180;
					
			
				/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(alpha)>180)
					{
						  if(alpha>180)
							{
								  alpha=alpha-360;
							}
							else
								  alpha=alpha+360;
						}
						v_alpha	= 0.6*ENC1_Calc_Average_Speed();
						
						theta 	= 	ENC_Get_AnglularPosition();	
// 						DeltaNum++;
// 					if(DeltaNum<3600)
// 					{
// 						theta+=10;
// 					}
							/****�Ƕ��޶���-180��180��Χ֮��*/
					while(abs(theta)>180)
					{
						
						  if(theta>180)
							{
// 								 flag2=1;
								  theta=theta-360;
							}
							else
								  theta=theta+360;
					}
						v_theta =  0.6*ENC_Calc_Average_Speed();//��ÿ���
			if((abs(alpha)<30)&(abs(v_alpha)<2000))//����ά���ȶ�״̬������
			{
// 				if(DeltaNum<360)
// 				{
				if(abs(theta)>178)
				{
					MotorA.PWM =-(K1 *theta  +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;		
				}
				else
				{
					DeltaNum+=0.01;
					MotorA.PWM =-DeltaNum*18 -(K1 *theta  +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;	
				}					
// 				}
// 				else
// 				{
// 						MotorA.PWM = -(K1 *theta  +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;							
// 				}
// 					MotorA.PWM = -(K1 *theta  +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;							
// 				 MotorA.PWM = ThetaDelta-(K1 * theta +K2 * (alpha)  +K3 * v_theta + K4 *v_alpha)/G;							
				MotorA_PWM_Update(MotorA.PWM);
			}
			else//������ƣ��ص�ԭ��
			{
				alpha_pi = alpha *PI /180;
				v_alpha_pi = v_alpha * PI/180;
				E = 3*v_alpha_pi*v_alpha_pi+490*(cos(alpha_pi)-1);//�Ŵ���490
				if(v_alpha_pi*cos(alpha_pi)>0)
				{
					MotorA.PWM = -E*6;
				}
				else if(v_alpha_pi*cos(alpha_pi)<0)
				{
						MotorA.PWM =E*6;
				}
				else if(v_alpha_pi*cos(alpha_pi)==0)
				{
					MotorA.PWM = 0;
				}
				MotorA_PWM_Update(MotorA.PWM);	
			}
		}
		if(Remote_Rdy)
			{
						Remote_Rdy=0;
						ir_key=Remote_Process();
						switch(ir_key)
						{
							case IR_PLAY:
								MotorA_Brk();
								State = INIT ;		
								break;
							case IR_PREV://���ص��˵�״̬
								MotorA_Brk();
								State = MENU;
							break;
							case IR_NEXT:
// 								ThetaDelta=0;
								DeltaNum=0;
// 								Diec =-Diec;
								IsCycleOK=0;
								break;
							}
			}
			if(KeyFlag ==1)
			{
				KeyFlag =0;
				IsCycleOK =0;
				ThetaDelta =0;
				DeltaNum =0;
				LED0_Toggle();
// 				State = LQR_CIRCULAR;
			}
}

void LQR_TEST_Task(void)
{
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//�ٶȵ���
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
// 					alpha 	= 	100*(s32)(ENC1_Get_AnglularPosition()+180);//�ڱ�
					alpha = ENC1_Get_AnglularPosition()+180;
					v_alpha = 	06*ENC1_Calc_Rot_Speed();//��ÿ��
// 					theta 	= 	100*(s32)ENC_Get_AnglularPosition()%36000;//����
					theta 	= 	ENC_Get_AnglularPosition();
					v_theta =  0.6*ENC_Calc_Rot_Speed();//��ÿ��
		}
	 		if(TB_DisplayDelay_IsElapsed()==TRUE)
			{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();
						sprintf(str,"alpha:%f",alpha);
						display_GB2312_string(5,1,str);
						sprintf(str,"Va:%f",v_alpha);
						display_GB2312_string(7,1,str);
						sprintf(str,"theta:%f",theta);
						display_GB2312_string(1,1,str);
						sprintf(str,"Vtheat:%f",v_theta);
						display_GB2312_string(3,1,str);
						LED1_Toggle();
			}
	
}
void INPUT_Task()
{
}
void POSITION_INPUT_Task()
{			
}
void SPEED_CONTROL_Task()
{
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//�ٶȵ���
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
// 					MotorA.SpeedExpected = 1200*sin(BufferNum * 14*PI/ BUFFER_SIZE );
					MotorA.SpeedTest = ENC_Calc_Rot_Speed() ;//ת600
					if(BufferNum < BUFFER_SIZE)
					{
						SpeedBuffer[BufferNum] = MotorA.SpeedTest;
						BufferNum++;
					}
// 					MotorA.PWM = 5*(MotorA.SpeedExpected - MotorA.SpeedTest);
 					MotorA.PWM = PI_Controller(MotorA.SpeedExpected - MotorA.SpeedTest,&SpeedPID);
					MotorA_PWM_Update(MotorA.PWM);
					
			
// 					sprintf(str,"%d\t%d\n",MotorA.PositionTest,	MotorA.PWM);
// 					printf(str);
		    	LED2_Toggle();
					
		}
// 			if(TB_DisplayDelay_IsElapsed()==TRUE)
// 	{
// 								TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// 								clear_screen();
// 								sprintf(str,"Pa:%d",MotorA.PositionTest);
// 								display_GB2312_string(1,1,str);
// 								sprintf(str,"Va:%f",MotorA.SpeedTest);
// 								display_GB2312_string(3,1,str);
// 								sprintf(str,"PWMa:%d",MotorA.PWM);
// 								display_GB2312_string(7,1,str);
// 								sprintf(str,"VaAim:%f",MotorA.SpeedExpected);
// 								display_GB2312_string(5,1,str);
// // 								LED1_Toggle();
// 			}
			if(Remote_Rdy)//���⴦��
			{
				Remote_Rdy=0;
				ir_key=Remote_Process();
				switch(ir_key)
				{
					case IR_VOL_UP:
					MotorA.SpeedExpected += 10;
					break;
					case IR_VOL_DOWN:
					MotorA.SpeedExpected -= 10;
					break;
					case IR_PLAY:
						MotorA_Brk();
						MotorB_Brk();
						State=IDLE;
					break;
				}
			}
}
void POSITION_CONTROL_Task()
{
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//�ٶȵ���
		{
					TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					MotorA.SpeedTest = ENC_Calc_Rot_Speed() ;//ת600
 					MotorA.PWM = PI_Controller(MotorA.SpeedExpected - MotorA.SpeedTest,&SpeedPID);
					MotorA_PWM_Update(MotorA.PWM);
		    	LED2_Toggle();
		}
		if(TB_PositionPIDDelay_IsElapsed()==TRUE)
		{
				TB_SetPositionPIDDelay_Time(POSITION_PID_DELAY);
			MotorA.PositionExpected = 30*sin(BufferNum *30*PI/ BUFFER_SIZE );
// 				MotorA.PositionExpected = (BufferNum>100)?3600:0;
				if(BufferNum < BUFFER_SIZE)
						{
							SpeedBuffer[BufferNum] = MotorA.SpeedTest;
							PositionBuffer[BufferNum] = MotorA.PositionTest;
							BufferNum++;
						}	
				MotorA.PositionTest = ENC_Get_AnglularPosition();	
				MotorA.SpeedExpected = PD_Controller(MotorA.PositionExpected - MotorA.PositionTest,&PositionPID)
												+ FF_Controller(MotorA.PositionExpected,&PositionFF);
		}
// 		if(TB_DisplayDelay_IsElapsed()==TRUE)
// 			{
// 								TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// 								clear_screen();
// 								sprintf(str,"Pa:%d",MotorA.PositionTest);
// 								display_GB2312_string(5,1,str);
// 								sprintf(str,"Va:%f",MotorA.SpeedTest);
// 								display_GB2312_string(7,1,str);
// 								sprintf(str,"Pb:%d",MotorB.PositionTest);
// 								display_GB2312_string(1,1,str);
// 								sprintf(str,"Vb:%f",MotorB.SpeedTest);
// 								display_GB2312_string(3,1,str);
// 			}
// 			if ( IsKeyPressed )		//����м�����
// 			{
// 					//����жϱ�־
// 					IsKeyPressed = 0;
// 					switch(zlg_key)
// 					{
// 						case KEY1:
// 							MotorA.PositionExpected +=360;
// 		
// 						break;
// 						case KEY2:
// 							MotorA_Brk();
// 							State=IDLE;
// 						break;
// 						case KEY3:
// 							MotorB.PositionExpected +=360;
// 						break;
// 						case KEY4:
// 							MotorB_Brk();
// 						State=IDLE;
// 						break;
// 						case KEY13:
// 							MotorA_Brk();
// 						MotorB_Brk();
// 						State=IDLE;
// 						break;
// 					}
// 		}
	if(Remote_Rdy)//���⴦��
			{
				Remote_Rdy=0;
				ir_key=Remote_Process();
				switch(ir_key)
				{
					case IR_PLAY:
						MotorA_Brk();
						MotorB_Brk();
						State=IDLE;
					break;
				}
			}
}

void TEST_KEY_AND_IR_Task()
{
	
	if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
			TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
			clear_screen();
			display_GB2312_string(5,1,"������������");
			display_GB2312_string(7,1,str);
			LED1_Toggle();
		}
	if( IsKeyPressed )		//����м�����
		{
				IsKeyPressed = 0;	//����жϱ�־
				sprintf(str,"%d",zlg_key);
				delay_ms(10);
		}
	if(Remote_Rdy)
		{
			Remote_Rdy=0;
			ir_key=Remote_Process();
			sprintf(str,"%d",ir_key);
			printf(str);
		}
}

void TEST_MOTOR_Task()
{
		u32 pwm_duty=100;
	
		if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//�ٶȵ���
				{
						TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
					
						MotorA.SpeedTest=ENC_Calc_Rot_Speed() ;//ת600	
// 						MotorB.SpeedTest=ENC1_Calc_Rot_Speed() ;//ת600
						MotorB.SpeedTest=ENC1_Calc_Average_Speed();
				}
		if(TB_PositionPIDDelay_IsElapsed()==TRUE)
				{
					TB_SetPositionPIDDelay_Time(POSITION_PID_DELAY);
					MotorA.PositionTest = ENC_Get_AnglularPosition();
					MotorB.PositionTest = ENC1_Get_AnglularPosition();
				}
		if(TB_DisplayDelay_IsElapsed()==TRUE)
			{
						TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
						clear_screen();
						sprintf(str,"Pa:%f",MotorA.PositionTest);
						display_GB2312_string(5,1,str);
						sprintf(str,"Va:%f",MotorA.SpeedTest);
						display_GB2312_string(7,1,str);
						sprintf(str,"Pb:%f",MotorB.PositionTest);
						display_GB2312_string(1,1,str);
						sprintf(str,"Vb:%f",MotorB.SpeedTest);
						display_GB2312_string(3,1,str);
						LED1_Toggle();
			}
			if( IsKeyPressed )		//����м�����
			{
					IsKeyPressed = 0;	//����жϱ�־
					switch(zlg_key)
					{
						case KEY1:
							MotorA_Forward(200);
						break;
						case KEY2:
							MotorB_Forward(200);
						break;
						case KEY4:
							MotorA_Backward(200);
						break;
						case KEY5:
							MotorB_Backward(200);
						break;
						case KEY13:
							MotorA_Brk();
							MotorB_Brk();
						break;
					}
			}
			if(Remote_Rdy)
			{
					Remote_Rdy=0;
					ir_key=Remote_Process();
					switch(ir_key)
					{
						case IR_KEY1:
							MotorA_Forward(pwm_duty);
							MotorB_Forward(pwm_duty);
						break;
						case IR_KEY2:
							MotorA_Backward(pwm_duty);
							MotorB_Backward(pwm_duty);
							break;
						case IR_VOL_UP:
							pwm_duty+=100;
							MotorA_Forward(pwm_duty);
						break;
						case IR_VOL_DOWN:
							pwm_duty-=100;
							MotorA_Forward(pwm_duty);
						break;
						case IR_PLAY:
							MotorA_Brk();
							MotorB_Brk();
						break;
					}
				}
}

void TEST_LED_Task()
{
		if(TB_Delay_IsElapsed()==TRUE)
		{
			TB_SetDelay_Time(LED_TEST_DELAY);
			LED0_Toggle();
			LED1_Toggle();
		}
}
void TEST_LCD_Task()
{
	if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
				clear_screen();
		  	display_photo(Photo0);
			
		}
}
void TEST_ADC_Task()
{
		if( TB_ADC_Delay_IsElapsed()==true)
		{
				TB_SetADC_Time(ADC_DELAY);
				LED2_Toggle();
		}
}

void TEST_DS18B20_Task()
{
	short temp;
	if(TB_DisplayDelay_IsElapsed()==TRUE)
		{
				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
				clear_screen();
				temp=DS18B20_Get_Temp();
			if(temp<0)
			{
				temp=-temp;
				sprintf(str,"T:-%3.2f .C",(float)temp/10);
//				sprintf(str,"T:-%d%d .C",temp/10,temp%10);
			}
			else
			{
			  sprintf(str,"T:%3.2f .C",(float)temp/10);
//				sprintf(str,"T:%d%d .C",temp/10,temp%10);
			}
			display_string_5x7(1,1,"TEST_DS18B20");
			display_string_5x7(2,2,str);
		}
}

void TEST_SPEED_Task(void)
{
	if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//�ٶȵ���
	{
		TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
		MotorA.SpeedTest=ENC_Calc_Rot_Speed() ;//ת600	
		if(BufferNum < BUFFER_SIZE)
		{
			SpeedBuffer[BufferNum] = MotorA.SpeedTest;
			BufferNum++;
		}
	}
	if(Remote_Rdy)//���⴦��
	{
		Remote_Rdy=0;
		ir_key=Remote_Process();
		switch(ir_key)
		{
			case IR_EQ:
				for(BufferNum=0;BufferNum < BUFFER_SIZE;BufferNum++)
				{
					sprintf(str,"%d\n",SpeedBuffer[BufferNum]);
					printf(str);
				}
				break;
			}
		}
}

// /* ���ʲ���ģʽ */
// void POWER_INC_Task()
// {

// 	short temp;
// 	if(TB_DisplayDelay_IsElapsed()==TRUE)
// 		{
// 				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// 				clear_screen();
// 				temp=DS18B20_Get_Temp();
// 				if(temp<0)
// 				{
// 					temp=-temp;
// 					sprintf(str,"�¶�:-%3.2f .C",(float)temp/10);
// 				}
// 				else
// 				{
// 					sprintf(str,"�¶�:%3.2f 'C",(float)temp/10);
// 				}
// 				display_GB2312_string(1,1,"һ�����ʲ���");  
// 			
// 				display_GB2312_string(3,1,str);    
// 				sprintf(str,"����:%3.1f",pwm_duty*0.2);
// 				display_GB2312_string(5,1,str); 
// 				display_GB2312_string(7,1,"��Դ ���� ��ΰ"); 
// 		}
// 	if(Remote_Rdy)
// 		{
// 				Remote_Rdy=0;
// 				ir_key=Remote_Process();
// 				switch(ir_key)
// 				{
// 					case IR_CH_UP:
// 							pwm_duty+=10;//��������
// 						TIM1_PWM_Update(pwm_duty);
// 					break;
// 					case IR_CH_DOWN:
// 						pwm_duty-=10;//��������
// 						TIM1_PWM_Update(pwm_duty);
// 						break;
// 					case IR_KEY1:
// 						pwm_duty+=0.1;
// 						TIM1_PWM_Update(pwm_duty);
// 						break;
// 					case IR_KEY2:
// 							pwm_duty-=0.1;
// 						TIM1_PWM_Update(pwm_duty);
// 						break;
// 					case IR_VOL_UP:
// 						pwm_duty+=0.5;//��������
// 						if(pwm_duty>100)
// 							pwm_duty=100;
// 						else if(pwm_duty<0)
// 							pwm_duty=0;
// 						TIM1_PWM_Update(pwm_duty);
// 					break;
// 					case IR_VOL_DOWN://���ʼ�С
// 						pwm_duty-=0.5;
// 						if(pwm_duty>100)
// 							pwm_duty=100;
// 						else if(pwm_duty<0)
// 							pwm_duty=0;
// 						TIM1_PWM_Update(pwm_duty);
// 					break;
// 					case IR_PLAY://ֹͣ����
// 							pwm_duty=0.5;
// 					break;
// 					case IR_PREV:
// 						pwm_duty=0;
// 						TIM1_PWM_Update(0);
// 						State=MENU;
// 						break;
// 				}
// 			
// 		}
// }
// /* �¶ȿ���ģʽ */
// void TEMPERATURE_CONTROL_Task()
// {
// 	short TemperatureTest;
// 	if(TB_DisplayDelay_IsElapsed()==TRUE)
// 		{
// 				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// 				TemperatureTest=DS18B20_Get_Temp();
// 				pwm_duty=PID_Controller((TemperatureAim-TemperatureTest),&TemperaturePID);
// 				TIM1_PWM_Update(pwm_duty);//�����
// 		}
// }
// void TEMPERATURE_CONTROL_INPUT_Task()
// {
// 	short temp;
// 	if(TB_DisplayDelay_IsElapsed()==TRUE)
// 		{
// 				TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// 				clear_screen();
// 				temp=DS18B20_Get_Temp();
// 				TemperatureTest=(float)temp/10;
// 			if(IsInputOK)
// 			{
// 				
// // 				pwm_duty=(TemperatureAim-TemperatureTest)*TemperaturePID.Kp;
// 				pwm_duty=PID_Controller(TemperatureAim-TemperatureTest,&TemperaturePID);
// 				TIM1_PWM_Update(pwm_duty);
// 				sprintf(str,"%f\n",TemperatureTest);
// 				printf(str);
// 				LED0_Toggle();
// 			}
// 				if(temp<0)
// 				{
// 					temp=-temp;
// 					sprintf(str,"�¶�:-%3.2f .C",TemperatureTest);
// 				}
// 				else
// 				{
// 					sprintf(str,"�¶�:%3.2f 'C",TemperatureTest);
// 				}
// 				display_GB2312_string(1,1,"�����¶ȿ���");  
// 				display_GB2312_string(3,1,str);    
// 				sprintf(str,"Ŀ��:%3.1fD:%2.1f",TemperatureAimTemp,pwm_duty);
// 				display_GB2312_string(5,1,str); 
// 				display_GB2312_string(7,1,"��Դ ���� ��ΰ"); 
// 		}
// 		if(Remote_Rdy)
// 		{
// 				Remote_Rdy=0;
// 				ir_key=Remote_Process();
// 				switch(ir_key)
// 				{
// 					case IR_CH_UP:
// 							TemperatureAimTemp+=10;//�¶�����
// // 							IsInputOK=0;
// 					break;
// 					case IR_CH_DOWN:
// 							TemperatureAimTemp-=10;//�¶ȼ�С
// // 							IsInputOK=0;
// 						break;
// 					case IR_VOL_UP:
// 						TemperatureAimTemp+=1;//�¶�����
// // 						IsInputOK=0;
// 					break;
// 					case IR_VOL_DOWN:
// 						TemperatureAimTemp-=1;//�¶ȼ�С
// // 						IsInputOK=0;
// 					break;
// 					case IR_PLAY://��ʼ����
// 						if(IsInputOK)
// 						{
// 							IsInputOK=0;
// 						}
// 						else
// 						{
// 							IsInputOK=1;
// 							TemperatureAim=TemperatureAimTemp;
// 							if(TemperatureAim>80)
// 							{
// 								TemperaturePID.Kp=55;
// 								TemperaturePID.Ki=0.4;		
// 							}
// 							else if(TemperatureAim>70)
// 							{
// 								TemperaturePID.Kp=25;
// 								TemperaturePID.Ki=0.3;
// 							}
// 							else if(TemperatureAim>60)
// 							{
// 								TemperaturePID.Kp=18;
// 								TemperaturePID.Ki=0.3;
// 							}
// 							else
// 							{
// 								TemperaturePID.Kp=11;
// 								TemperaturePID.Ki=0.2;
// 							}
// 						}
// 					break;
// 					case IR_PREV:
// 						pwm_duty=0;
// 						TIM1_PWM_Update(0);
// 						State=MENU;
// 						break;
// 				}
// 			
// 		}
// }





















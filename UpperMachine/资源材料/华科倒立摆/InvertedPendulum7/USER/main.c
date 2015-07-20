
#include "driver.h"
#include "globals.h"

#define ERROR_BOND 8
#define ARRIVE_NUM_MAX 10
#define P1 (double)-0.000489646
#define P2 (double)0.04517
#define P3 (double)-1.65533
#define P4 (double)31.13644
#define P5 (double)-333.73872
#define P6 (double)1919.39436

// Point_t AimPoint;
u32 timer_start;
u32 timer_stop;
int timer_wast;


int main(void)
{		
	/*系统模块初始化*/
	//人机接口模块
	TB_Init();            //时间基准初始化
 	LCD_Init();						//液晶初始化
	LED_Init();						//LED初始化
	SystemInit_key();			//ZLG按键初始化
	Remote_Init();				//红外按键初始化
	InitUSART(19200);   //串口初始化
//delay_init(72);				//SysyTick延时初始化
	EXTI_KEY_Init();

 //电机控制模块
		Controller_Init();      //PID变量初始化
		ENC_Init();					//编码器初始化
		ENC1_Init();
		MotorInit();				//直流电机初始化
		
// 		TIM1_PWM_Init(); //TIM1_PWM输出初始化
// 	MotorA.PositionExpected=0;
// 	MotorB.PositionExpected=0;
	
// 	TIM1_CapInit();//TIM1_捕获初始化
// 	EnableGPIO_Init();

// 	LED0_OFF();
// 	LED1_OFF();
// 	printf("hello,com2");

		display_GB2312_string(1,1,"黄河远上白云间,");  
    display_GB2312_string(3,1,"一片孤城万仞山."); 
    display_GB2312_string(5,1,"羌笛何须怨杨柳,");    
    display_GB2312_string(7,1,"春风不度玉门关."); 
		display_GB2312_string(1,1,"黄河远上白云间,");  
// 	  display_GB2312_string(5,1,"HUST Sci&Tec Inov");
// 		delay_ms(100);
		/*InitDs18b20*/
// 	while(DS18B20_Init())
// 	{
// 		clear_screen();
// 		 display_string_5x7(1,1,"HUST Sci&Tec Inov");
// 		 display_string_5x7(2,1,"DS18B20 Check Failed"); 
// 		 display_string_5x7(3,1,"please Check!"); 
// 			delay_ms(100);
// 			LED0_Toggle();
// 	}

// State=TEST_SPEED;
// State=TEST_ENCODER;
// State=TEST_LOCATION;
// State=POSITION_CONTROL;
// MotorA.PositionExpected=360;
// 	State=SPEED_CONTROL;
// 	MotorA.SpeedExpected=3000;
// State = TEST_SPEED;
// MotorA_Forward(500);
// 	State=TEST_PLAY;
// 	State=TEST_LED;
// State=TEST_IR;
// State=TEST_DELAY;
// State=TEST_KEY_AND_IR;
// 	State=TEST_MOTOR;
// 	MotorA_Forward(100);
//	State=TEST_LCD;
// 	State=TEST_DS18B20;
// 	State=TEST_MOTOR;
// State = LQR_CONTROL;
State = INIT;
	while(1)
	{
// 			if(TB_Delay_IsElapsed()==TRUE)
// 				{
// 					TB_SetDelay_Time(LED_TEST_DELAY);
// 					LED0_Toggle();
// 					LED1_Toggle();
// 				}
		switch(State)
		{
			case IDLE:
// 					if(Remote_Rdy)//红外处理
// 			{
// 				Remote_Rdy=0;
// 				ir_key=Remote_Process();
// 				switch(ir_key)
// 				{
// 					case IR_EQ:
// 						for(BufferNum=0;BufferNum < BUFFER_SIZE;BufferNum++)
// 						{
// 							sprintf(str,"%d\n",SpeedBuffer[BufferNum]);
// 							printf(str);
// 						}
// 						break;
// 						case IR_PLAY:
// 						for(BufferNum=0;BufferNum < BUFFER_SIZE;BufferNum++)
// 						{
// 							sprintf(str,"%d\n",PositionBuffer[BufferNum]);
// 							printf(str);
// 						}
// 							break;
// 					}
// 				}
				break;
// 			case BUFFER_SEND:
			
				break;
			case INIT:	
					INIT_Task();
				break;
			case MENU:
				MENU_Task();
				break;
			case RECIPROCATE_INPUT://往复运动输入
				RECIPROCATE_INPUT_Task();
				break;
			case RECIPROCATE://往复运动中
				RECIPROCATE_Task();
				break;
			case FREE_LQR:
			 FREE_LQR_Task();//等待检测松手后进入闭环控制
				break;
			case LQR_CONTROL:
				LQR_CONTROL_Task();//LQR保持倒立状态
					break;
			case LQR_CIRCULAR_INPUT:
				LQR_CIRCULAT_INPUT_Task();//lqr圆周运动输入角度
				break;
			case LQR_CIRCULAR://LQR圆周运动
				LQR_CIRCULAR_Task();
				break;
			case LQR_TEST:
				LQR_TEST_Task();
			break;
			case POSITION_MEASURE:
				break;
			case POSITION_INPUT:
				break;
			case POSITION_CONTROL:
				POSITION_CONTROL_Task();
				break;
			case SPEED_CONTROL:
				SPEED_CONTROL_Task();
				break;
			case TEST_LCD:
				TEST_LCD_Task();
				break;
			case TEST_USART:
				break;
			case TEST_DELAY:
				break;
			case 	TEST_KEY_AND_IR:		
						if(KeyFlag==1)
						{
							KeyFlag =0;
							LED0_Toggle();
						}
				break;
	 	case TEST_MOTOR:
			TEST_MOTOR_Task();
			break;
		case TEST_SPEED:
			TEST_SPEED_Task();
			break;
			case TEST_ADC:
				break;
			case TEST_ENCODER:
				break;
			case TEST_LED:
				break;
						default:
						break;
					}
	}
}
				
// 			case INIT:
// 				if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//速度调节
// 						{
// 								TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
// 								MotorA.SpeedTest=ENC_Calc_Rot_Speed() ;//转600
// 								MotorA.PWM=SpeedPID_Regulator(MotorA.SpeedExpected-MotorA.SpeedTest);
// 								MotorA_PWM_Update(MotorA.PWM);
// 								MotorB.SpeedTest=ENC1_Calc_Rot_Speed() ;//转600
// 								MotorB.PWM=SpeedPID1_Regulator(MotorB.SpeedExpected-MotorB.SpeedTest);
// 								MotorB_PWM_Update(MotorB.PWM);
// 						}
// 						if(TB_PositionPIDDelay_IsElapsed()==TRUE)
// 						{
// 							TB_SetPositionPIDDelay_Time(POSITION_PID_DELAY);
// 							MotorA.PositionTest = ENC_Get_AnglularPosition();
// 							MotorA.SpeedExpected = PositionPID_Regulator(MotorA.PositionExpected-MotorA.PositionTest);
// 							MotorB.PositionTest = ENC1_Get_AnglularPosition();
// 							MotorB.SpeedExpected = PositionPID1_Regulator(MotorB.PositionExpected-MotorB.PositionTest);
// 						}
// 							if ( IsKeyPressed )		//如果有键按下
// 						{
// 						//清除中断标志
// 							IsKeyPressed = 0;
// 						//读取键值、连击计数器值、功能键值
// 							zlg_key=ZLK_KeyRead();
// 						switch(zlg_key)
// 						{
// 							case KEY1:
// 								MotorA.PositionExpected +=100;
// // 								MotorA_Enable=true;
// 							break;
// 							case KEY4:
// 								MotorA.PositionExpected -=100;
// 							break;
// 							case KEY2:
// 								MotorB.PositionExpected +=100;
// 							break;
// 							case KEY5:
// 								MotorB.PositionExpected -=100;
// 							break;
// // 							case KEY3://意外控制
// // 								MotorA_Brk();
// // 								MotorB_Brk();
// // 								State=IDLE;
// 							break;
// 							case KEY13://完成初始化，进入菜单模式
// 								  ENC_Init();					//编码器初始化
// 									ENC1_Init();
// 									PID_Init();
// 									MotorA.PositionExpected=0;
// 									MotorB.PositionExpected=0;
// 									MotorA.SpeedExpected=0;
// 									MotorB.SpeedExpected=0;
// 									MotorA_Brk();
// 									MotorB_Brk();
// 									State=MENU;
// 								break;
// 						}
// 					}
// 				break;

// 	case SPEED_CONTROL:
// 						if(TB_SpeedPIDDelay_IsElapsed() == TRUE)//速度调节
// 						{
// 								TB_SetSpeedPIDDelay_Time(SPEED_PID_DELAY);
// 								MotorA.SpeedTest=ENC_Calc_Rot_Speed() ;//转600
// 								MotorA.PWM=SpeedPID_Regulator(MotorA.SpeedExpected-MotorA.SpeedTest);
// 								MotorA_PWM_Update(MotorA.PWM);
// 								MotorB.SpeedTest=-ENC1_Calc_Rot_Speed() ;//转600
// 								MotorB.PWM=SpeedPID1_Regulator(MotorB.SpeedExpected-MotorB.SpeedTest);
// 								MotorB_PWM_Update(MotorB.PWM);
// 						}
// // 					if(TB_DisplayDelay_IsElapsed()==TRUE)
// // 					{
// // 								TB_SetDisplayDelay_Time(LCD_DISPLAY_DELAY);
// // 								clear_screen();
// // 								sprintf(str,"AimVa:%f",MotorA.SpeedExpected);
// // 								display_GB2312_string(5,1,str);
// // 								sprintf(str,"Va:%f",MotorA.SpeedTest);
// // 								display_GB2312_string(7,1,str);
// // 								sprintf(str,"AimVb:%f",MotorB.SpeedExpected);
// // 								display_GB2312_string(1,1,str);
// // 								sprintf(str,"Vb:%f",MotorB.SpeedTest);
// // 								display_GB2312_string(3,1,str);
// // 								LED1_Toggle();
// // 					}
// 						if(Remote_Rdy)
// 							{
// 								Remote_Rdy=0;
// 								ir_key=Remote_Process();
// 								switch(ir_key)
// 								{
// 									case IR_KEY1:
// 									MotorA.SpeedExpected+=100;
// 									break;
// 									case IR_KEY2:
// 									MotorA.SpeedExpected-=100;
// 										break;
// 									case IR_KEY4:
// 											MotorB.SpeedExpected+=100;
// 										break;
// 									case IR_KEY5:
// 											MotorB.SpeedExpected-=100;
// 										break;
// 									case IR_PLAY:
// 										MotorA_Brk();
// 										MotorB_Brk();
// 										State=IDLE;
// 									break;
// 								}
// 							}
// 					
// 				break;


// 			case POSITION_CONTROL:

// 				break;
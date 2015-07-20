#include "MyType.h"
#include "led.h"
#include "MYCONST.H"
extern volatile SystStatus_t  STATE;//ϵͳ״̬


/*****����LED����***/
extern volatile LED_TypeDef 		LED;
extern volatile int LED_Time;

/*******�г̿��ر�־********/
extern volatile uint8_t SW0_IsTouched;
extern volatile uint8_t SW1_IsTouched;

/***�������ȫ�ֱ���***/
extern volatile Motor_TypeDef  MotorA;

/*******���ʹ洢���ݱ���**********/
extern volatile s16 SpeedStore[SPEED_STORE_MAX];				//�ٶ��ٶȴ洢
extern volatile s16 CCRStore[CCR_STORE_MAX];						//ռ�ձȵ�ѹ�洢
extern volatile s32 PositionStore[POSITION_STORE_MAX];	//λ�ô洢

//��������
extern volatile s32 SpeedSampleNum;
extern volatile s32 CCRNum;
extern volatile s16 SampleNum;
/**���ڷ�������***/
extern volatile s32 s;
extern volatile s32 c;
extern volatile s32 a;

/***PID��������***/
extern volatile PID_Typedef 	SpeedPID_WC,PositionPID_WC;
/***Control������**/
extern volatile 	s32	SpeedErrorSum;
extern volatile s32 PositionErrorSum;
extern volatile   s16 PWM_B;

extern volatile  u32 INIT_Delay ;

/********����ٶȿ��Ʊ���********/
extern volatile int SpeedMax;
extern volatile int SpeedMin;

/***���Ʊ�־λ***/
extern volatile int IsPositionArrived ;
extern volatile int IsSpeedArrived  ;
extern volatile int IsReport;
extern volatile int PosFrameReceivedFlag;

/***�ٶȴ�ʹ��־*/
extern volatile  	int bIs_First_Measurement ;

/******ȫ�ֱ�����ʼ��*********/
void GloableVariableInit(void);

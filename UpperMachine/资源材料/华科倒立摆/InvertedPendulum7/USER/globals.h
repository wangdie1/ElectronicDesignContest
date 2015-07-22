#ifndef _globals_h
#define _globals_h

#include "stm32f10x.h"
#include "mytype.h"

#define BUFFER_SIZE 1000
#define KE        4.5

// #define K1	(float) -3.3301
// #define K2	(float) 88//88.4105
// #define K3	(float) -6.2931
// #define K4  (float) 8.8556
// #define G   (float) 6
#define K1	(float) -9.3301
#define K2	(float) 110.4105
#define K3	(float) -9.0931
#define K4  (float) 9.656
#define G   (float) 5

// #define K1	(float) -1.1180
// #define K2	(float) 76.0178
// #define K3	(float) -2.7157
// #define K4  (float) 7.4858
// #define G   (float) 6
// #define K1	(float) -3.1623
// #define K2	(float) 83.6464
// #define K3	(float) -3.7022
// #define K4  (float) 8.3137
// #define G   (float) 6

// #define K1	(float) -3.1623
// #define K2	(float) 40.9615
// #define K3	(float) -2.071
// #define K4  (float) 4.9307
// #define G   (float) 1.8

// #define K1	(float) -3.0
// #define K2	(float) 21.315
// #define K3	(float) -3.3903
// #define K4  (float) 2.4490
// #define G   (float) 1
// #define K1	(float) -2.2361
// #define K2	(float) 26.6591
// #define K3	(float) -1.5240*1.2
// #define K4  (float) 2.5730
// #define G   (float) 1.6
extern Motor_TypeDef MotorA,MotorB;
extern SysStatus_t State;
extern SysStatus_t PreStatus;
extern FForward_Typedef PositionFF;
extern PID_Typedef TemperaturePID;
extern PID_Typedef SpeedPID,SpeedPID1,PositionPID,PositionPID1,PositionPID_WV;
extern  float TemperatureAim;
extern float TemperatureAimTemp;
extern float TemperatureTest;
extern  char str[10];
extern float pwm_duty;
extern u8 IsInputOK;
extern int Diec ;
extern u8 IsCycleOK ;
extern s32 SpeedBuffer[BUFFER_SIZE];
extern s32 PositionBuffer[BUFFER_SIZE];
extern s32 BufferNum;
extern double theta;//摆杆角度
extern double alpha;//旋臂角度
extern double alpha_pi;//弧度制
extern double v_alpha_pi ;//速度弧度
extern double v_alpha;//速度
extern double v_theta;
extern int AimAngle;
extern double AimTheta;
extern double ThetaDelta;
extern double StopTheta;
extern double DeltaNum;
extern double E;
extern double E0;
extern int flag2;
extern volatile  u8 KeyFlag ;
#endif

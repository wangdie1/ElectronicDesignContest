#include "stm32f10x.h"
#include "TimeBase.h"
 #include "mytype.h"
#include "control_param.h"
#include "globals.h"
#include "app.h"



/*maxon re25 360rpm 的参数*/
#define MAXON_RE25_SPEED_KP 			(float)			1
#define MAXON_RE25_SPEED_KI 			(float)			0.05
#define MAXON_RE25_POSITION_KP  	    (float)			30
#define MAXON_RE25_POSITION_KD  	    (float)			5
#define MAXON_RE25_POSITION_FF_KV 	    (float)		30
#define MAXON_RE25_SPEED_MAX				3600//460
#define MAXON_RE25_SPEED_MIN				-3600//-460

/*位置环单位是0.01度 36000*/
/*maxon1 125rpm 的参数*/
#define MAXON1_SPEED_KP 		(float)			8
#define MAXON1_SPEED_KI 		(float)			0.04
#define MAXON1_POSITION_KP  (float)			0.07
#define MAXON1_POSITION_FF_KV	(float)		1.5
#define MAXON1_SPEED_MAX			(float)		1250
#define MAXON1_SPEED_MIN			(float)		-1250

/*maxon2 46rpm 的参数*/
#define MAXON2_SPEED_KP 			(float)			8
#define MAXON2_SPEED_KI 			(float)			0.2
#define MAXON2_POSITION_KP  	(float)			0.35
#define MAXON2_POSITION_KD  	(float)			0.02
#define MAXON2_POSITION_FF_KV 	(float)		1.4
#define MAXON2_SPEED_MAX				470//460
#define MAXON2_SPEED_MIN				-470//-460


#define PWM_MAX			999 //
#define PWM_MIN			-999//

#define SPEED_MAX   MAXON_RE25_SPEED_MAX //rpm*10
#define SPEED_MIN		MAXON_RE25_SPEED_MIN





s32  SpeedPID_Regulator(s32 SpeedError,PID_Typedef *PID);
s32 SpeedPID1_Regulator(s32 SpeedError);
s32 PositionPID_Regulator(s32 PositionError,PID_Typedef *PID);
s32 PositionPID1_Regulator(s32 PositionError);
s32 PositionPID_Regulator_WithoutV(float PositionError);
void Controller_Init(void);
void ErrorClear(PID_Typedef *PID );
double P_Controller(float Error,PID_Typedef *PID);
double PI_Controller(float Error,PID_Typedef *PID);
double PD_Controller(float Error,PID_Typedef *PID);
double PID_Controller(float Error,PID_Typedef *PID);
double FF_Controller(double rin,FForward_Typedef *FF );



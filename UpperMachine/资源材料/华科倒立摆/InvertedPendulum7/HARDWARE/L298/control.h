#include "stm32f10x.h"
#include "TimeBase.h"
//#include "control_param.h"

#include "app.h"

#define SPEED_KP 		20//50
#define SPEED_KI 		0.3//0.3//SPEED_KP*(1/SPEED_LOOP_FREQ)/SPEED_TI
#define SPEED_KD 		SPEED_KP*(SPEED_TD*SPEED_LOOP_FREQ)
#define SPEED_ERROR_BOND 2
#define SPEED_TI 		0
#define SPEED_TD 		0


#define SPEED1_KP 		20
#define SPEED1_KI 		0.1//SPEED_KP*(1/SPEED_LOOP_FREQ)/SPEED_TI
#define SPEED1_ERROR_BOND 2

#define PWM_MAX			600 //
#define PWM_MIN			-600//
#define SPEED_MAX   90 //rpm
#define SPEED_MIN		-90

#define POSITION_KP 0.5
#define POSITION_TI 0
#define POSITION_KI	0//0.0001//POSITION_KP/(POSITION_LOOP_FREQ*POSITION_TI)
#define POSITION_ERROR_BOND 10
#define POSITION_MAX  72000


void ErrorClear(void );
s32 SpeedPID_Regulator(s32 SpeedError);
s32 SpeedPID1_Regulator(s32 SpeedError);
// s32 PositionPID_Regulator(s32 PositionError);
void PID_Init(void);


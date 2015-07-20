#ifndef __STEP_H 
#define __STEP_H   
#include "sys.h"  
#include "usart.h" 
#include "delay.h" 

#define LEFT 0 
#define RIGHT 1 

//#define STEP_EN1   PBout(14) 
//#define STEP_EN2   PBout(15) 
#define STEP_DIR  PGout(9) 
#define STEP_CLK  PGout(10)   

////////////////////////////////////////////////////////// 
#define COIN_INT_CNTP SENS_IN5 //中断计数传感器 



//void temp_init(void); 
//void back_money(void); 
//void colt_money(void); 


void Step_Init(void); 
void Step_Run(float deg,u8 lr); 
void Step_Run_18(u16 dx,u8 lr); 
void Step_Run_Left(u16 dx);
void Step_Run_Right(u16 dx);


//u8 Holder_Run(u8 lr); 
//u8 Holder_Back(u8 lr); 

//void step_test(u8 stepx,u16 dt,u16 cycle); 

#endif 
















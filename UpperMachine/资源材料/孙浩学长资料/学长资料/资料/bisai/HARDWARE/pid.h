#ifndef __PID_H__
#define __PID_H__

#include <stm32f10x.h>

float  Kp =     0.32  ; 
float  Ti =                0.09 ; 
float Td =                0.0028 ;  
#define T                  0.02 
#define Ki     Kp*(T/Ti)        
#define Kd                Kp*(Td/T)
typedef struct 
{
 int setpoint;
 int sum_error;
 float proportion ;
 float integral ;
 float derivative;
 int last_error;
 int prev_error;
}PIDtypedef;

void PIDperiodinit(u16 arr,u16 psc);     
void incPIDinit(void);                
int incPIDcalc(PIDtypedef*PIDx,u16 nextpoint);        
void PID_setpoint(PIDtypedef*PIDx,u16 setvalue);
void PID_set(float pp,float ii,float dd);
void set_speed(float W1,float W2,float W3,float W4);

#endif
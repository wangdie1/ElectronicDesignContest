#ifndef _MyTask_h
#define _MyTaks_h
#include "driver.h"
#include "globals.h"
extern  unsigned char Photo0[];
void INIT_Task(void);
void MENU_Task(void);
void INPUT_Task(void);
void POSITION_INPUT_Task(void);
void POSITION_CONTROL_Task(void);
void SPEED_CONTROL_Task();

void TEST_KEY_AND_IR_Task(void);
void TEST_MOTOR_Task(void);
void TEST_LED_Task(void);
void TEST_LCD_Task(void);
void TEST_ADC_Task(void);
void TEST_DS18B20_Task(void);
void TEST_SPEED_Task(void);

void RECIPROCATE_INPUT_Task(void);
void RECIPROCATE_Task(void);
void FREE_LQR_Task(void);
void LQR_CONTROL_Task(void);
void LQR_CIRCULAT_INPUT_Task(void);
void LQR_CIRCULAR_Task(void);
void LQR_TEST_Task(void);
#endif
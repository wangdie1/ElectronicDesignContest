#ifndef _ZLG_Key_h
#define _ZLG_Key_h

#include "I2C.H"
#include "ZLG7290.H"
#include "stm32f10x.h"
#include "delay.h"

#define KEY1			1
#define KEY2			2
#define KEY3			3
#define KEY4   		9
#define KEY5			10
#define KEY6			11
#define KEY7			17
#define KEY8			18
#define KEY9			19
#define KEY10			253
#define KEY11			254
#define KEY12     251
#define KEY13			4
#define KEY14     12
#define KEY15     20
#define KEY16     247
// #define KEY_UP			KEY2
// #define KEY_DOWN		KEY5
// #define KEY_RIGHT		KEY4
// #define KEY_LEFT		KEY6
#define KEY_ENTER		4
#define KEY_BACK  	12
extern volatile  unsigned char zlg_key;
void SystemInit_key(void);
void ClearAll(void);
void Disp_Led(u8	dat,u8	b);
void DispValue(char x, unsigned char dat);
void DispHexValue(char x, unsigned char dat);
void Test_Key(void);
unsigned char ZLK_KeyRead(void);
#endif
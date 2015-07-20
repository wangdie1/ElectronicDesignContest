#ifndef _wt_display_h
#define _wt_display_h

#include "timebase.h"
#include "mytype.h"
#include "stm32f10x.h"
#include "wt_lcd.h"
#define VISUALIZATION_0   (u8)0
#define VISUALIZATION_1   (u8)1
#define VISUALIZATION_2   (u8)2
#define VISUALIZATION_3   (u8)3
#define VISUALIZATION_4   (u8)4
#define VISUALIZATION_5   (u8)5
#define VISUALIZATION_6   (u8)6
#define VISUALIZATION_7   (u8)7
#define VISUALIZATION_8   (u8)8
#define VISUALIZATION_9   (u8)9
#define VISUALIZATION_10  (u8)10


u8 ComputerVisualization(u8 bLocal_MenuIndex);
void Display_Welcome_Message(void);
void Display_LCD(void);

#endif
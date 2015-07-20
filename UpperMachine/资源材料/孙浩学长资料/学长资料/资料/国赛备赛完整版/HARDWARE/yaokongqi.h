#ifndef _YAOKONGQI_H_
#define _YAOKONGQI_H_
#include <stm32f10x.h>
void yaokongqi_init(void);
unsigned int key_scan(void);
void huanyingjiemian(void);
void xuanzejiemian(void);
void querenjiemian(void);
void yanshijiemian(void);
void jieshujiemian(void);
void Lcd_Part_Clear(u16 x,u16 y,u16 width,u16 height,u16 CharBackColor);
#endif

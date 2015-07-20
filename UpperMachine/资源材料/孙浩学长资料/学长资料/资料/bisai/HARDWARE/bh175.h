#ifndef __BH175_H
#define __BH175_H

#include"i2c.h"
#include"delay.h"
int Single_Write_BH1750(u8 REG_Address);

u8 Multiple_read_BH1750(void);

char read_eprom(void);
void write_eprom(char);

#endif


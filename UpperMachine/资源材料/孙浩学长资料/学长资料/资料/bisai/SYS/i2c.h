#ifndef   __I2C_H
#define   __I2C_H

#include<stm32f10x.h>
#include"delay.h"
//SDAΪPB11
//SCLΪPB10
void   start_i2c(void);
void   stop_i2c(void);
void   sendbyte(unsigned char  c);
unsigned char     rcvbyte(void);
void   send_ack(unsigned char a);
void   i2c_init(void);
unsigned char     i2c_Wait_Ack(void);
unsigned char     rcv_ack(void);

#endif

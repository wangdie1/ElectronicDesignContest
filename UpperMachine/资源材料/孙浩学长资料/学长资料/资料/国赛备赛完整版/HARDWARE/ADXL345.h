#ifndef __ADXL345_H
#define __ADXL345_H

#define DEVICE_ID		0X00 	//Æ÷¼þID,0XE5
#define THRESH_TAP		0X1D   	//ÇÃ»÷·§Öµ
#define OFSX			0X1E
#define OFSY			0X1F
#define OFSZ			0X20
#define DUR				0X21
#define Latent			0X22
#define Window  		0X23 
#define THRESH_ACK		0X24
#define THRESH_INACT	0X25 
#define TIME_INACT		0X26
#define ACT_INACT_CTL	0X27	 
#define THRESH_FF		0X28	
#define TIME_FF			0X29 
#define TAP_AXES		0X2A  
#define ACT_TAP_STATUS  0X2B 
#define BW_RATE			0X2C 
#define POWER_CTL		0X2D 

#define INT_ENABLE		0X2E
#define INT_MAP			0X2F
#define INT_SOURCE  	0X30
#define DATA_FORMAT	    0X31
#define DATA_X0			0X32
#define DATA_X1			0X33
#define DATA_Y0			0X34
#define DATA_Y1			0X35
#define DATA_Z0			0X36
#define DATA_Z1			0X37
#define FIFO_CTL		0X38
#define FIFO_STATUS		0X39


#define ADXL_READ    0XA7
#define ADXL_WRITE   0XA6


void Single_Write(unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char REG_Address);
void Multiple_read(short *x,short *y,short *z);
int Init_ADXL345(void);
void ADXL345_RD_Avval(short *x,short *y,short *z);
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval);
void ADXL345_Read_Average(short *x,short *y,short *z,unsigned char times);
short ADXL345_Get_Angle(float x,float y,float z,unsigned char dir);



#endif


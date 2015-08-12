#include "niming.h"
#include "led.h"
#include "usart.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103开发板
//IIC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


float ROL_P = 0;
float ROL_I = 0;
float ROL_D = 0;
float PIT_P = 0;
float PIT_I = 0;
float PIT_D =0 ;
float YAW_P = 0;
float YAW_I = 0;
float YAW_D = 0;



//串口1发送1个字符 
//c:要发送的字符
void usart1_send_char(u8 c)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//循环发送,直到发送完毕   
    USART_SendData(USART1,c);   
} 

//传送数据给匿名四轴上位机软件(V2.6版本)
//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=len;	//数据长度
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//发送数据到串口1 
}

//发送加速度传感器数据和陀螺仪数据
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//自定义帧,0XA1
}	

//通过串口1上报结算后的姿态数据给电脑
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
//roll:横滚角.单位0.01度。 -18000 -> 18000 对应 -180.00  ->  180.00度
//pitch:俯仰角.单位 0.01度。-9000 - 9000 对应 -90.00 -> 90.00 度
//yaw:航向角.单位为0.1度 0 -> 3600  对应 0 -> 360.0度
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//清0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//飞控显示帧,0XAF
}  


//传送pid数据给匿名上位机

void usart1_niming_report_pid(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=0x1C;
	send_buf[3]=0xAD;
	send_buf[4]=len;	//数据长度
	for(i=0;i<len;i++)
		send_buf[4+i]=data[i];			//复制数据
	for(i=0;i<len+4;i++)
		send_buf[len+4]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+5;i++)
		usart1_send_char(send_buf[i]);	//发送数据到串口1 
}



//两路pwm曲线，两路编码器  
void usart1_report_Pwm(short pwm1,short pwm2,short enc1,short enc2)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
	tbuf[i]=0;//清0
	tbuf[0]=(pwm1>>8)&0XFF;
	tbuf[1]=pwm1&0XFF;
	tbuf[2]=(pwm2>>8)&0XFF;
	tbuf[3]=pwm2&0XFF;
	tbuf[4]=(enc1>>8)&0XFF;
	tbuf[5]=enc1&0XFF;
	tbuf[6]=(enc2>>8)&0XFF;
	tbuf[7]=enc2&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//飞控显示帧,0XAF
} 


//
void usart_report_enc(short enc1)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
	tbuf[i]=0;//清0
	tbuf[0]=(enc1>>8)&0XFF;
	tbuf[1]=enc1&0XFF;

	usart1_niming_report(0XAF,tbuf,28);//飞控显示帧,0XAF
}

//发送pid的数值给上位机
void usart1_report_Pid(short pid_p,short pid_i,short pid_d)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
		tbuf[i]=0;//清0
	tbuf[0]=(pid_p>>8)&0XFF;
	tbuf[1]=pid_p&0XFF;
	tbuf[2]=(pid_i>>8)&0XFF;
	tbuf[3]=pid_i&0XFF;
	tbuf[4]=(pid_d>>8)&0XFF;
	tbuf[5]=pid_d&0XFF;
	usart1_niming_report_pid(0XAC,tbuf,20);//飞控显示帧,0XAF
} 

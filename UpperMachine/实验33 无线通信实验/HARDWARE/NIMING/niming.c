#include "niming.h"
#include "led.h"
#include "usart.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
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



//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//ѭ������,ֱ���������   
    USART_SendData(USART1,c);   
} 

//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}

//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
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
	usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1
}	

//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
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
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
}  


//����pid���ݸ�������λ��

void usart1_niming_report_pid(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=0x1C;
	send_buf[3]=0xAD;
	send_buf[4]=len;	//���ݳ���
	for(i=0;i<len;i++)
		send_buf[4+i]=data[i];			//��������
	for(i=0;i<len+4;i++)
		send_buf[len+4]+=send_buf[i];	//����У���	
	for(i=0;i<len+5;i++)
		usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}



//��·pwm���ߣ���·������  
void usart1_report_Pwm(short pwm1,short pwm2,short enc1,short enc2)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
	tbuf[i]=0;//��0
	tbuf[0]=(pwm1>>8)&0XFF;
	tbuf[1]=pwm1&0XFF;
	tbuf[2]=(pwm2>>8)&0XFF;
	tbuf[3]=pwm2&0XFF;
	tbuf[4]=(enc1>>8)&0XFF;
	tbuf[5]=enc1&0XFF;
	tbuf[6]=(enc2>>8)&0XFF;
	tbuf[7]=enc2&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
} 


//
void usart_report_enc(short enc1)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
	tbuf[i]=0;//��0
	tbuf[0]=(enc1>>8)&0XFF;
	tbuf[1]=enc1&0XFF;

	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
}

//����pid����ֵ����λ��
void usart1_report_Pid(short pid_p,short pid_i,short pid_d)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)
		tbuf[i]=0;//��0
	tbuf[0]=(pid_p>>8)&0XFF;
	tbuf[1]=pid_p&0XFF;
	tbuf[2]=(pid_i>>8)&0XFF;
	tbuf[3]=pid_i&0XFF;
	tbuf[4]=(pid_d>>8)&0XFF;
	tbuf[5]=pid_d&0XFF;
	usart1_niming_report_pid(0XAC,tbuf,20);//�ɿ���ʾ֡,0XAF
} 

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


void usart1_send_char(u8 c)
{

	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,c);   
} 

//void usart2_ReceiveData_char(u8 c)
//{
//	while(USART_GetITStatus(USART1, USART_FLAG_RXNE) != RESET); 
//	c = USART_ReceiveData(USART1);
//}

//int  usart1_niming_RecevieData(u8*data)
//{
//	u8 send_buf[32];
//	u8 receive_buf[32];
//	u8 receive_buf_data = 0;
//	u8 i;
//	u8 len = 28;
//	
//	//���Բ�����У��λ
//	
//	if(receive_buf[0]!=0x8A)
//		return 0;
//	if(receive_buf[1]!=0x8B)
//		return 0;
//	if(receive_buf[2]!=0x1C)
//		return 0;
//	if(receive_buf[3]!=0xAE)
//		return 0;
//	
//	for(i=0;i<len+3;i++)
//		receive_buf_data += receive_buf[i];	//����У���	
//	if(receive_buf[len+3]!=receive_buf_data)
//		return 0;
//	return 1;
//}


//void usart1_recevie_Pid(short pid_p,short pid_i,short pid_d)
//{
//	u8 data[28];
//	if(usart1_niming_RecevieData(&data) == 1)
//		
//} 

void Data_Receive_Anl(u8 *data_buf)
{
	u8 i;
	u8 num=32;
	vs16 rc_value_temp;
	u8 sum = 0;

	//����У���
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
    //�ж�У��� 
	if(!(sum==*(data_buf+num-1)))
//		return;		//??sum
	//�ж�֡ͷ
	if((*(data_buf)!=0x8A || *(data_buf+1)!=0x8B))
//		return;		//????
/////////////////////////////////////////////////////////////////////////////////////

	if(*(data_buf+2)==0X1C)								//PID1
	{
			ROL_P = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/100;
			ROL_I = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
			ROL_D = (float)((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100;
			PIT_P = (float)((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
			PIT_I = (float)((vs16)(*(data_buf+12)<<8)|*(data_buf+13))/1000;
			PIT_D = (float)((vs16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
			YAW_P = (float)((vs16)(*(data_buf+16)<<8)|*(data_buf+17))/100;
			YAW_I = (float)((vs16)(*(data_buf+18)<<8)|*(data_buf+19))/100;
			YAW_D = (float)((vs16)(*(data_buf+20)<<8)|*(data_buf+21))/100;
	}
	
	if(ROL_P> 10)
	{
		LED0 = 1;
		LED1 = 0;
	}

}

void Data_Receive(void)
{
	u8 sta,len;
//	if(USART_RX_STA&0x8000)//���ڽ�����ɣ�
//	{					   
//		len=USART_RX_STA&0x3fff;	//�õ��˴ν��յ������ݳ���
//		USART_RX_BUF[len]='\0';	//��ĩβ���������. 
		Data_Receive_Anl(USART_RX_BUF);
//		sta=usmart_dev.cmd_rec(USART_RX_BUF);//�õ�����������Ϣ
//		if(sta==0)
//			usmart_dev.exe();	//ִ�к��� 
//		else 
//		{  
////			len=usmart_sys_cmd_exe(USART_RX_BUF);
//		
//			if(len!=USMART_FUNCERR)sta=len;
//			if(sta)
//			{
//				switch(sta)
//				{
//					case USMART_FUNCERR:
//						printf("��������!\r\n");   			
//						break;	
//					case USMART_PARMERR:
//						printf("��������!\r\n");   			
//						break;				
//					case USMART_PARMOVER:
//						printf("����̫��!\r\n");   			
//						break;		
//					case USMART_NOFUNCFIND:
//						printf("δ�ҵ�ƥ��ĺ���!\r\n");   			
//						break;		
//				}
//			}
//		}
		USART_RX_STA=0;//״̬�Ĵ������	    
//	}
}
//void Data_Send_Check(u16 check)
//{
//	data_to_send[0]=0xAA;
//	data_to_send[1]=0xAA;
//	data_to_send[2]=0xF0;
//	data_to_send[3]=3;
//	data_to_send[4]=0xBA;
//	
//	data_to_send[5]=BYTE1(check);
//	data_to_send[6]=BYTE0(check);
//	
//	u8 sum = 0;
//	for(u8 i=0;i<7;i++)
//		sum += data_to_send[i];
//	
//	data_to_send[7]=sum;

//	Uart1_Put_Buf(data_to_send,8);
//}





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
	for(i=0;i<len;i++)
		send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)
		send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)
		usart1_send_char(send_buf[i]);	//�������ݵ�����1 
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
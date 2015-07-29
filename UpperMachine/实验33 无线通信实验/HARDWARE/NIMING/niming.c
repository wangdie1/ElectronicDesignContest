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
//	//可以不计算校验位
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
//		receive_buf_data += receive_buf[i];	//计算校验和	
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

	//计算校验和
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
    //判断校验和 
	if(!(sum==*(data_buf+num-1)))
//		return;		//??sum
	//判断帧头
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
//	if(USART_RX_STA&0x8000)//串口接收完成？
//	{					   
//		len=USART_RX_STA&0x3fff;	//得到此次接收到的数据长度
//		USART_RX_BUF[len]='\0';	//在末尾加入结束符. 
		Data_Receive_Anl(USART_RX_BUF);
//		sta=usmart_dev.cmd_rec(USART_RX_BUF);//得到函数各个信息
//		if(sta==0)
//			usmart_dev.exe();	//执行函数 
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
//						printf("函数错误!\r\n");   			
//						break;	
//					case USMART_PARMERR:
//						printf("参数错误!\r\n");   			
//						break;				
//					case USMART_PARMOVER:
//						printf("参数太多!\r\n");   			
//						break;		
//					case USMART_NOFUNCFIND:
//						printf("未找到匹配的函数!\r\n");   			
//						break;		
//				}
//			}
//		}
		USART_RX_STA=0;//状态寄存器清空	    
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
	for(i=0;i<len;i++)
		send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)
		send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+4;i++)
		usart1_send_char(send_buf[i]);	//发送数据到串口1 
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
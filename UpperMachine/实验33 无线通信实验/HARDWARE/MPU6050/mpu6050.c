#include "mpu6050.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//MPU6050 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
 
//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Init(void)
{ 
	u8 res;
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��AFIOʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��ʹ������IO PORTAʱ�� 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	 // �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��ֹJTAG,�Ӷ�PA15��������ͨIOʹ��,����PA15��������ͨIO!!!
	
	MPU_AD0_CTRL=0;			//����MPU6050��AD0��Ϊ�͵�ƽ,�ӻ���ַΪ:0X68
	
	MPU_IIC_Init();//��ʼ��IIC����
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
  delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);						//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		MPU_IIC_Send_Byte(buf[i]);	//��������
		if(MPU_IIC_Wait_Ack())		//�ȴ�ACK
		{
			MPU_IIC_Stop();	 
			return 1;		 
		}		
	}    
    MPU_IIC_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=MPU_IIC_Read_Byte(0);//������,����nACK 
		else *buf=MPU_IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    MPU_IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	MPU_IIC_Send_Byte(data);//��������
	if(MPU_IIC_Wait_Ack())	//�ȴ�ACK
	{
		MPU_IIC_Stop();	 
		return 1;		 
	}		 
    MPU_IIC_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|1);//����������ַ+������	
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=MPU_IIC_Read_Byte(0);//��ȡ����,����nACK 
    MPU_IIC_Stop();			//����һ��ֹͣ���� 
	return res;		
}



//mpu6050��ʹ�ù�ʽ

//int main(void)
// {	 
//	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
//	u8 key;
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�	
//	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(500000);	 	//���ڳ�ʼ��Ϊ500000
//	delay_init();	//��ʱ��ʼ�� 
//	usmart_dev.init(72);		//��ʼ��USMART
//	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
//	LCD_Init();			   		//��ʼ��LCD  
//	MPU_Init();					//��ʼ��MPU6050
// 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
//	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
//	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
//	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(30,110,200,16,16,"2015/1/17"); 
//	while(mpu_dmp_init())
// 	{
//		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
//		delay_ms(200);
//		LCD_Fill(30,130,239,130+16,WHITE);
// 		delay_ms(200);
//	}  
//	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
//	LCD_ShowString(30,150,200,16,16,"KEY0:UPLOAD ON/OFF");
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
// 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
// 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
// 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
// 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
// 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");	 
// 	while(1)
//	{
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES)
//		{
//			report=!report;
//			if(report)LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");
//			else LCD_ShowString(30,170,200,16,16,"UPLOAD OFF");
//		}
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{ 
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			if(report)
//				mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
//			if(report)
//				usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
//			if((t%10)==0)
//			{ 
//				//�¶�ֵ
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//��ʾС������ 
//				
//				//ŷ���� pitch
//				temp=pitch*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,220,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//��ʾС������ 
//				
//				//ŷ���� roll
//				temp=roll*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}
//				else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//��ʾС������ 
//				
//				//ŷ���� yaw
//				temp=yaw*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//��ʾС������  
//				t=0;
//				LED0=!LED0;//LED��˸
//			}
//		}
//		t++; 
//	} 	
//}
// 


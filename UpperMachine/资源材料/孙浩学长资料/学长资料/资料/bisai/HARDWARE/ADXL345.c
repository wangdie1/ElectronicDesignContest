 #include"ADXL345.h"
 #include"i2c.h"
 #include"delay.h"
 #include<math.h>
 int ADXL_BUF[6]={0};

 void Single_Write(unsigned char REG_Address,unsigned char REG_data)
{
    start_i2c();                 //��ʼ�ź�
    sendbyte(ADXL_WRITE);   //�����豸��ַ+д�ź�
	i2c_Wait_Ack();
    sendbyte(REG_Address);    //�ڲ��Ĵ�����ַ
	i2c_Wait_Ack();
    sendbyte(REG_data);      //�ڲ��Ĵ�������
	i2c_Wait_Ack();
    stop_i2c();                   //����ֹͣ�ź�
}


//********���ֽڶ�ȡ*****************************************

unsigned char Single_Read(unsigned char REG_Address)
{  
    unsigned char REG_data;
    start_i2c();                            //��ʼ�ź�/    
	sendbyte(ADXL_WRITE);           //�����豸��ַ+д�ź�
	i2c_Wait_Ack();
    sendbyte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ
	i2c_Wait_Ack();

    start_i2c();                            //��ʼ�ź�
    sendbyte(ADXL_READ);         //�����豸��ַ+���ź�
	i2c_Wait_Ack();
    REG_data=rcvbyte();              //�����Ĵ�������
    send_ack(1);
    stop_i2c( );                            //ֹͣ�ź�
    return REG_data;
}


/*
��������ADXL345�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
*/
void Multiple_read(short *x,short *y,short *z)
{
    unsigned char i;
    start_i2c();                          //��ʼ�ź�
    sendbyte(ADXL_WRITE);          //�����豸��ַ+д�ź�
	i2c_Wait_Ack();
    sendbyte(0x32);
	i2c_Wait_Ack();
   
    start_i2c();                           //��ʼ�ź�
    sendbyte(ADXL_READ);         //�����豸��ַ+���ź�
	i2c_Wait_Ack();
    for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        ADXL_BUF[i] = rcvbyte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           send_ack(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
           send_ack(0);                //��ӦACK
        }
    }
    stop_i2c( );                          //ֹͣ�ź�
    *x=(short)(((u16)ADXL_BUF[1]<<8)+ADXL_BUF[0]); 	    
	*y=(short)(((u16)ADXL_BUF[3]<<8)+ADXL_BUF[2]); 	    
	*z=(short)(((u16)ADXL_BUF[5]<<8)+ADXL_BUF[4]); 
}


//*****************************************************************
//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�************************
int Init_ADXL345()
{
    if(Single_Read(DEVICE_ID)==0XE5)
	{	//��ȡ����ID
    Single_Write(DATA_FORMAT,0x2b);   //������Χ,����16g��13λģʽ
    Single_Write(BW_RATE,    0x0a);   //�����趨Ϊ12.5 
    Single_Write(POWER_CTL,  0x28);   //ѡ���Դģʽ   
    Single_Write(INT_ENABLE, 0x00);   //ʹ�� DATA_READY �ж�
    Single_Write(OFSX,0x00);   //X ƫ���� 
    Single_Write(OFSY,0x00);   //Y ƫ���� 
    Single_Write(OFSZ,0x00);   //Z ƫ���� 
	return 0;
	}
	else
	return 1;
}


short ADXL345_Get_Angle(float x,float y,float z,u8 dir)
{
	float temp;
 	float res=0;
	switch(dir)
	{
		case 0://����ȻZ��ĽǶ�
 			temp=sqrt((x*x+y*y))/z;
 			res=atan(temp);
 			break;
		case 1://����ȻX��ĽǶ�
 			temp=x/sqrt((y*y+z*z));
 			res=atan(temp);
 			break;
 		case 2://����ȻY��ĽǶ�
 			temp=y/sqrt((x*x+z*z));
 			res=atan(temp);
 			break;
 	}
	return res*1800/3.14;
}


void ADXL345_Read_Average(short *x,short *y,short *z,u8 times)
{
	u8 i;
	short tx,ty,tz;
	*x=0;
	*y=0;
	*z=0;
	if(times)//��ȡ������Ϊ0
	{
		for(i=0;i<times;i++)//������ȡtimes��
		{
			Multiple_read(&tx,&ty,&tz);
			*x+=tx;
			*y+=ty;
			*z+=tz;
			delay_ms(5);
		}
		*x/=times;
		*y/=times;
		*z/=times;
	}
}





//�Զ�У׼
//xval,yval,zval:x,y,z���У׼ֵ
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
{
	short tx,ty,tz;
	u8 i;
	short offx=0,offy=0,offz=0;
	Single_Write(POWER_CTL,0x00);	   	//�Ƚ�������ģʽ.
	delay_ms(100);
	Single_Write(DATA_FORMAT,0X2B);	//�͵�ƽ�ж����,13λȫ�ֱ���,��������Ҷ���,16g���� 
	Single_Write(BW_RATE,0x0A);		//��������ٶ�Ϊ100Hz
	Single_Write(POWER_CTL,0x28);	   	//����ʹ��,����ģʽ
	Single_Write(INT_ENABLE,0x00);	//��ʹ���ж�		 

	Single_Write(OFSX,0x00);
	Single_Write(OFSY,0x00);
	Single_Write(OFSZ,0x00);
	delay_ms(12);
	for(i=0;i<10;i++)
	{
		ADXL345_RD_Avval(&tx,&ty,&tz);
		offx+=tx;
		offy+=ty;
		offz+=tz;
	}	 		
	offx/=10;
	offy/=10;
	offz/=10;
	*xval=-offx/4;
	*yval=-offy/4;
	*zval=-(offz-256)/4;	  
 	Single_Write(OFSX,*xval);
	Single_Write(OFSY,*yval);
	Single_Write(OFSZ,*zval);	
}

//��ȡADXL��ƽ��ֵ
//x,y,z:��ȡ10�κ�ȡƽ��ֵ
void ADXL345_RD_Avval(short *x,short *y,short *z)
{
	short tx=0,ty=0,tz=0;	   
	u8 i;  
	for(i=0;i<10;i++)
	{
		Multiple_read(x,y,z);
		delay_ms(10);
		tx+=(short)*x;
		ty+=(short)*y;
		tz+=(short)*z;	   
	}
	*x=tx/10;
	*y=ty/10;
	*z=tz/10;
} 


/*
extern int ADXL_BUF[6];
short x_dat=0,y_dat=0,z_dat=0;
int main()
{
	int i=0;
	SYS_CONFIG();
    i2c_init();
  	Init_ADXL345();
	delay_ms(520);
	
	while(1)
	{
	
	   
	 Multiple_read(&x_dat,&y_dat,&z_dat);
	 
	 printf("%d  %d  %d   ",x_dat,y_dat,z_dat);
	 printf("%\r\n");
	 delay_ms(1000);
	 
	}
   
}




*/

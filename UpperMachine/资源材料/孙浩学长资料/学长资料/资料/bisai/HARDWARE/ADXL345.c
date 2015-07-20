 #include"ADXL345.h"
 #include"i2c.h"
 #include"delay.h"
 #include<math.h>
 int ADXL_BUF[6]={0};

 void Single_Write(unsigned char REG_Address,unsigned char REG_data)
{
    start_i2c();                 //起始信号
    sendbyte(ADXL_WRITE);   //发送设备地址+写信号
	i2c_Wait_Ack();
    sendbyte(REG_Address);    //内部寄存器地址
	i2c_Wait_Ack();
    sendbyte(REG_data);      //内部寄存器数据
	i2c_Wait_Ack();
    stop_i2c();                   //发送停止信号
}


//********单字节读取*****************************************

unsigned char Single_Read(unsigned char REG_Address)
{  
    unsigned char REG_data;
    start_i2c();                            //起始信号/    
	sendbyte(ADXL_WRITE);           //发送设备地址+写信号
	i2c_Wait_Ack();
    sendbyte(REG_Address);                   //发送存储单元地址，从0开始
	i2c_Wait_Ack();

    start_i2c();                            //起始信号
    sendbyte(ADXL_READ);         //发送设备地址+读信号
	i2c_Wait_Ack();
    REG_data=rcvbyte();              //读出寄存器数据
    send_ack(1);
    stop_i2c( );                            //停止信号
    return REG_data;
}


/*
连续读出ADXL345内部加速度数据，地址范围0x32~0x37
*/
void Multiple_read(short *x,short *y,short *z)
{
    unsigned char i;
    start_i2c();                          //起始信号
    sendbyte(ADXL_WRITE);          //发送设备地址+写信号
	i2c_Wait_Ack();
    sendbyte(0x32);
	i2c_Wait_Ack();
   
    start_i2c();                           //起始信号
    sendbyte(ADXL_READ);         //发送设备地址+读信号
	i2c_Wait_Ack();
    for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        ADXL_BUF[i] = rcvbyte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           send_ack(1);                //最后一个数据需要回NOACK
        }
        else
        {
           send_ack(0);                //回应ACK
        }
    }
    stop_i2c( );                          //停止信号
    *x=(short)(((u16)ADXL_BUF[1]<<8)+ADXL_BUF[0]); 	    
	*y=(short)(((u16)ADXL_BUF[3]<<8)+ADXL_BUF[2]); 	    
	*z=(short)(((u16)ADXL_BUF[5]<<8)+ADXL_BUF[4]); 
}


//*****************************************************************
//初始化ADXL345，根据需要请参考pdf进行修改************************
int Init_ADXL345()
{
    if(Single_Read(DEVICE_ID)==0XE5)
	{	//读取器件ID
    Single_Write(DATA_FORMAT,0x2b);   //测量范围,正负16g，13位模式
    Single_Write(BW_RATE,    0x0a);   //速率设定为12.5 
    Single_Write(POWER_CTL,  0x28);   //选择电源模式   
    Single_Write(INT_ENABLE, 0x00);   //使能 DATA_READY 中断
    Single_Write(OFSX,0x00);   //X 偏移量 
    Single_Write(OFSY,0x00);   //Y 偏移量 
    Single_Write(OFSZ,0x00);   //Z 偏移量 
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
		case 0://与自然Z轴的角度
 			temp=sqrt((x*x+y*y))/z;
 			res=atan(temp);
 			break;
		case 1://与自然X轴的角度
 			temp=x/sqrt((y*y+z*z));
 			res=atan(temp);
 			break;
 		case 2://与自然Y轴的角度
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
	if(times)//读取次数不为0
	{
		for(i=0;i<times;i++)//连续读取times次
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





//自动校准
//xval,yval,zval:x,y,z轴的校准值
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval)
{
	short tx,ty,tz;
	u8 i;
	short offx=0,offy=0,offz=0;
	Single_Write(POWER_CTL,0x00);	   	//先进入休眠模式.
	delay_ms(100);
	Single_Write(DATA_FORMAT,0X2B);	//低电平中断输出,13位全分辨率,输出数据右对齐,16g量程 
	Single_Write(BW_RATE,0x0A);		//数据输出速度为100Hz
	Single_Write(POWER_CTL,0x28);	   	//链接使能,测量模式
	Single_Write(INT_ENABLE,0x00);	//不使用中断		 

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

//读取ADXL的平均值
//x,y,z:读取10次后取平均值
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

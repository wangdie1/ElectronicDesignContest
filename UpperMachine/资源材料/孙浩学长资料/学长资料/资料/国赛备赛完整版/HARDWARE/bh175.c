#include"bh175.h"


#define	  SlaveAddress   0x46 
u8 BUF[5]={0};


int  Single_Write_BH1750(u8 REG_Address)
{
    start_i2c();                  //起始信号
    sendbyte(SlaveAddress);   //发送设备地址+写信号
    i2c_Wait_Ack();

    sendbyte(REG_Address);    //内部寄存器地址，
	i2c_Wait_Ack();

    stop_i2c();                   //发送停止信号
	 return 0;
}


u8 Multiple_read_BH1750(void)
{   u8 i;	
    start_i2c();                          //起始信号
    sendbyte(SlaveAddress+1);         //发送设备地址+读信号
	i2c_Wait_Ack();
 
	 for (i=0; i<3; i++)                      //连续读取2个地址数据，存储中BUF
    {	 
        BUF[i] = rcvbyte();          //BUF[0]存储0x32地址中的数据
        if (i == 3)
        {

           send_ack(1);                //最后一个数据需要回NOACK
        }
        else
        {		
          send_ack(0);                //回应ACK
       }
   }   

    stop_i2c();                          //停止信号
    delay_ms(5);

	return 1;
}  

/*
extern u8 BUF[5];

int main()
{

  u16 dis_data=0;
  SYS_CONFIG();
 
  i2c_init();
  delay_ms(500);
  Single_Write_BH1750(0x01);   //准备接受命令


  while(1)
  {
   Single_Write_BH1750(0x01);
   Single_Write_BH1750(0x10);

   delay_ms(180);	  //等待180ms
   Multiple_read_BH1750();
   dis_data=BUF[0];
   dis_data=(dis_data<<8)+BUF[1];
   printf("%d\r\n",dis_data);  
   
   delay_ms(500);
 
   } 


}

*/



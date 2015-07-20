#include"bh175.h"


#define	  SlaveAddress   0x46 
u8 BUF[5]={0};


int  Single_Write_BH1750(u8 REG_Address)
{
    start_i2c();                  //��ʼ�ź�
    sendbyte(SlaveAddress);   //�����豸��ַ+д�ź�
    i2c_Wait_Ack();

    sendbyte(REG_Address);    //�ڲ��Ĵ�����ַ��
	i2c_Wait_Ack();

    stop_i2c();                   //����ֹͣ�ź�
	 return 0;
}


u8 Multiple_read_BH1750(void)
{   u8 i;	
    start_i2c();                          //��ʼ�ź�
    sendbyte(SlaveAddress+1);         //�����豸��ַ+���ź�
	i2c_Wait_Ack();
 
	 for (i=0; i<3; i++)                      //������ȡ2����ַ���ݣ��洢��BUF
    {	 
        BUF[i] = rcvbyte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3)
        {

           send_ack(1);                //���һ��������Ҫ��NOACK
        }
        else
        {		
          send_ack(0);                //��ӦACK
       }
   }   

    stop_i2c();                          //ֹͣ�ź�
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
  Single_Write_BH1750(0x01);   //׼����������


  while(1)
  {
   Single_Write_BH1750(0x01);
   Single_Write_BH1750(0x10);

   delay_ms(180);	  //�ȴ�180ms
   Multiple_read_BH1750();
   dis_data=BUF[0];
   dis_data=(dis_data<<8)+BUF[1];
   printf("%d\r\n",dis_data);  
   
   delay_ms(500);
 
   } 


}

*/



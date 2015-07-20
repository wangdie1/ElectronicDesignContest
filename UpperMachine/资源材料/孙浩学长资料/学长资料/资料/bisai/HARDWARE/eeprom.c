#include"eeprom.h"
#include"delay.h"

#define ADDR  0xa0

int buffer[10]={0};

void Eeprom_ByteWrite(int addr,int dat)
{
	 start_i2c();  
	 sendbyte(ADDR);
	 i2c_Wait_Ack();
	 sendbyte(addr);
	 i2c_Wait_Ack();
	 sendbyte(dat);
	 i2c_Wait_Ack();
	 stop_i2c();
}



void eeprom_PageWrite(int addr,char* table,int len )
{
    int i=0;

	for(i=0;i<len;i++)
	{
	Eeprom_ByteWrite(addr+i,table[i]);
	delay_ms(4);  //延时很重要不能丢
	}

}


int Eeprom_ReadOneByte(int addr)
{
	 int rec;
	 start_i2c();  
	 sendbyte(ADDR);
	 i2c_Wait_Ack();
	 sendbyte(addr);
	 i2c_Wait_Ack();
	 start_i2c();
	 sendbyte(ADDR+1);
	 i2c_Wait_Ack(); 
	 rec=rcvbyte();
	 send_ack(1);
	 stop_i2c();

	 return rec;
}


void  Eeprom_SquRead(int addr,int len)
{
	 int i=0;
	 start_i2c();  
	 sendbyte(ADDR);
	 i2c_Wait_Ack();
	 sendbyte(addr);
	 i2c_Wait_Ack();
	 start_i2c();
	 sendbyte(ADDR+1);
	 i2c_Wait_Ack(); 
	 for(i=0;i<len;i++)
	 {
	   if(i==len-1)
	   {
	   buffer[i]=rcvbyte();
	   send_ack(1);
	   }
	   else
	   {
	   buffer[i]=rcvbyte();
	   send_ack(0);
	   }
	  }
	 
	 stop_i2c();

}


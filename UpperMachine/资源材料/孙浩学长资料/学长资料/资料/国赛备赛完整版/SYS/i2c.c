/*嵌入式家园stm32 I2C代码库函数版1.0版本 不足之处希望同学们可以多多修改，使程序更
加完善。*/
/*
对于应答机制输出0代表应答，输出高电平代表非应答，我们在考虑应
答的同时也必须考虑是由主机发出还是由从机发出
 2013.6.25 */

//SDA为PB11
//SCL为PB10

#include"i2c.h"

/*****************************i2c硬件接口******************************/
/*可以根据需要进行改变*/ 
#define    sda_pin    GPIO_Pin_11               //I2C  数据 
#define    scl_pin    GPIO_Pin_10               //I2C   时钟 
#define    iic_clk 	  RCC_APB2Periph_GPIOB	    //需要开启相应总线的时钟
#define    iic_group  GPIOB				        //接口所在分组

/********************************宏定义***********************************/
#define SCL(x)	x ? GPIO_SetBits(GPIOB , scl_pin)  : GPIO_ResetBits(GPIOB , scl_pin)
#define	SDA(x)  x ? GPIO_SetBits(GPIOB , sda_pin) : GPIO_ResetBits(GPIOB , sda_pin)
    


/*************************设置SDA为输入模式***************************/
void SDA_IN()				
{

    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = sda_pin;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;       //上拉输入 
	GPIO_Init(iic_group, &GPIO_InitStructure);           //初始化GPIOB端口
}


/**************************设置SDA为输入模式**********************/
void SDA_OUT()			  
{
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = sda_pin ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(iic_group, &GPIO_InitStructure);           //初始化GPIOB端口


}


/**************************i2c初始化*****************************/
void i2c_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( iic_clk, ENABLE);		     //开启总线时钟

	GPIO_InitStructure.GPIO_Pin = sda_pin|scl_pin ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(iic_group, &GPIO_InitStructure);           //初始化GPIOB端口

}


/**************************I2C起始信号*****************************************/
void start_i2c()
{
	  SDA_OUT();
	  SDA(1);  //SDA=1; 发送起始条件的数据信号
	  SCL(1);	  //SCL=1;
	  delay_us(4);                //起始条件建立时间大于4.7us,延时  
	  SDA(0);  //SDA=0;           /*发送起始信号*/
	  delay_us(5);                // 起始条件锁定时间大于4μs
	  SCL(0);	  //SCL=0;       /*钳住I2C总线，准备发送或接收数据 */
	  
}


/**************************I2C结束信号*******************************************/
void stop_i2c()
{
	  SDA_OUT();
	  SCL(0);
	  SDA(0);  //SDA=0;   //发送结束条件的数据信号
	  delay_us(4);      //发送结束条件的时钟信号
	  SCL(1)	; //SCL=1; 结束条件建立时间大于4μs
	  SDA(1);  //SDA=1; 发送I2C总线结束信号
	  delay_us(4);

}


/*************************************************************
				    接受应答
当返回值为0时表示接收到应答，返回值为1时表示未接受到应答
**************************************************************/
u8 i2c_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();           //SDA设置为输入  
	SDA(1);delay_us(1);	//此时拉高只是为了后续应答的判断，并非是应答机制中必须的。   
	SCL(1);delay_us(1);	 
	while(GPIO_ReadInputDataBit(GPIOB ,sda_pin))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			stop_i2c();
			return 1;
		}
	}
	SCL(0);//时钟输出0 	   
	return 0;  
} 


/*******************************************************************
                 字节数据发送函数               
后面需要常常接iic_Wait_Ack()；函数用于判断是否接收到从机的应答
若未接到应答可能从机出现问题了。
********************************************************************/
void  sendbyte(unsigned char  c)
{
 unsigned char  BitCnt;
  	SDA_OUT(); 
	SCL(0);
 for(BitCnt=0;BitCnt<8;BitCnt++)   //要传送的数据长度为8位
    {
     if((c<<BitCnt)&0x80) SDA(1);  //SDA=1; 判断发送位
     else SDA(0);                
     delay_us(2);
     SCL(1);                      //SCL=1 置时钟线为高，通知被控器开始接收数据位
	 delay_us(2);                 //保证时钟高电平周期大于4μs
     SCL(0);	                  //SCL = 0
    }
    
 
}


/*******************************************************************
                 字节数据接收函数               
执行该函数后需要主机发送 应答信号或非应答信号，用于告诉从机是
否已经成功接受到消息。注意！！！非应答信号并不是什么都不接了 
********************************************************************/    
unsigned char   rcvbyte()
{
  unsigned char  retc;
  unsigned char  BitCnt;
  SDA_IN();
  retc=0; 

  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
                  
        SCL(0);    //SCL=0 置时钟线为低，准备接收数据位
		delay_us(2); //时钟低电平周期大于4.7μs
     	
		SCL(1);	 //SCL=1 置时钟线为高使数据线上数据有效
        delay_us(1);
        retc=retc<<1;
        if(GPIO_ReadInputDataBit(GPIOB , sda_pin)== 1)retc=retc+1; // SDA == 1读数据位,接收的数据位放入retc中 
        delay_us(2);
	
      }

  return(retc);
}


/********************************************************************
                     应答子函数
当a为0时是应答信号，当a为1时是非应答信号，注意！！这是主机发向
从机的信号。
********************************************************************/
void send_ack(u8 a)
{
  SCL(0);
  SDA_OUT();

  if(a==0)
  {
   SDA(0);	    //SDA=0;在此发出应答
  }  
  else 
  {
   SDA(1);      //SDA=1;
  }
  delay_us(3);    
 
  SCL(1);       //SCL=1;	 
  delay_us(4);	//时钟低电平周期大于4μs
 
  SCL(0)	;   //SCL=0; 清时钟线，钳住I2C总线以便继续接收
  delay_us(2); 
 
}


/***************************接受应答********************************/
/***************和之前的等待应答函数是等效的********************/
u8 rcv_ack(void)
{
	
	u8 bit=0;
    SCL(1);                    //拉高时钟线
    delay_us(5);                 //延时
    bit=GPIO_ReadInputDataBit(GPIOB ,sda_pin);                   //读应答信号
    SCL(0);                    //拉低时钟线
    delay_us(5);                 //延时
    return bit;

}








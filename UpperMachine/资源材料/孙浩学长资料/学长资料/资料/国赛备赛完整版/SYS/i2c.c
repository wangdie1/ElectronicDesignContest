/*Ƕ��ʽ��԰stm32 I2C����⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�*/
/*
����Ӧ��������0����Ӧ������ߵ�ƽ�����Ӧ�������ڿ���Ӧ
���ͬʱҲ���뿼�������������������ɴӻ�����
 2013.6.25 */

//SDAΪPB11
//SCLΪPB10

#include"i2c.h"

/*****************************i2cӲ���ӿ�******************************/
/*���Ը�����Ҫ���иı�*/ 
#define    sda_pin    GPIO_Pin_11               //I2C  ���� 
#define    scl_pin    GPIO_Pin_10               //I2C   ʱ�� 
#define    iic_clk 	  RCC_APB2Periph_GPIOB	    //��Ҫ������Ӧ���ߵ�ʱ��
#define    iic_group  GPIOB				        //�ӿ����ڷ���

/********************************�궨��***********************************/
#define SCL(x)	x ? GPIO_SetBits(GPIOB , scl_pin)  : GPIO_ResetBits(GPIOB , scl_pin)
#define	SDA(x)  x ? GPIO_SetBits(GPIOB , sda_pin) : GPIO_ResetBits(GPIOB , sda_pin)
    


/*************************����SDAΪ����ģʽ***************************/
void SDA_IN()				
{

    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = sda_pin;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;       //�������� 
	GPIO_Init(iic_group, &GPIO_InitStructure);           //��ʼ��GPIOB�˿�
}


/**************************����SDAΪ����ģʽ**********************/
void SDA_OUT()			  
{
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = sda_pin ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(iic_group, &GPIO_InitStructure);           //��ʼ��GPIOB�˿�


}


/**************************i2c��ʼ��*****************************/
void i2c_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( iic_clk, ENABLE);		     //��������ʱ��

	GPIO_InitStructure.GPIO_Pin = sda_pin|scl_pin ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;    //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(iic_group, &GPIO_InitStructure);           //��ʼ��GPIOB�˿�

}


/**************************I2C��ʼ�ź�*****************************************/
void start_i2c()
{
	  SDA_OUT();
	  SDA(1);  //SDA=1; ������ʼ�����������ź�
	  SCL(1);	  //SCL=1;
	  delay_us(4);                //��ʼ��������ʱ�����4.7us,��ʱ  
	  SDA(0);  //SDA=0;           /*������ʼ�ź�*/
	  delay_us(5);                // ��ʼ��������ʱ�����4��s
	  SCL(0);	  //SCL=0;       /*ǯסI2C���ߣ�׼�����ͻ�������� */
	  
}


/**************************I2C�����ź�*******************************************/
void stop_i2c()
{
	  SDA_OUT();
	  SCL(0);
	  SDA(0);  //SDA=0;   //���ͽ��������������ź�
	  delay_us(4);      //���ͽ���������ʱ���ź�
	  SCL(1)	; //SCL=1; ������������ʱ�����4��s
	  SDA(1);  //SDA=1; ����I2C���߽����ź�
	  delay_us(4);

}


/*************************************************************
				    ����Ӧ��
������ֵΪ0ʱ��ʾ���յ�Ӧ�𣬷���ֵΪ1ʱ��ʾδ���ܵ�Ӧ��
**************************************************************/
u8 i2c_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();           //SDA����Ϊ����  
	SDA(1);delay_us(1);	//��ʱ����ֻ��Ϊ�˺���Ӧ����жϣ�������Ӧ������б���ġ�   
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
	SCL(0);//ʱ�����0 	   
	return 0;  
} 


/*******************************************************************
                 �ֽ����ݷ��ͺ���               
������Ҫ������iic_Wait_Ack()�����������ж��Ƿ���յ��ӻ���Ӧ��
��δ�ӵ�Ӧ����ܴӻ����������ˡ�
********************************************************************/
void  sendbyte(unsigned char  c)
{
 unsigned char  BitCnt;
  	SDA_OUT(); 
	SCL(0);
 for(BitCnt=0;BitCnt<8;BitCnt++)   //Ҫ���͵����ݳ���Ϊ8λ
    {
     if((c<<BitCnt)&0x80) SDA(1);  //SDA=1; �жϷ���λ
     else SDA(0);                
     delay_us(2);
     SCL(1);                      //SCL=1 ��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
	 delay_us(2);                 //��֤ʱ�Ӹߵ�ƽ���ڴ���4��s
     SCL(0);	                  //SCL = 0
    }
    
 
}


/*******************************************************************
                 �ֽ����ݽ��պ���               
ִ�иú�������Ҫ�������� Ӧ���źŻ��Ӧ���źţ����ڸ��ߴӻ���
���Ѿ��ɹ����ܵ���Ϣ��ע�⣡������Ӧ���źŲ�����ʲô�������� 
********************************************************************/    
unsigned char   rcvbyte()
{
  unsigned char  retc;
  unsigned char  BitCnt;
  SDA_IN();
  retc=0; 

  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
                  
        SCL(0);    //SCL=0 ��ʱ����Ϊ�ͣ�׼����������λ
		delay_us(2); //ʱ�ӵ͵�ƽ���ڴ���4.7��s
     	
		SCL(1);	 //SCL=1 ��ʱ����Ϊ��ʹ��������������Ч
        delay_us(1);
        retc=retc<<1;
        if(GPIO_ReadInputDataBit(GPIOB , sda_pin)== 1)retc=retc+1; // SDA == 1������λ,���յ�����λ����retc�� 
        delay_us(2);
	
      }

  return(retc);
}


/********************************************************************
                     Ӧ���Ӻ���
��aΪ0ʱ��Ӧ���źţ���aΪ1ʱ�Ƿ�Ӧ���źţ�ע�⣡��������������
�ӻ����źš�
********************************************************************/
void send_ack(u8 a)
{
  SCL(0);
  SDA_OUT();

  if(a==0)
  {
   SDA(0);	    //SDA=0;�ڴ˷���Ӧ��
  }  
  else 
  {
   SDA(1);      //SDA=1;
  }
  delay_us(3);    
 
  SCL(1);       //SCL=1;	 
  delay_us(4);	//ʱ�ӵ͵�ƽ���ڴ���4��s
 
  SCL(0)	;   //SCL=0; ��ʱ���ߣ�ǯסI2C�����Ա��������
  delay_us(2); 
 
}


/***************************����Ӧ��********************************/
/***************��֮ǰ�ĵȴ�Ӧ�����ǵ�Ч��********************/
u8 rcv_ack(void)
{
	
	u8 bit=0;
    SCL(1);                    //����ʱ����
    delay_us(5);                 //��ʱ
    bit=GPIO_ReadInputDataBit(GPIOB ,sda_pin);                   //��Ӧ���ź�
    SCL(0);                    //����ʱ����
    delay_us(5);                 //��ʱ
    return bit;

}








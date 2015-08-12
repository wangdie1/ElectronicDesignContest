//-------------------------------------------------------------------------*
// 文件名: visualscope.c                                                          *
// 说  明: visualscope驱动程序文件                                                *
//-------------------------------------------------------------------------*
#include "visualscope.h"
#include "usart.h"
#include "sys.h"
//============================================================================
//函数名称：CRC_CHECK
//函数返回：
//参数说明：
//功能概要：计算CRC校验码
//============================================================================
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++)
    {      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++)
        {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}


//============================================================================
//函数名称：OutPut_Data
//函数返回：
//参数说明：
//功能概要：输出CH通道的数据到上位机
//============================================================================
void VisualScopeUpdate(float data1,float data2,float data3,float data4)
{
  
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0}; 
  u8 i;
  unsigned short CRC16 = 0;

  float OutData[4]={0};
  OutData[0] = data1;
  OutData[1] = data2;
  OutData[2] = data3; 
  OutData[3] = data4;

  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK((unsigned char *)databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
  {
     uart1_send_dat(databuf[i]);
	 //printf(databuf[i]);
  }
}




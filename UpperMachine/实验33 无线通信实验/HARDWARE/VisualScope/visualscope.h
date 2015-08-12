#ifndef _VISUALSCOPE_H
#define _VISUALSCOPE_H

  //3 函数声明
//============================================================================
//函数名称：OutPut_Data
//函数返回：
//参数说明：
//功能概要：输出CH通道的数据到上位机
//============================================================================
void OutPut_Data(void);
  
  
//============================================================================
//函数名称：CRC_CHECK
//函数返回：
//参数说明：
//功能概要：计算CRC校验码
//============================================================================
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);

void VisualScopeUpdate(float data1,float data2,float data3,float data4);
#endif 



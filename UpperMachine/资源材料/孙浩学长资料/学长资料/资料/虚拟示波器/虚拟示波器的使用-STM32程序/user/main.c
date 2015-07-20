/************
  虚拟示波器使用方法
  使用前配置：应该选择破解之后的VisualScope_Crack程序，兼容性选择win95或者98
  然后在Setup->Communication protocol->CRC16设置。同时在Tools->Scom Assistant中点击
  Open，查看是否有数据发过来。要是有，则关闭后叉掉。再点击
  优势：操作比较人性化，可以显示当前状态值。可以不需要延时处理。

***************/

#include"stm32f10x.h"
#include"delay.h"
#include"usart.h" /* printf函数定向输出到串口，所以必须包含这个文件 */
#include"ocsctl.h"
#include<stdio.h>  /* 因为用到了printf函数，所以必须包含这个文件 */
int main(void)
{
   SystemInit();
   delay_init(72);
   InitUart();
 	
   while(1)
   {
       OCS_displayData(10.0,100.0,255.0,1000.9);
	   delay_us(1);								
   }
  
}

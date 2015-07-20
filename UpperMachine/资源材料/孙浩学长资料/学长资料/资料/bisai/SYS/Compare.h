/*嵌入式家园stm32 时钟输入捕获代码库函数版1.0版本 不足之处希望同学们可以多多修改，使程序更
加完善。
作者 孙浩 2013.4.1 */

//定时器2/5时接PA0,PA1,PA2,PA3
//定时器3时接PA6,PA7,PB0,PB1
//定时器4时接PB6,PB7,PB8,PB9

#ifndef __COMPARE_H
#define __COMPARE_H
typedef enum {TIM5_1,TIM5_2,TIM5_3,TIM5_4}COMPARE_type;
void TIM5_GPIO_INIT(COMPARE_type type);
void TIM5_Cap_Init(COMPARE_type type,unsigned int arr,unsigned int psc);
void  Input_Compare_Init(COMPARE_type type);
int Get_H_Pulse(COMPARE_type type);
#endif

/*Ƕ��ʽ��԰stm32 ʱ�����벶�����⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�
���� ��� 2013.4.1 */

//��ʱ��2/5ʱ��PA0,PA1,PA2,PA3
//��ʱ��3ʱ��PA6,PA7,PB0,PB1
//��ʱ��4ʱ��PB6,PB7,PB8,PB9

#ifndef __COMPARE_H
#define __COMPARE_H
typedef enum {TIM5_1,TIM5_2,TIM5_3,TIM5_4}COMPARE_type;
void TIM5_GPIO_INIT(COMPARE_type type);
void TIM5_Cap_Init(COMPARE_type type,unsigned int arr,unsigned int psc);
void  Input_Compare_Init(COMPARE_type type);
int Get_H_Pulse(COMPARE_type type);
#endif

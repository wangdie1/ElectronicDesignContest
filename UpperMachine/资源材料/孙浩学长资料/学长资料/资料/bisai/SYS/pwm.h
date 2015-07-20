/*Ƕ��ʽ��԰stm32 PWM�������⺯����1.0�汾 ����֮��ϣ��ͬѧ�ǿ��Զ���޸ģ�ʹ�����
�����ơ�
���� ��� 2013.4.1 */

//��ʱ��2ʱ��PA0,PA1,PA2,PA3
//��ʱ��3ʱ��PA6,PA7,PB0,PB1
//��ʱ��4ʱ��PB6,PB7,PB8,PB9
#ifndef __PWM_H
#define __PWM_H

#define	use    1
#define nonuse 0

typedef enum {TIM2_1,TIM2_2,TIM2_3,TIM2_4,TIM3_1,TIM3_2,TIM3_3,TIM3_4,TIM4_1,TIM4_2,TIM4_3,TIM4_4}TIMtype;
void pwm_config(TIMtype type);
void pwm_init(TIMtype type);
void pwm_gpio_init(TIMtype type);
void set_pwm_percent(TIMtype type,int percent);  

#endif

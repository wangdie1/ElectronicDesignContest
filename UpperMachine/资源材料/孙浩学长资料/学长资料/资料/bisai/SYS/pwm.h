/*嵌入式家园stm32 PWM输出代码库函数版1.0版本 不足之处希望同学们可以多多修改，使程序更
加完善。
作者 孙浩 2013.4.1 */

//定时器2时接PA0,PA1,PA2,PA3
//定时器3时接PA6,PA7,PB0,PB1
//定时器4时接PB6,PB7,PB8,PB9
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

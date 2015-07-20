#ifndef __CAR_H
#define __CAR_H 			   

#define P   2
#define I	0.5
#define D	0.5
typedef struct my_pid
{
int PreError;
int LastError;
int proportion;
int differ;
int interal;
int setpoint;

}my_pid;

void Dc_motor_init(void);
void Dc_gpio_init(void);
void backward(int  percent);
void forward(int percent);
void turn_left_1(void);
void turn_left_2(void);
void turn_left_3(void);
void turn_left_4(void);
void turn_left_5(void);
void turn_right_1(void);
void turn_right_2(void);
void turn_right_3(void);
void turn_right_4(void);
void turn_right_5(void);
void turn_straight(void);
void car_init(void);
void Pid_Init(my_pid *temp);
int get_inc(my_pid *pid,int nextpoint);

#endif



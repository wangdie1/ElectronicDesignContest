#include <stm32f10x.h>
#include "USART.H"
#include "ADC1.H"
#define ANGLE_BUFFER_SIZE 8
float ANG_Measure(void);
float ANG_Average_Calc(void);
void Clear_Angle_Buffer(void);
void InitAngleBuffer(void);
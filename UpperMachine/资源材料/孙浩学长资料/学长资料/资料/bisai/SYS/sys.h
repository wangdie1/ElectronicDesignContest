#ifndef   __SYS_H
#define	  __SYS_H
 
#include "delay.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"
#include "Compare.h"
#include "car.h"
#include "ADXL345.h"
#include "i2c.h"
#include "bh175.h"
#include "ultrasonic_sensor.h"
#include "color_det.h"
#include "eeprom.h"
#include "adc.h"

void NVIC_CONFIG(void);
void SYS_CONFIG(void);

#endif


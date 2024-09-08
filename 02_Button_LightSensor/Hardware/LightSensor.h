#ifndef __LightSensor_H
#define __LightSensor_H
#include <stm32f10x.h>

void LightSensor_Init(uint16_t GPIO_Pin_Num);
int8_t LightSensor_Bit(void);


#endif

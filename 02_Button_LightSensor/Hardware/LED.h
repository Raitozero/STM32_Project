#ifndef __LED_H
#define __LED_H

#include <stm32f10x.h>

void Led_Init(uint16_t GPIO_Pin_Num);
void Led_Turn(uint16_t GPIO_Pin_Num);

#endif

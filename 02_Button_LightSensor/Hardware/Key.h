#ifndef __KEY_H
#define __KEY_H
#include <stm32f10x.h>

void Key_Init(uint16_t GPIO_Pin_Num);
int8_t Is_Key_Pressed(uint16_t GPIO_Pin_Num);


#endif

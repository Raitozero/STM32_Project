#ifndef __Buzzer_H
#define __Buzzer_H
#include <stm32f10x.h>

void Buzzer_Init(uint16_t GPIO_Pin_Num);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Turn(void);


#endif

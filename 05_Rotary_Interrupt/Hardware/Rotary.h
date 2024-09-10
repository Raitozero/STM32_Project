#ifndef __ROTARY_H
#define __ROTARY_H


void Rotary_Init(void);
uint16_t Rotary_Get_Count(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

#endif

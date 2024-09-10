#ifndef __IRSENSOR_H
#define __IRSENSOR_H

void IRSensor_Init(void);
uint16_t IRSensor_Get_Count(void);
void EXTI15_10_IRQHandler(void);

#endif

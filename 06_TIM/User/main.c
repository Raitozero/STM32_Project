#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t num1, num2;

int main(void)
{
	OLED_Init();
	Internal_Timer_Init();
	ETR_Timer_Init();
	OLED_ShowString(1, 1, "IN_Count: ");
	OLED_ShowString(2, 1, "EXT_Count: ");
	while (1)
	{	
		OLED_ShowNum(1, 11, num1, 3);
		OLED_ShowNum(2, 12, num2, 3);
	}
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET){
		num1++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		num2++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
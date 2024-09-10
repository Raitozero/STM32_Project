#include "stm32f10x.h"                  // Device header

#include "IRSensor.h"
#include "Delay.h"
#include "OLED.h"
#include "Rotary.h"

//uint16_t num;

int main(void)
{
	OLED_Init();
	IRSensor_Init();
	Rotary_Init();

	OLED_ShowString(1, 1, "IR Count: ");
	OLED_ShowString(3, 1, "Rotary Count: ");
	while (1)
	{	
		//num += Rotary_Get_Count();
		OLED_ShowSignedNum(2, 1, IRSensor_Get_Count(), 5);
		OLED_ShowSignedNum(4, 1, Rotary_Get_Count(), 5);
	}
}

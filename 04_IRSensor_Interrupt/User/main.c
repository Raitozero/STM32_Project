#include "stm32f10x.h"                  // Device header

#include "IRSensor.h"
#include "Delay.h"
#include "OLED.h"


int main(void)
{
	OLED_Init();
	IRSensor_Init();
	OLED_ShowString(1,1, "Count Number: ");
	while (1)
	{
		OLED_ShowNum(2, 1, IRSensor_Get_Count(), 5);
	}
}

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();
	OLED_ShowChar(1, 1, 'S');
	OLED_ShowChar(1, 2, 'H');
	OLED_ShowChar(1, 3, 'U');
	OLED_ShowChar(1, 4, ':');
	OLED_ShowString(1, 5, "Hello World!");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	while (1)
	{
		
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main(void){

	Led_Init(GPIO_Pin_0|GPIO_Pin_1); //LEDs are at GPIOA 0&1
	Key_Init(GPIO_Pin_1|GPIO_Pin_11); // Keys are at GPIOB 1&11
	Buzzer_Init(GPIO_Pin_12); //Buzzer at GPIOB 12
	LightSensor_Init(GPIO_Pin_13); // Light sensor is at GPIOB 13
	while(1){
		if(Is_Key_Pressed(GPIO_Pin_1)) Led_Turn(GPIO_Pin_0);
		if(Is_Key_Pressed(GPIO_Pin_11)) Led_Turn(GPIO_Pin_1);
		//默认是上拉，如果有光，那么传感器无电阻，短路pin到GND，那么return 0；相反，无光，有电阻，不会短路，还是1
		if(LightSensor_Bit() == 1) Buzzer_On();
		else Buzzer_Off();
	}
}

#include "LightSensor.h"
#include "Delay.h"
static uint16_t Pin_Num;

void LightSensor_Init(uint16_t GPIO_Pin_Num){
    GPIO_InitTypeDef GPIO_LightSensor_Structrue;
    Pin_Num = GPIO_Pin_Num;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_LightSensor_Structrue.GPIO_Mode = GPIO_Mode_IPU;;
    GPIO_LightSensor_Structrue.GPIO_Pin = GPIO_Pin_Num;
    GPIO_LightSensor_Structrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_LightSensor_Structrue);
}


int8_t LightSensor_Bit(void){
    return GPIO_ReadInputDataBit(GPIOB, Pin_Num);
}

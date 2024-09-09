#include "stm32f10x.h"                  // Device header
#include "IRSensor.h"


uint16_t count;
//GPIO->AFIO->EXTI->NVIC
void IRSensor_Init(void){
    //GPIO Init
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // Do not forget to Enable AFIO Clock
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //AFIO Init: 告诉AFIO 14号通道用GPIOB的pin14
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    //EXTI Init: 设置 下降沿Interrupt
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //触发itr的条件
    EXTI_Init(&EXTI_InitStructure);

    //NVIC Assign Group
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //NVIC Init
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

uint16_t IRSensor_Get_Count(void){
    return count;
}

void EXTI15_10_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line14) == SET){
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) count++;
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}
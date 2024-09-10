#include "stm32f10x.h"                  // Device header
#include "Rotary.h"

/*
explanation:
B端落后A端90度波相位，所以当A从high到low，trigger interrupt时，如果是正转，那么B此时应该为high;
如果是反转为low，这就是EXTI0_IRQHandler的逻辑，其实用这一个interrupt就够了
但这里用B端的去判断正转的情况，原理一样
*/

uint16_t Rotary_Count;

//Rotary: A is at GPIOB_Pin_0, B is at GPIOB_Pin_1;
void Rotary_Init(void){
    //GPIO Init
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // Do not forget to Enable AFIO Clock
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //AFIO Init
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    
    //EXTI Init
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //触发itr的条件
    EXTI_Init(&EXTI_InitStructure);

    //NVIC Assign Group
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    //NVIC Init
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

// uint16_t Rotary_Get_Count(void){
//     uint16_t tmp = Rotary_Count;
//     Rotary_Count = 0;
//     return tmp;
// }

uint16_t Rotary_Get_Count(void){
    return Rotary_Count;
}

void EXTI0_IRQHandler(void){
	if (EXTI_GetITStatus(EXTI_Line0) == SET){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) Rotary_Count--;	
		}
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}
}

void EXTI1_IRQHandler(void){
	if (EXTI_GetITStatus(EXTI_Line1) == SET){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0){
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) Rotary_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
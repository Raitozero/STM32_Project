#include "LED.h"

//Init Led, assuming Led is connected to [GPIOA], take "GPIO_Pin_0 | GPIO_Pin_1 |..."
void Led_Init(uint16_t GPIO_Pin_Num){
    GPIO_InitTypeDef GPIO_LED_Structrue;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_LED_Structrue.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_LED_Structrue.GPIO_Pin = GPIO_Pin_Num;
    GPIO_LED_Structrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_LED_Structrue);
    GPIO_SetBits(GPIOA, GPIO_Pin_Num);
}

void Led_Turn(uint16_t GPIO_Pin_Num){
    uint8_t Read_Bit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_Num);
    Read_Bit == 0? GPIO_WriteBit(GPIOA, GPIO_Pin_Num, Bit_SET):GPIO_WriteBit(GPIOA, GPIO_Pin_Num, Bit_RESET);
}

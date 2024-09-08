#include "Buzzer.h"
static uint16_t Pin_Num;

void Buzzer_Init(uint16_t GPIO_Pin_Num){
    GPIO_InitTypeDef GPIO_Buzzer_Structrue;
    Pin_Num = GPIO_Pin_Num;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_Buzzer_Structrue.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Buzzer_Structrue.GPIO_Pin = GPIO_Pin_Num;
    GPIO_Buzzer_Structrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_Buzzer_Structrue);
    GPIO_SetBits(GPIOB, GPIO_Pin_Num);
}

void Buzzer_On(void){
    GPIO_WriteBit(GPIOB, Pin_Num, Bit_RESET);
}
void Buzzer_Off(void){
    GPIO_WriteBit(GPIOB, Pin_Num, Bit_SET);
}
void Buzzer_Turn(void){
    uint8_t Read_Bit = GPIO_ReadOutputDataBit(GPIOB, Pin_Num);
    Read_Bit == 0? GPIO_WriteBit(GPIOB, Pin_Num, Bit_SET):GPIO_WriteBit(GPIOB, Pin_Num, Bit_RESET);
}

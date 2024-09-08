#include "Key.h"
#include "Delay.h"
//Init Key, assuming Key is connected to [GPIOB], take "GPIO_Pin_0 | GPIO_Pin_1 |..."
void Key_Init(uint16_t GPIO_Pin_Num){
    GPIO_InitTypeDef GPIO_Key_Structrue;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_Key_Structrue.GPIO_Mode = GPIO_Mode_IPU;;
    GPIO_Key_Structrue.GPIO_Pin = GPIO_Pin_Num;
    GPIO_Key_Structrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_Key_Structrue);
}

//check if a key is pressed
int8_t Is_Key_Pressed(uint16_t GPIO_Pin_Num){
    //IPU Mode: default Key_Bit = 1; if pressed, Key_Bit = 0
    uint8_t Key_Bit = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_Num);
    if(!Key_Bit){
        //Delay a moment to avoid button shaking period unstable signal.
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_Num) == 0);// wait for releasing
        Delay_ms(20);
        return 1;
    }
    else return 0;
}

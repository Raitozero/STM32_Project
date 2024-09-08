#include "stm32f10x.h"                  // Device header
#include "Delay.h"
 int main(void){
	 GPIO_InitTypeDef GPIO_LED_Structrue, GPIO_Buzzer_Structure;
	 int i;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 
	 //LED Init
	 GPIO_LED_Structrue.GPIO_Mode = GPIO_Mode_Out_PP;//通用推挽输出
	 GPIO_LED_Structrue.GPIO_Pin = GPIO_Pin_All;
	 GPIO_LED_Structrue.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_LED_Structrue);
	//Buzzer Init
	 GPIO_Buzzer_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Buzzer_Structure.GPIO_Pin = GPIO_Pin_12;
	 GPIO_Buzzer_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_Buzzer_Structure);
	 
	 //GPIO_SetBits(GPIOA, GPIO_Pin_0);
	 //GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	 while(1){
		 //1.WriteBit可以写1位，所以这里指定pin0为低电压
//		 GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
//		 Delay_ms(200);
//		 GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//		 Delay_ms(200);
		 //2. ResetBits()同理
		 //GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		 //GPIO_setBits(GPIOA, GPIO_Pin_0);
		 //3. Write直接写16位，所以用0x0000直接给出想要的16位
		 for(i = 0x0001; i <= 0x0080; i <<= 1){
			GPIO_Write(GPIOA, ~i);
			Delay_ms(400);
		 }
//		 GPIO_Write(GPIOA, ~0x0001);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0002);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0004);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0008);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0010);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0020);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0040);
//		 Delay_ms(200);
//		 GPIO_Write(GPIOA, ~0x0080);
//		 Delay_ms(200);
		 
		 //蜂鸣器
		 GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
		 Delay_ms(100);
		 GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
		 Delay_ms(100);
		 GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
		 Delay_ms(100);
		 GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
		 Delay_ms(500);
	 }
 }
 
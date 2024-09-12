#include "stm32f10x.h"                  // Device header
#include "Timer.h"


void Internal_Timer_Init(void){
    //If we want to use TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    //Choose Internal Clock as the source for TIM3 (default is internal clock, so no problem if not specifified)
    TIM_InternalClockConfig(TIM3);

    //Set Time Base
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //这里是给滤波器分的时钟频率，这里没有影响；选择不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    
    /*
    这里2个参数决定计数时间; Internal Clock 默认72MHz;
    比如这里要定时1s钟，
    1.PSC分频参数为7200-1，分完后，频率为 72MHz/(7200-1+1) = 10000Hz; 也就是10000/second
    2.再计10000个数，就正好可以是1s;
    这里的两个参数，ARR和PSC取值范围为0~65535，也就是16bits的寄存器
    */
    TIM_TimeBaseInitStructure.TIM_Period = 10000-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器功能，按下不表
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    //The pre line TIM_TimeBaseInit() will immediately set bit, thus interrupt which cause the count starting from 1. 
    //Clear it to let the count start from 0
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //打开中断输出控制器

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM3, ENABLE);
}


void ETR_Timer_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Set Time Base
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInitStructure.TIM_Period = 10-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1-1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM2, ENABLE);
}
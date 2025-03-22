#include "timer.h"
#include <stm32f10x_tim.h> 

void timer2_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef timerInit;
    timerInit.TIM_CounterMode = TIM_CounterMode_Up;
    timerInit.TIM_Period = 0xFFFF;
    timerInit.TIM_Prescaler = 72 - 1;
    timerInit.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInit);
    TIM_Cmd(TIM2, ENABLE);
}

void Delay_1ms(unsigned long time_ms) {
    for (unsigned long i = 0; i < time_ms; i++) {
        TIM_SetCounter(TIM2, 0);
        while (TIM_GetCounter(TIM2) < 1000);
    }
}

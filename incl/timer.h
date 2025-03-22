#ifndef TIMER_H
#define TIMER_H

#include <stm32f10x.h>
#include <stm32f10x_tim.h> 

void timer2_Init(void);
void Delay_1ms(unsigned long time_ms); 

#endif

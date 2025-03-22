#ifndef APP_UART_H
#define APP_UART_H

#include <stm32f10x.h>

void UART_Config(void);
void UART_SendChar(char c);
void UART_SendString(const char *str); 

#endif

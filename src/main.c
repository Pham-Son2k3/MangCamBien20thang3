#include "define.h"
#include "app_i2c.h"
#include "bh1750.h"
#include "app_uart.h"
#include "timer.h" 
#include <stdio.h>

int main(void) {
    timer2_Init();
    UART_Config();
    BH1750_Init();

    while (1) {
        float lux = BH1750_Read();
        char buffer[32];
        sprintf(buffer, "Light BH1750: %.2f Lux\n", lux);
        UART_SendString(buffer);
        Delay_1ms(1000);
    }
}

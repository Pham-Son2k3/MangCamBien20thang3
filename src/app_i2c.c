#include "app_i2c.h"
#include <stm32f10x.h>

#define I2C_TIMEOUT 100000

static unsigned char I2C_WaitEvent(I2C_TypeDef* I2Cx, unsigned long event) {
    unsigned long ticks = I2C_TIMEOUT;
    while (!I2C_CheckEvent(I2Cx, event) && ticks) { ticks--; }
    return (ticks > 0) ? 1 : 0;
}

void I2C1_config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x0B;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 200000;

    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
}

void I2C1_write(unsigned char HW_address, unsigned char sub, unsigned char data) {
    unsigned long ticks = I2C_TIMEOUT;
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) { ticks--; }
    if (ticks == 0) return;

    ticks = I2C_TIMEOUT;
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Transmitter);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && ticks) { ticks--; }
    if (ticks == 0) return;

    if (sub != 0xFF) {
        ticks = I2C_TIMEOUT;
        I2C_SendData(I2C1, sub);
        while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) { ticks--; }
        if (ticks == 0) return;
    }

    ticks = I2C_TIMEOUT;
    I2C_SendData(I2C1, data);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) { ticks--; }
    if (ticks == 0) return;

    I2C_GenerateSTOP(I2C1, ENABLE);
}

char I2C1_read(unsigned char HW_address, unsigned char sub) {
    unsigned long ticks = I2C_TIMEOUT;
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) { ticks--; }
    if (ticks == 0) return 0;

    ticks = I2C_TIMEOUT;
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Transmitter);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && ticks) { ticks--; }
    if (ticks == 0) return 0;

    if (sub != 0xFF) {
        ticks = I2C_TIMEOUT;
        I2C_SendData(I2C1, sub);
        while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) { ticks--; }
        if (ticks == 0) return 0;
    }

    ticks = I2C_TIMEOUT;
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) { ticks--; }
    if (ticks == 0) return 0;

    ticks = I2C_TIMEOUT;
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Receiver);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && ticks) { ticks--; }
    if (ticks == 0) return 0;

    ticks = I2C_TIMEOUT;
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) && ticks) { ticks--; }
    if (ticks == 0) return 0;

    char data = I2C_ReceiveData(I2C1);
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    return data;
}

void I2C1_read_buf(unsigned char HW_address, unsigned char sub, unsigned char *p_buf, unsigned char buf_size) {
    unsigned long ticks = I2C_TIMEOUT;
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) { ticks--; }
    if (ticks == 0) return;

    ticks = I2C_TIMEOUT;
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Transmitter);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && ticks) { ticks--; }
    if (ticks == 0) return;

    if (sub != 0xFF) {
        ticks = I2C_TIMEOUT;
        I2C_SendData(I2C1, sub);
        while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) { ticks--; }
        if (ticks == 0) return;
    }

    ticks = I2C_TIMEOUT;
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) { ticks--; }
    if (ticks == 0) return;

    ticks = I2C_TIMEOUT;
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Receiver);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) && ticks) { ticks--; }
    if (ticks == 0) return;

    for (unsigned char i = 0; i < buf_size - 1; i++) {
        ticks = I2C_TIMEOUT;
        while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) && ticks) { ticks--; }
        if (ticks == 0) return;
        p_buf[i] = I2C_ReceiveData(I2C1);
    }

    ticks = I2C_TIMEOUT;
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    while (!I2C_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) && ticks) { ticks--; }
    if (ticks == 0) return;
    p_buf[buf_size - 1] = I2C_ReceiveData(I2C1);

    I2C_GenerateSTOP(I2C1, ENABLE);
}
#include "bh1750.h"
#include "app_i2c.h"

#define BH1750_I2C_ADDR (BH1750_ADDR << 1) 

void BH1750_Init(void) {
    I2C1_config();
    I2C1_write(BH1750_I2C_ADDR, 0xFF, BH1750_POWER_ON);
    I2C1_write(BH1750_I2C_ADDR, 0xFF, BH1750_ONE_H_MODE); 
}

float BH1750_Read(void) {
    unsigned char tmp8[2] = {0};
    I2C1_read_buf(BH1750_I2C_ADDR, BH1750_ONE_H_MODE, tmp8, 2);
    unsigned int raw = (tmp8[0] << 8) | tmp8[1]; 
    return (float)raw / 1.2;
}

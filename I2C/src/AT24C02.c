//
// Created by dingrui on 2023/1/18.
//

#include "AT24C02.h"
#include "I2C.h"

/**
 * @brief 往AT24C02写数据
 * @param addr AT24C02地址
 * @param dat 数据
 */
void e2prom_write_one_byte(u8 addr, u8 dat)
{
    i2c_start();
    i2c_write_byte(0xa0);
    i2c_wait_ack();
    i2c_write_byte(addr);
    i2c_wait_ack();
    i2c_write_byte(dat);
    i2c_wait_ack();
    i2c_stop();
    delay_ms(10);
}

/**
 * @brief 从e2prom读取数据
 * @param addr e2prom地址
 * @return
 */
u8 e2prom_read_one_byte(u8 addr)
{
    i2c_start();
    i2c_write_byte(0xa0);
    i2c_wait_ack();
    i2c_write_byte(addr);
    i2c_wait_ack();
    i2c_start();
    i2c_write_byte(0xa1);
    i2c_wait_ack();
    u8 ret = i2c_read_byte(SLAVE_SEND_STOP);
    i2c_stop();
    return ret;
}
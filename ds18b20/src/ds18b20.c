//
// Created by dingrui on 2023/1/27.
//

#include "ds18b20.h"

void ds18b20_reset()
{
    DS18B20_PORT = 0;
    delay_10us(75);
    DS18B20_PORT = 1;
    delay_10us(2);
}

/**
 * @brief 检测DS18B20是否存在
 * @return 1:未检测到DS18B20的存在 0:存在
 */
u8 ds18b20_check()
{
    u8 delay = 0;
    while (DS18B20_PORT && delay < 20) // 等待DQ为低电平
    {
        delay++;
        delay_10us(1);
    }
    if (delay >= 20) return 1; // 超时
    else delay = 0;
    while ((!DS18B20_PORT) && delay < 20) // 等待DQ为高电平
    {
        delay++;
        delay_10us(1);
    }
    if (delay >= 20) return 1; // 超时
    return 0;
}

/**
 * @brief 初始化DS18B20的IO口DQ 同时检测DS的存在
 * @return 1:不存在 0:存在
 */
u8 ds18b20_init()
{
    ds18b20_reset();
    return ds18b20_check();
}

// 写0时序
void ds18b20_write_0()
{
    DS18B20_PORT = 0;
    delay_10us(6);
    DS18B20_PORT = 1;
    delay_10us(1);
}

// 写1时序
void ds18b20_write_1()
{
    DS18B20_PORT = 0;
    delay_10us(1);
    DS18B20_PORT = 1;
    delay_10us(6);
}

void ds18b20_write_byte(u8 dat)
{
    for (int i = 0; i < 8; ++i)
    {
        u8 tmp = (dat >> i) & 0x01;
        if (tmp)
            ds18b20_write_1();
        else ds18b20_write_0();
    }
}

u8 ds18b20_read_bit()
{
    u8 ret = 0;
    DS18B20_PORT = 0;
    delay_10us(1);
    if (DS18B20_PORT) ret = 1; // 读到1
    else ret = 0; // 读到0
    delay_10us(5);
    return ret;
}

// 读字节 低位->高位
u8 ds18b20_read_byte()
{
    u8 ret = 0;
    for (int i = 0; i < 8; ++i)
    {
        u8 tmp = ds18b20_read_bit();
        ret >>= 1;
        ret |= (tmp << 7);
    }
    return ret;
}

/**
 * @brief 开始温度转换
 */
void ds18b20_start()
{
    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0x44);
}

float ds18b20_read_temperature()
{
    ds18b20_start();
    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0xbe);
    u8 lo = ds18b20_read_byte();
    u8 hi = ds18b20_read_byte();
    u16 value = 0;
    value |= hi;
    value << 8;
    value |= lo;
    float ans = 0;
    if ((value & 0xf800) == 0xf800) // 高5位符号位
    {
        value = (~value) + 1;
        ans = value * (-0.0625);
    } else ans = value * 0.0625;
    return ans;
}
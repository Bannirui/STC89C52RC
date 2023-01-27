//
// Created by dingrui on 2023/1/27.
//

#include "ds1302.h"

// 秒分时日月周年
u8 g_write_rtc_addr[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 g_read_rtc_addr[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};

// 2023-01-27 14-51-47
u8 g_ds1302_time[7] = {0x47, 0x50, 0x13, 0x27, 0x01, 0x05, 0x23};

/**
 * @brief 单字节写
 * @param op 控制命令
 * @param dat 数据
 */
void ds1302_write_byte(u8 op, u8 dat)
{
    DS1302_RST = 0;
    delay_10us(1);
    DS1302_CLK = 0;
    delay_10us(1);
    // 指令写入 低位->高位
    for (int i = 0; i < 8; ++i)
    {
        DS1302_IO = (op >> i) & 0x01;
        DS1302_CLK = 1;
        delay_10us(1);
        DS1302_CLK = 0;
        delay_10us(1);
    }
    // 写入数据
    for (int i = 0; i < 8; ++i)
    {
        DS1302_IO = (dat >> i) & 0x01;
        DS1302_CLK = 1;
        delay_10us(1);
        DS1302_CLK = 0;
        delay_10us(1);
    }
    DS1302_RST = 0;
}

/**
 * @brief 单字节读
 * @param op 命令
 * @return
 */
u8 ds1302_read_byte(u8 op)
{
    DS1302_RST = 0;
    delay_10us(1);
    DS1302_CLK = 0;
    delay_10us(1);
    DS1302_RST = 1;
    delay_10us(1);
    for (int i = 0; i < 8; ++i)
    {
        DS1302_IO = (op >> 1) & 0x01;
        DS1302_CLK = 1;
        delay_10us(1);
        DS1302_CLK = 0;
        delay_10us(1);
    }
    u8 ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        ans = (ans >> 1) | (DS1302_IO << 7);
        DS1302_CLK = 1;
        delay_10us(1);
        DS1302_CLK = 0;
        delay_10us(1);
    }
    DS1302_RST = 0;
    delay_10us(1);

    DS1302_CLK = 1;
    delay_10us(1);
    DS1302_IO = 0;
    delay_10us(1);
    DS1302_IO = 1;
    delay_10us(1);
    return ans;
}

void ds1302_init()
{
    // 关闭写保护功能
    ds1302_write_byte(0x8e, 0x00);
    for (int i = 0; i < 7; ++i)
    {
        ds1302_write_byte(g_write_rtc_addr[i], g_ds1302_time[i]);
    }
    // 打开写保护
    ds1302_write_byte(0x8e, 0x80);
}

void ds1302_read_time()
{
    for (int i = 0; i < 7; ++i)
        g_ds1302_time[i] = ds1302_read_byte(g_read_rtc_addr[i]);
}
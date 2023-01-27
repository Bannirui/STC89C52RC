//
// Created by dingrui on 2023/1/27.
//

#include "ired.h"

// 红外接收的数据
// 地址码 地址反码 控制码 控制反码
u8 g_ired_data[4];

/**
 * @brief 配置外部中断
 */
void ired_init()
{
    /**
     * 0 低电平触发
     * 1 下降沿触发
     */
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    IRED = 1;
}

// 外部中断服务函数
void ired() __interrupt(0)
{
    if (IRED == 0)
    {
        // 引导码 9ms低电平
        u16 delay_cnt = 1000;
        while (!IRED && delay_cnt)
        {
            delay_10us(1);
            delay_cnt--;
            if (delay_cnt == 0) return;
        }
        if (IRED)
        {
            // 4.5ms高电平
            delay_cnt = 500;
            while (IRED && delay_cnt)
            {
                delay_10us(1);
                delay_cnt--;
                if (delay_cnt == 0) return; // 不是正确的引导信号
            }
            // 数据接收 32位 4个字节
            for (int i = 0; i < 4; ++i) // 4个字节
            {
                for (int j = 0; j < 8; ++j) // 每个字节8bit
                {
                    // 位0 0.56ms低电平 1.125ms周期
                    // 位1 0.56ms低电平 2.25ms周期
                    delay_cnt = 60;
                    while (IRED == 0 && delay_cnt)
                    {
                        delay_10us(1);
                        delay_cnt--;
                        if (delay_cnt == 0) return; // 干扰信号
                    }
                    u8 ired_high_time = 0;
                    while (IRED)
                    {
                        delay_10us(10);
                        ired_high_time++;
                        if (ired_high_time >= 20) return; // 2ms高电平
                    }
                    g_ired_data[i] >>= 1;
                    if (ired_high_time >= 8) // 判定为位1
                        g_ired_data[i] |= 0x80;
                }
            }
        }
        // 数据校验 控制码 控制反码
        if (g_ired_data[2] != ~g_ired_data[3])
        {
            for (int i = 0; i < 4; ++i)
                g_ired_data[i] = 0;
            return;
        }
    }
}
//
// Created by dingrui on 2023/1/14.
//

#include "74HC595.h"
#include <mcs51/8052.h>
#include "delay.h"

/**
 * 74HC595芯片扩展IO
 * 实现LED点阵的滚动
 * 点阵的阴极连接的是P0端口 使之为低电平
 * 点阵的阳极是74HC595芯片的输出 使之为高电平就可以点亮LED
 * DP[h...a]依次输出高电平
 * 芯片的使能引脚OE为低电平 让芯片能工作
 * 输入为3个引脚 P3.5 P3.6 P3.4
*/

// 74HC595的3个输入引脚
#define SRCLK P3_6
#define rclk P3_5 // 8052头文件中已经定义过RCLK
#define SER P3_4

void hc_595_write_data(unsigned char dat)
{
    for (int i = 7; i >= 0; i--)
    {
        // SER是芯片输入引脚 SRCLK上升沿 将SER写入芯片移位寄存器中 将dat从高位->低位依次通过SER写入芯片的寄存器
        SER = ((dat >> i) & 1);
        SRCLK = 0;
        delay_1_us_cnt(10);
        SRCLK = 1;
        delay_1_us_cnt(10);
    }
    // RCLK上升沿 将8个移位寄存器中数据一次性写入到存储器中
    rclk = 0;
    delay_1_us_cnt(10);
    rclk = 1;
}
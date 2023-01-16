//
// Created by dingrui on 2023/1/11.
//

#include "led.h"
#include <mcs51/8052.h>
#include "delay.h"

// LED GND引脚
#define LED1 P2_0

// P2口有8个控制端口[P2.0 ... P2.7]
#define LED_PORT P2

// 给LED连接的单片机引脚一个低电平 跟VCC高电平形成电压差 LED有电流 被点亮
void on_LED1()
{
    LED1 = 0; // P2.0管脚输出一个低电平
}

void off_LED1()
{
    LED1 = 1; // P2.0管脚输出一个高电平
}

void on_off_led1()
{
    on_LED1();
    delay_1_ms_cnt(1000);
    off_LED1();
    delay_1_ms_cnt(1000);
}

// [led1...led8]跑马灯
void horse_race_lamp()
{
    // LED1...LED7流水灯就是每个LED依次点亮一会
    //        P2.7 P2.6 P2.5 P2.4 P2.3 P2.2 P2.1 P2.0
    // LED1亮   1    1    1    1    1    1    1    0     0xfe
    // LED2亮   1    1    1    1    1    1    0    1     0xfd
    // LED3亮   1    1    1    1    1    0    1    1     0xfb
    // LED4亮   1    1    1    1    0    1    1    1     0xf7
    // LED5亮   1    1    1    0    1    1    1    1     0xef
    // LED6亮   1    1    0    1    1    1    1    1     0xdf
    // LED7亮   1    0    1    1    1    1    1    1     0xbf
    // LED8亮   0    1    1    1    1    1    1    1     0x7f
    unsigned char states[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
    for (unsigned char i = 0; i < 8; i++)
    {
        LED_PORT = ~(0x01 << i);
        // 如果没有能力通过移位操作 可以粗暴的枚举端口输出电平状态状态
        // LED_PORT = states[i];
        delay_1_ms_cnt(400);
    }
}
//
// Created by dingrui on 2023/1/11.
//

#include "led.h"
#include "delay.h"

// LED GND引脚
#define LED1 P2_0

// P2口有8个控制端口
#define LED P2

// 给LED连接的单片机引脚一个低电平 跟VCC高电平形成电压差 LED有电流 被点亮
void on_LED1()
{
    LED1 = 0;
}

void off_LED1()
{
    LED1 = 1;
}

void on_off_led1()
{
    on_LED1();
    delay_20ms(50);
    off_LED1();
    delay_20ms(50);
}


// [led1...led8]跑马灯
void horse_race_lamp()
{
    for (unsigned char i = 0; i < 8; i++)
    {
        LED = ~(0x01 << i);
        delay_20ms(10);
    }
}
//
// Created by dingrui on 2023/1/11.
//

#include "beep.h"
#include <mcs51/8052.h>
#include "delay.h"

// ULN2003芯片驱动来放大电流
// 蜂鸣器连接着ULN2003 其引脚对应着单片机的P2.5管脚
// 芯片扮演的角色类似非门 单片机P2.5输出高电平则BEEP输出低电平 单片机P2.5输出低电平则BEEP输出高电平
// 该蜂鸣器是无源蜂鸣器 需要提供一定频率的脉冲即高低电平
#define BEEP P2_5

void beep_one()
{
    delay_20ms(50);
    BEEP = !BEEP; // 交叉高低电平产生脉冲
}

void beep(unsigned cnt)
{
    while (cnt--)
    {
        beep_one();
    }
}
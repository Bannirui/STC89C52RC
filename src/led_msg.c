//
// Created by dingrui on 2023/1/11.
//

#include "led_msg.h"
#include <mcs51/8052.h>
#include "delay.h"

// 数码管LED8的管脚控制段选
#define SMG_DP_PORT_A P0

// 数码管的段选a-dp连接在74HC245驱动芯片上
// 芯片由P0口的[P0.0...P0.7]控制
// 每个数码管的段选由P0控制 给定真值就可以进行显示
#define SMG_DP_PORT P0

// 38译码器的输入[P2.2...P2.4] 定义了数码管的位选
//    P2.4 P2.3 P2.2   十进制  Y编号 LED编号
//      0    0    0      0     Y0   LED1
//      0    0    1      1     Y1   LED2
//      0    1    0      2     Y2   LED3
//      0    1    1      3     Y3   LED4
//      1    0    0      4     Y4   LED5
//      1    0    1      5     Y5   LED6
//      1    1    0      6     Y6   LED7
//      1    1    1      7     Y7   LED8   单片机默认起始状态就是高电平1
#define LSC P2_4
#define LSB P2_3
#define LSA P2_2

// 共阴数码管真值表
// [0..9 A...F 不显示]
unsigned char g_smg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39,
                                0x5e, 0x79, 0x71, 0x00};

void static_led_msg_display_0()
{
    SMG_DP_PORT_A = g_smg_code[1]; // 输出段码
}

void static_led_msg_display()
{
    // 数码管led8轮流显示[0...9 A...F 不显示]
    for (int i = 0; i < 17; ++i)
    {
        SMG_DP_PORT_A = g_smg_code[i];
        delay_1_ms_cnt(1000);
    }
}

void dynamic_led_msg_display()
{
    for (unsigned char i = 0; i < 8; ++i)
    {
        // 位选 控制哪个LED数码管点亮
        switch (i)
        {
            case 0:
                LSC = 1;
                LSB = 1;
                LSA = 1;
                break; // 111->7 LED8被点亮
            case 1:
                LSC = 1;
                LSB = 1;
                LSA = 0;
                break; // 110->6 LED7被点亮
            case 2:
                LSC = 1;
                LSB = 0;
                LSA = 1;
                break; // 101->5 LED6被点亮
            case 3:
                LSC = 1;
                LSB = 0;
                LSA = 0;
                break; // 100->4 LED5被点亮
            case 4:
                LSC = 0;
                LSB = 1;
                LSA = 1;
                break; // 011->3 LED4被点亮
            case 5:
                LSC = 0;
                LSB = 1;
                LSA = 0;
                break; // 010->2 LED3被点亮
            case 6:
                LSC = 0;
                LSB = 0;
                LSA = 1;
                break; // 001->1 LED2被点亮
            case 7:
                LSC = 0;
                LSB = 0;
                LSA = 0;
                break; // 000->0 LED1被点亮
        }
        // 数码管段选
        // [LED8...LED1]分别显示[0...7]
        SMG_DP_PORT = g_smg_code[i];
        // 单个数码管显示-不显示延时 只要延时小于人类肉眼的余晖阈值 人类就感知不到刷新
        // 间隔的两个lED之间的延时 8个LED灯总共有7个延时 总延时要在余晖效应之间 控制在20ms内
        // 如果不设置延时 那么数码管整体显示的亮度就会偏暗
        delay_1_ms_cnt(1);
        SMG_DP_PORT = g_smg_code[16]; // 不显示 消影作用 消除下一个数码管段选对上一个数码管显示的残影影响
    }
}
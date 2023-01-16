//
// Created by dingrui on 2023/1/14.
//

#include "switch.h"
#include <mcs51/8052.h>
#include "delay.h"

// 按键管脚
// 读取管脚的输入判断按键状态
// 按键按下 管脚输入为低电平
// 按键弹起 管脚输入为高电平
#define K1 P3_1
#define K2 P3_0
#define K3 P3_2
#define K4 P3_3

// [D1...D4] led管脚
#define LED1 P2_0
#define LED2 P2_1
#define LED3 P2_2
#define LED4 P2_3

#define KEY1_PRESS 1<<0
#define KEY2_PRESS 1<<2
#define KEY3_PRESS 1<<3
#define KEY4_PRESS 1<<4
#define KEY_UN_PRESS 0

/**
 * @brief [K1...K4]4个独立按键状态检测
 *        按键2个引脚一端连着P3端口 一端连着GND
 *        P3端口内部有上拉电阻 也就意味着默认情况下P3输出为高电平
 *        按键如果被按下 整条电路导通 P3的输出为低电平
 *        按键如果没按下 整条电路断开 P3的输出为高电平
 * @param mode 检测模式 mode为1标识可以连续检测 mode为0标识只能单次检测
 * @return K1按下返回K1的指定值
 *         K2按下返回K2的指定值
 *         K3按下返回K3的指定值
 *         K4按下返回K4的指定值
 *         都没有按下返回指定值
 */
unsigned char key_status_scan(unsigned char mode)
{
    static unsigned char key = 1;
    if (mode) key = 1;
    if (key == 1 && (K1 == 0 || K2 == 0 || K3 == 0 || K4 == 0))
    {
        // 按键管脚低电平 说明按键被按下
        delay_1_ms_cnt(10); // 机械按键的消抖处理
        key = 0;
        if (K1 == 0) return KEY1_PRESS;
        if (K2 == 0) return KEY2_PRESS;
        if (K3 == 0) return KEY3_PRESS;
        if (K4 == 0) return KEY4_PRESS;
    } else
    {
        key = 1;
    }
    return KEY_UN_PRESS;
}

void switch_ctl_led()
{
    unsigned char switch_status = key_status_scan(0);
    // 8个LED共阳极连接着P2端口 其内部有上拉电阻 即默认输出高电平 因此检测到开关被按下 给LED的阴极输出低电平即可点亮led
    if (switch_status == KEY1_PRESS) LED1 = !LED1; // K1按下 点亮D1
    if (switch_status == KEY2_PRESS) LED2 = !LED2; // K2按下 点亮D2
    if (switch_status == KEY3_PRESS) LED3 = !LED3; // K3按下 点亮D3
    if (switch_status == KEY4_PRESS) LED4 = !LED4; // K4按下 点亮D4
}
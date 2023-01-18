//
// Created by dingrui on 2023/1/18.
//
#pragma once

#include "public.h"

// 按键管脚
// 读取管脚的输入判断按键状态
// 按键按下 管脚输入为低电平
// 按键弹起 管脚输入为高电平
#define K1 P3_1
#define K2 P3_0
#define K3 P3_2
#define K4 P3_3

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
u8 key_status_scan(u8 mode);
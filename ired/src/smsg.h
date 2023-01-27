//
// Created by dingrui on 2023/1/18.
//

#pragma once

#include "public.h"

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

// 数码管的段选a-dp连接在74HC245驱动芯片上
// 芯片由P0口的[P0.0...P0.7]控制
// 每个数码管的段选由P0控制 给定真值就可以进行显示
#define SMG_DP_PORT P0

// 共阴数码管真值表
// [0..9 A...F 不显示]
extern u8 g_smg_code[17];

void smsg_display(u8 pos, u8 dat[]);

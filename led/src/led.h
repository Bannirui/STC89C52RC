//
// Created by dingrui on 2023/1/11.
//

#ifndef STC89C52RC_LED_H
#define STC89C52RC_LED_H

#include <mcs51/8052.h>

// 操作led1 点亮-熄灭
extern void on_off_led1();

// [led1...led8]跑马灯
extern void horse_race_lamp();

#endif //STC89C52RC_LED_H

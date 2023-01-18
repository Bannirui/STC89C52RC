//
// Created by dingrui on 2023/1/18.
//

#include "key.h"

u8 key_status_scan(u8 mode)
{
    static unsigned char key = 1;
    if (mode) key = 1;
    if (key == 1 && (K1 == 0 || K2 == 0 || K3 == 0 || K4 == 0))
    {
        // 按键管脚低电平 说明按键被按下
        // 机械按键的消抖处理
        delay_ms(10);
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
//
// Created by dingrui on 2023/1/14.
//

#include "led_matrix.h"
#include "74HC595.h"
#include "delay.h"
#include <mcs51/8052.h>

// 点阵的阴极
#define LED_MATRIX_COL_PORT P0

// 74HC595芯片的SER输入
unsigned char g_74hc595_ser_in[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void scroll_led_matrix_up_2_down()
{
    LED_MATRIX_COL_PORT = 0x00; // P0端口输入低电平
    for (int i = 0; i < 8; ++i)
    {
        hc_595_write_data(0x00); // 消影 关闭led点阵
        hc_595_write_data(g_74hc595_ser_in[i]); // 点亮行
        delay_1_ms_cnt(30); // 大于余晖效应
    }
}
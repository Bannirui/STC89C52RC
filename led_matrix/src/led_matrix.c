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
    LED_MATRIX_COL_PORT = 0x00; // 使P0端口输入低电平 led的阴极连接着P0端口
    // led阳极的8个行上的引脚连接着74HC595芯片的输出 从上之下为高位->低位
    // 芯片OE使能为低电平 连接着J24端子 让J24端子的GND和OE直连使芯片工作
    for (int i = 0; i < 8; ++i)
    {
        hc_595_write_data(0x00); // 消影 关闭led点阵
        hc_595_write_data(g_74hc595_ser_in[i]); // 通过芯片串转并输出某一行的高电平 点亮行
        delay_1_ms_cnt(2000); // 大于余晖效应
    }
}

void on_left_top()
{
    LED_MATRIX_COL_PORT = 0x7f; // 使P0口输出
    hc_595_write_data(0x80); // 芯片SER输入
}

// 点阵上显示0 行上电平输出 列上电平输出
unsigned char g_img_0_row_output[] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};
unsigned char g_img_0_col_output[] = {0xff, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xff};

void display_img_0()
{
    // 扫描8列
    for (int i = 0; i < 8; ++i)
    {
        LED_MATRIX_COL_PORT = g_img_0_col_output[i]; // 使P0端口输出
        hc_595_write_data(g_img_0_row_output[i]); // 使595芯片输出
        delay_1_ms_cnt(1); // 延时保证稳定显示
        hc_595_write_data(0x00); // 消影
    }
}
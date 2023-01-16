//
// Created by dingrui on 2023/1/14.
//

/**
 * 矩阵式按键
 * 独立式按键的引脚一端连接着GPIO 一端连接着GND
 * 矩阵式按键中每个按键两端都连接着GPIO
 * 以m*n矩阵排列方式
 * m行每一行连接着一个GPIO 该行上所有列按键的一个引脚并联
 * n列每一列连接着一个GPIO 该列上所有行按键的一个引脚并联
 * 因此只要m+n个控制口即可
 *
 * 至于判断哪个按键被按下 有两种方式
 * 1 行列式扫描
 * 2 线翻转法
*/
#include "switch_matrix.h"
#include <mcs51/8052.h>
#include "delay.h"
#include "led_msg.h"

// 按键矩阵端口
#define KEY_MATRIX_PORT P1

//           列1  列2  列3  列4
//          P1.3 P1.2 P1.1 P1.0
// 行1 P1.7  S1   S2   S3   S4
// 行2 P1.6  S5   S6   S7   S8
// 行3 P1.5  S9   S10  S11  S12
// 行4 P1.4  S13  S14  S15  S16

/**
 * @brief 行列式扫描法
 * @return 返回值0标识没有按键被按下 有效编号[1...16]
 */
unsigned char row_col_scan()
{
    /**
     * 第1列输出低电平 1111 0111 检测4行哪些输入是低电平 就是哪个按键被按下
     * 第2列输出低电平 1111 1011 检测4行哪些输入是低电平 就是哪个按键被按下
     * 第3列输出低电平 1111 1101 检测4行哪些输入是低电平 就是哪个按键被按下
     * 第4列输出低电平 1111 1110 检测4行哪些输入是低电平 就是哪个按键被按下
     */
    unsigned char ans = 0; // 按键编号

    KEY_MATRIX_PORT = 0xf7; // 使第1列输出为低电平 1111 0111
    if (KEY_MATRIX_PORT != 0xf7)
    {
        // 第1列上有按键被按下
        delay_1_ms_cnt(10); // 消抖
        switch (KEY_MATRIX_PORT)
        {
            case 0x77: // 第1行的按键被按下 0111 0111
                ans = 1; // 第1行第1列编号S1
                break;
            case 0xb7: // 第2行的按键被按下 1011 0111
                ans = 5; // 第2行第1列编号S5
                break;
            case 0xd7: // 第3行的按键被按下 1101 0111
                ans = 9; // 第3行第1列编号S9
                break;
            case 0xe7: // 第4行的按键被按下 1110 0111
                ans = 13; // 第4行第1列编号S13
                break;
        }
        while (KEY_MATRIX_PORT != 0xf7); // 等待按键松开
    }

    KEY_MATRIX_PORT = 0xfb; // 使第2列输出为低电平 1111 1011
    if (KEY_MATRIX_PORT != 0xfb)
    {
        // 第2列上有按键被按下
        delay_1_ms_cnt(10); // 消抖
        switch (KEY_MATRIX_PORT)
        {
            case 0x7b: // 第1行的按键被按下 0111 1011
                ans = 2; // 第1行第2列编号S2
                break;
            case 0xbb: // 第2行的按键被按下 1011 1011
                ans = 6; // 第2行第2列编号S6
                break;
            case 0xdb: // 第3行的按键被按下 1101 1011
                ans = 10; // 第3行第2列编号S10
                break;
            case 0xeb: // 第4行的按键被按下 1110 1011
                ans = 16; // 第4行第2列编号S14
                break;
        }
        while (KEY_MATRIX_PORT != 0xfb); // 等待按键松开
    }

    KEY_MATRIX_PORT = 0xfd; // 使第3列输出为低电平 1111 1101
    if (KEY_MATRIX_PORT != 0xfd)
    {
        // 第3列上有按键被按下
        delay_1_ms_cnt(10); // 消抖
        switch (KEY_MATRIX_PORT)
        {
            case 0x7d: // 第1行的按键被按下 0111 1101
                ans = 3; // 第1行第3列编号S3
                break;
            case 0xbd: // 第2行的按键被按下 1011 1101
                ans = 7; // 第2行第3列编号S7
                break;
            case 0xdd: // 第3行的按键被按下 1101 1101
                ans = 11; // 第3行第3列编号S11
                break;
            case 0xed: // 第4行的按键被按下 1110 1101
                ans = 15; // 第4行第3列编号S15
                break;
        }
        while (KEY_MATRIX_PORT != 0xfd); // 等待按键松开
    }

    KEY_MATRIX_PORT = 0xfe; // 使第4列输出为低电平 1111 1110
    if (KEY_MATRIX_PORT != 0xfe)
    {
        // 第4列上有按键被按下
        delay_1_ms_cnt(10); // 消抖
        switch (KEY_MATRIX_PORT)
        {
            case 0x7e: // 第1行的按键被按下 0111 1110
                ans = 4; // 第1行第4列编号S4
                break;
            case 0xbe: // 第2行的按键被按下 1011 1110
                ans = 8; // 第2行第4列编号S8
                break;
            case 0xde: // 第3行的按键被按下 1101 1110
                ans = 12; // 第3行第4列编号S12
                break;
            case 0xee: // 第4行的按键被按下 1110 1110
                ans = 16; // 第4行第4列编号S16
                break;
        }
        while (KEY_MATRIX_PORT != 0xfe); // 等待按键松开
    }

    return ans;
}

/**
 * @brief 线翻转法
 * @return 返回值0标识没有按键被按下 有效编号[1...16]
 */
unsigned char flip_scan()
{
    static unsigned char ans = 0; // 被按下的按键序号[1...16]
    // 行输出低电平测试列
    KEY_MATRIX_PORT = 0x0f;
    if (KEY_MATRIX_PORT != 0x0f)
    {
        delay_1_ms_cnt(10); // 消抖
        // 测试列 通过判断低4位哪个为低电平0 确定按键在哪列上
        switch (KEY_MATRIX_PORT)
        {
            case 0x07: // 0000 0111 说明被按下的按键在第1列
                ans = 1;
                break;
            case 0x0b: // 0000 1011 说明被按下的按键在第2列
                ans = 2;
                break;
            case 0x0d: // 0000 1101 说明被按下的按键在第3列
                ans = 3;
                break;
            case 0x0e: // 0000 1110 说明被按下的按键在第4列
                ans = 4;
                break;
        }
        if (ans == 0) return ans; // 没有按键被按下
        // 列输出低电平测试行
        KEY_MATRIX_PORT = 0xf0;
        switch (KEY_MATRIX_PORT)
        {
            case 0x70: // 0111 0000 第1行
                ans = ans + (4 * 0);
                break;
            case 0xb0: // 1011 0000 第2行
                ans = ans + (4 * 1);
                break;
            case 0xd0: // 1101 0000 第3行
                ans = ans + (4 * 2);
                break;
            case 0xe0: // 1110 0000 第4行
                ans = ans + (4 * 3);
                break;
        }
        while (KEY_MATRIX_PORT != 0xf0); // 等待按键松开
    }
    return ans;
}

void print_pressed_key_no()
{
    // 按键矩阵中被按下的按键编号
    unsigned char key_no = 0;
    // key_no = row_col_scan(); // 行列扫描
    key_no = flip_scan(); // 线性翻转
    if (key_no == 0) return;
    static_led_msg_display_0(g_smg_code[key_no - 1]); // 数码管SMG1第一个数码管显示内容
}
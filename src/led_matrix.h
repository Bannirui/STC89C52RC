//
// Created by dingrui on 2023/1/14.
//

#pragma once

/**
 * @brief 从上至下方向按行滚动点亮led
 *        led点阵阴极连接P0端口 全部输出低电平
 *        从上至下为[A1...A8]分别连接着74HC595芯片的[DPh...DPa]
 *                   DPh DPg DPf DPe DPd DPc DPb DPa    芯片SER输入
 *        第1行点亮    1   0   0   0   0   0   0   0        0x80
 *        第2行点亮    0   1   0   0   0   0   0   0        0x40
 *        第3行点亮    0   0   1   0   0   0   0   0        0x20
 *        第4行点亮    0   0   0   1   0   0   0   0        0x10
 *        第5行点亮    0   0   0   0   1   0   0   0        0x08
 *        第6行点亮    0   0   0   0   0   1   0   0        0x04
 *        第7行点亮    0   0   0   0   0   0   1   0        0x02
 *        第8行点亮    0   0   0   0   0   0   0   1        0x01
 */
void scroll_led_matrix_up_2_down();
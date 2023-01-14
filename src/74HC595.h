//
// Created by dingrui on 2023/1/14.
//

// #ifndef STC89C52RC_74HC595_H
// #define STC89C52RC_74HC595_H

// #endif //STC89C52RC_74HC595_H
#pragma once

/**
 * @brief 向74HC595写入数据 通过移位寄存器输出
 *        向595芯片写入1个Byte
 *        将1个字节Byte从高位到低位依次将bit写给SER引脚
 *        控制RCLK和SRCLK
 *        在SRCLK的一个上升沿中就会存入一个移位寄存器中 从高位到低位的顺序
 *        在RCLK的一个上升沿中将移位寄存器中的数据全部传入到存储寄存器中
 */
void hc_595_write_data(unsigned char dat);
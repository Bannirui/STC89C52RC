//
// Created by dingrui on 2023/1/28.
//

#include "lcd1602.h"

/**
 * @brief 写命令 根据时序图
 * @param cmd
 */
void lcd1602_write_cmd(u8 cmd)
{
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_E = 0;
    LCD1602_DATA_PORT = cmd; // 准备数据
    delay_ms(1);
    // 上升沿
    LCD1602_E = 1;
    delay_ms(1);
    // 下降沿
    LCD1602_E = 0;
}

/**
 * @brief 写数据
 * @param dat
 */
void lcd1602_write_dat(u8 dat)
{
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_E = 0;
    LCD1602_DATA_PORT = dat; // 准备数据
    delay_ms(1);
    // 上升沿
    LCD1602_E = 1;
    delay_ms(1);
    // 下降沿
    LCD1602_E = 0;
}

/**
 * @brief 初始化 指令写入
 */
void lcd1602_init()
{
    lcd1602_write_cmd(0x38);
    lcd1602_write_cmd(0x0c);
    lcd1602_write_cmd(0x06);
    lcd1602_write_cmd(0x01); // 清屏指令
}

/**
 * @brief 显示字符内容
 * @param x
 * @param y
 * @param dat
 */
void lcd1602_display_char(u8 x, u8 y, u8 dat)
{
    if (x > 15 || y > 1) return;
    if (y == 0)
        lcd1602_write_cmd(0x80 + x);
    else
        lcd1602_write_cmd(0x80 + 0x40 + x);
    lcd1602_write_dat(dat + 0x30); // 转ascii值
}

/**
 * @brief 显示字符串内容
 * @param x [0...15]
 * @param y [0...1]
 * @param str 显示的内容
 */
void lcd1602_display_str(u8 x, u8 y, u8 *str)
{
    if (x > 15 || y > 1) return;
    u8 i = 0;
    if (y == 0)
    {
        // 第一行
        while (*str != '\0')
        {
            if (i < 16 - x) lcd1602_write_cmd(0x80 + x + i);
            else
                lcd1602_write_cmd(0x80 + 0x40 + x + i - 16);
            lcd1602_write_dat(*str);
            str++;
            i++;
        }
    } else
    {
        // 第二行
        while (*str != '\0')
        {

            if (i < 16 - x) lcd1602_write_cmd(0x80 + 0x40 + x + i);
            else
                lcd1602_write_cmd(0x80 + x + i - 16);
            lcd1602_write_dat(*str);
            str++;
            i++;
        }
    }
}

/**
 * @brief 清屏
 */
void lcd1602_clear()
{
    lcd1602_write_cmd(0x01);
}
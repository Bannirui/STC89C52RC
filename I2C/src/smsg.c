//
// Created by dingrui on 2023/1/18.
//

#include "smsg.h"

u8 g_smg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39,
                     0x5e, 0x79, 0x71, 0x00};

/**
 * @brief 数码管显
 * @param pos 从指定位置开始 数码管标识从左到右[1...8]
 * @param dat 将数据依次显示出来 dat数组存放的是数码管真值表的段码脚标[0...16]
 */
void smsg_display(u8 pos, u8 dat[])
{
    u8 idx = 0;
    for (unsigned char i = pos - 1; i < 8; ++i)
    {
        // 位选 控制哪个LED数码管点亮
        switch (i)
        {
            case 0:
                LSC = 1;
                LSB = 1;
                LSA = 1;
                break; // 111->7 LED8被点亮
            case 1:
                LSC = 1;
                LSB = 1;
                LSA = 0;
                break; // 110->6 LED7被点亮
            case 2:
                LSC = 1;
                LSB = 0;
                LSA = 1;
                break; // 101->5 LED6被点亮
            case 3:
                LSC = 1;
                LSB = 0;
                LSA = 0;
                break; // 100->4 LED5被点亮
            case 4:
                LSC = 0;
                LSB = 1;
                LSA = 1;
                break; // 011->3 LED4被点亮
            case 5:
                LSC = 0;
                LSB = 1;
                LSA = 0;
                break; // 010->2 LED3被点亮
            case 6:
                LSC = 0;
                LSB = 0;
                LSA = 1;
                break; // 001->1 LED2被点亮
            case 7:
                LSC = 0;
                LSB = 0;
                LSA = 0;
                break; // 000->0 LED1被点亮
        }
        // 数码管段选
        SMG_DP_PORT = g_smg_code[dat[idx]];
        idx++;
        delay_ms(1);
        SMG_DP_PORT = g_smg_code[16]; // 消隐
    }
}
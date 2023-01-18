#include "key.h"
#include "smsg.h"
#include "AT24C02.h"

// 指定E2PROM写入数据的地址
#define E2PROM_ADDR 0

/**
 * 系统运行时 数码管右3位显示0
 * 按K1键将数据写入到E2PROM中
 * 按K2键读取E2PROM中保存的数据
 * 按K3键数据+1 在数码管上显示出来
 * 按K4键数据清0 在数码管上显示出来
 */
int main()
{
    u8 dat = 1;
    // dat要显示在数码管 按照百位 十位 个位顺序依次显示
    u8 display_buf[3];
    while (1)
    {
        u8 key_status = key_status_scan(0);
        switch (key_status)
        {
            case KEY1_PRESS:
                // K1被按下 保存数据
                e2prom_write_one_byte(E2PROM_ADDR, dat);
                break;
            case KEY2_PRESS:
                // K2被按下 读取数据
                dat = e2prom_read_one_byte(E2PROM_ADDR);
                break;
            case KEY3_PRESS:
                // K3被按下 自增 数据范围
                if (dat != 255)
                    dat++;
                break;
            case KEY4_PRESS:
                // K4被按下 清0
                dat = 0;
                break;
            case KEY_UN_PRESS:
                break;
        }
        display_buf[0] = dat / 100;
        display_buf[1] = dat % 100 / 10;
        display_buf[2] = dat % 100 % 10;
        smsg_display(6, display_buf);
    }
}
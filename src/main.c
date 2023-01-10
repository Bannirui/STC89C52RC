#include <mcs51/reg51.h>

// 点亮led
void on_light();

// 模拟延时
void delay();

int main()
{
    on_light();
    return 0;
}

void on_light()
{
    // 地址位
    // P0
    __sbit LED = P0;
    // [P1.0...P1.4]
    __sbit ADDR0 = P1 ^ 0, ADDR1 = P1 ^ 1, ADDR2 = P1 ^ 2, ADDR3 = P1 ^ 3;
    __sbit ENLED = P1 ^ 4;

    ENLED = 0; // U3 U4两片74HC138总使能
    ADDR3 = 1; // 使能U3使之正常输出
    ADDR2 = 1; // 经U3的Y6输出开启三极管Q16
    ADDR1 = 1;
    ADDR0 = 0;

    for (;;)
    {
        LED = 0; // 点亮
        delay();
        LED = 1; // 熄灭
        delay();
    }
}

void delay()
{
    for (int i = 0; i < 30000; i++);
}
#include <mcs51/8052.h>

// 独立按键K3的阳极管脚
#define K3_POSITIVE P3_2
#define K4_POSITIVE P3_3

// D1阴极管脚
#define D1_NEGATIVE P2_0
#define D2_NEGATIVE P2_1

// 初始化外部中断0
void init_int0()
{
    IT0 = 1; // 外部中断0的触发方式为1(电平下降沿)
    EX0 = 1; // 允许外部中断0
    EA = 1; // 中断总开关
}

// 初始化外部中断1
void init_int1()
{
    IT1 = 1; // 外部中断0的触发方式为1(电平下降沿)
    EX1 = 1; // 允许外部中断1
    EA = 1; // 中断总开关
}

int main()
{
    /**
     * 管脚P3.2是多功能 外部中断0 INT0管脚
     * 外部中断0两种出发方式
     *     下降沿电平
     *     低电平
     * 独立按键K3一端连接着GND 另一端连接着P3.2
     * 当独立按键被按下时 P3.2跟GND导通
     * P3.2端口管脚内部有上拉电阻 初始时为高电平 按键K3被按下时P3.2为低电平 也就是相当于对P3.2输入了一个下降沿电平
     * 出发外部中断0
     * 在中断回调函数中点亮D1
     * D1阳极为VCC 阴极为P2.0(P2.0内部有上拉电阻 初始时为高电平) 给P2.0输入一个低电平即可点亮D1
     */

    init_int0();
    init_int1();
    while (1)
    {

    }
}

// 外部中断0服务函数
void int0_interrupt_callback() __interrupt(0)
{
    // 按键按下触发的中断 对机械按键进行消抖
    for (int i = 0; i < 3000; ++i);
    // 控制D1的点亮和熄灭
    if (K3_POSITIVE == 0) D1_NEGATIVE = !D1_NEGATIVE;
}

// 外部中断0服务函数
void int1_interrupt_callback() __interrupt(2)
{
    // 按键按下触发的中断 对机械按键进行消抖
    for (int i = 0; i < 3000; ++i);
    // 控制D2的点亮和熄灭
    if (K4_POSITIVE == 0) D2_NEGATIVE = !D2_NEGATIVE;
}
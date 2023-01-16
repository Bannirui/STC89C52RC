#include <mcs51/8052.h>

/**
 * 定时器配置
 *     对TMOD赋值 确定T0和T1的工作方式
 *     根据所要定时的时间计算初值 将初值写入TH和TL
 *     如果使用中断 则对EA赋值 开放定时器中断
 *     使TR置位 启动定时器/计数器进行定时或者计数
 *
 * 初值计算
 *     外部晶振=f(Hz)
 *     时钟周期=1/f(s)
 *     机器周期=12/f(s)
 *     初始值=65536-N*机器周期
 *     TH=初始值>>8
 *     TL=初始值
 */

/**
 * 晶振频率=11.0592MHz
 * 时钟周期=1/11059200(s)
 * 机器周期=12/11059200(s)
 * 1ms=0.001/(12/11059200)(机器周期)=921.6(机器周期)
 */
#define INIT_VALUE (65536 - 921)

// 高精度赋值低精度 隐式转换 丢失高位 保留低位的8位
#define TH_VALUE INIT_VALUE>>8
#define TL_VALUE INIT_VALUE

// led1的阴极
#define D1_NEGATIVE_PORT P2_0

// 定时器T0初始化
void timer0_1ms_init()
{
    /**
     * TMOD设置定时器模式
     * 0x01 -> 0000 0001
     * 高4位针对T1定时器 低4位针对T0定时器
     * 当前设置T0定时器位模式1
     *     GATE C/T M1 M0
     *       0   0  0  1
     *  16位定时器/计数器模式
     */
    TMOD |= 0x01;
    TH0 = TH_VALUE;
    TL0 = TL_VALUE;
    ET0 = 1; // 打开定时器0中断允许
    EA = 1; // 中断总开关打开
    TR0 = 1; // 打开定时器
}

// 定时器1s中 通过LED标识工作状态
int main()
{
    // 定时器0配置
    timer0_1ms_init();
    while (1);
}

// 定时器0中断服务函数
void timer0_1ms_interrupt() __interrupt(1)
{
    // 记录中断次数
    static unsigned short cnt = 0;
    cnt++;
    if (cnt == 999)
    {
        // 1s
        cnt = 0;
        D1_NEGATIVE_PORT = !D1_NEGATIVE_PORT; // 控制led1的熄灭点亮状态转换
    }
    TF0 = 0; // 重置满0
    // 重新设置初值
    TH0 = TH_VALUE;
    TL0 = TL_VALUE;
}
#include <mcs51/8052.h>

// LED GND引脚
#define LED1 P2_0
#define LED2 P2_1
#define LED3 P2_2
#define LED4 P2_3
#define LED5 P2_4
#define LED6 P2_5
#define LED7 P2_6
#define LED8 P2_7

// 给LED连接的单片机引脚一个低电平 跟VCC高电平形成电压差 LED有电流 被点亮
void on_LED1()
{
    LED1 = 0;
}

void off_LED1()
{
    LED1 = 1;
}

typedef unsigned int u16;

// 时延 20ms为步进值
// STC89C52RC晶振=11.0592MHz
// 时钟周期=1/11059200(s)
// KST51架构下机器周期=12个时钟周期=12/11059200(s)
// 假定一个延时20ms为单位
// 就是求n个机器周期总时长是0.02s n=0.02/(12/11.0592)=0.02*11059200/12=18432
// 16位定时器的溢出值是65536(65535+1后溢出)
// 给定时器设置一个初值 每次经过一个机器周期就自增1 经过18432个机器周期后达到65536溢出 通过检测TF0的值判定定时器值是否溢出 溢出了说明经过了一个20ms时常
// 用户需要多久的定时操作就给定对应的20ms的倍数 比如要实现sleep(1s)就传实参50
void delay_20ms(unsigned char target)
{
    unsigned char cnt = 0; // 计数变量记录T0溢出次数
    TMOD = 0x01; // T0为模式1
    TH0 = 0xBB; // T0初值0xBB00
    TL0 = 0x00;
    TR0 = 1; // 启动T0
    for (;;)
    {
        if (TF0 == 1)
        {
            // 检测T0到溢出
            TF0 = 0; // T0溢出后清0中断标志
            TH0 = 0xBB; // 重新赋值
            TL0 = 0x00;
            cnt++;
            if (cnt >= target) return;
        }
    }
}

// 操作led1 点亮-熄灭
void on_off_led1()
{
    on_LED1();
    delay_20ms(50);
    off_LED1();
    delay_20ms(50);
}

typedef unsigned char u8;

// P2口有8个控制端口
#define LED P2

// [led1...led8]跑马灯
void horse_race_lamp()
{
    u8 i = 0;
    for (i = 0; i < 8; i++)
    {
        LED = ~(0x01 << i);
        delay_20ms(10);
    }
}

typedef unsigned char u8;
// 共阴数码管真值表
// [0..9] [A...F] 不显示
u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71,
                    0x00};

// 数码管LED8的管脚
#define SMG_A_DP_PORT P0

// 静态数码管
// 2个4位一体的共阴数码管 上连了38译码器
// 38译码器P2口[P2.2...p2.4]默认高电平为1 二进制111等于十进制7 输出Y7也就是LED8是0 表示低电平 LED8默认情况下是亮着的
// 就可以指定数码管真值表进行静态显示
void static_led_msg_display_0()
{
    SMG_A_DP_PORT = gsmg_code[0];
}

// LED8 指定数码管真值表进行静态显示
void static_led_msg_display()
{
    // 数码管led8轮流显示[0...9 A...F 不显示]
    for (int i = 0; i < 17; ++i)
    {
        SMG_A_DP_PORT = gsmg_code[i];
        delay_20ms(50);
    }
}

// 38译码器的输入[P2.2...P2.4] 定义了数码管的位选
#define LSA P2_2
#define LSB P2_3
#define LSC P2_4

// 数码管的段选a-dp连接在74HC245驱动芯片上
// 芯片由P0口的[P0.0...P0.7]控制
#define SMG_DP_PORT P0

// 2个4位一体共阴数码管 就是8个数码管
// 38译码器位选控制哪个数码管点亮
// 数码管真值表映射数码管显示内容
// 从左到右[0...7]分别对应[LED8...LED1]
void dynamic_led_msg_display()
{
    u8 i = 0;
    for (i = 0; i < 8; ++i)
    {
        // 位选 控制哪个LED数码管点亮
        switch (i)
        {
            case 0:
                LSC = 1;
                LSB = 1;
                LSA = 1;
                break; // 111->7
            case 1:
                LSC = 1;
                LSB = 1;
                LSA = 0;
                break; // 110->6
            case 2:
                LSC = 1;
                LSB = 0;
                LSA = 1;
                break; // 101->5
            case 3:
                LSC = 1;
                LSB = 0;
                LSA = 0;
                break; // 100->4
            case 4:
                LSC = 0;
                LSB = 1;
                LSA = 1;
                break; // 011->3
            case 5:
                LSC = 0;
                LSB = 1;
                LSA = 0;
                break; // 010->2
            case 6:
                LSC = 0;
                LSB = 0;
                LSA = 1;
                break; // 001->1
            case 7:
                LSC = 0;
                LSB = 0;
                LSA = 0;
                break; // 000->1
        }
        // 数码管段选
        // [LED8...LED1]分别显示[0...7]
        SMG_DP_PORT = gsmg_code[i];
        delay_20ms(10);
        SMG_DP_PORT = gsmg_code[16]; // 不显示
    }
}

int main()
{
    for (;;)
    {
        // on_off_led1();
        // horse_race_lamp();
        // static_led_msg_display_0();
        // static_led_msg_display();
        dynamic_led_msg_display();
    }
}
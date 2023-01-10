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

// 时延
void delay_10us(u16 ten_us)
{
    while (ten_us--);
}

// 操作led1 点亮-熄灭
void on_off_led1()
{
    on_LED1();
    delay_10us(50000);
    off_LED1();
    delay_10us(50000);
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
        delay_10us(50000);
    }
}

int main()
{
    for (;;)
    {
        horse_race_lamp();
    }
}
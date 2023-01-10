#include <mcs51/8052.h>

// P2.0管脚
#define LED1 P2_0

// led
void light_on();

void light_off();

// 时延
void delay();

int main()
{
    for (;;)
    {
        light_on();
        delay();
        light_off();
        delay();
    }
}

void light_on()
{
    LED1 = 0; // 点亮
}

void light_off()
{
    LED1 = 1; // 熄灭
}

void delay()
{
    for (int i = 0; i < 3000; i++);
}
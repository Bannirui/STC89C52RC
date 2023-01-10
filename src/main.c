#include <mcs51/8052.h>

// P2.0管脚
#define LED1 P2_0

int main()
{
    for (;;)
    {
        LED1 = 0; // 点亮
        for (int i = 0; i < 3000; i++);
        LED1 = 1; // 熄灭
        for (int i = 0; i < 3000; i++);
    }
    return 0;
}
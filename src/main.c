#include <mcs51/reg51.h>

__sbit __at(0xA0) LED;
__sbit ADDR0;

int main()
{
    LED = 0;
    ADDR0 = P0 ^ 0;
    return 0;
}

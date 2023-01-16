#include "key.h"

int main()
{
    for (;;)
    {
        switch_ctl_led(); // 通过独立按键[K1...K4]控制led小灯[D1...D4]
    }
}
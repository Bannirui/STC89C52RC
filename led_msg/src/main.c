#include "led_msg.h"

int main()
{
    for (;;)
    {
        // static_led_msg_display_0(g_smg_code[1]); // 数码管LED8静态显示数码管真值
        // static_led_msg_display(); // 数码管LED8动态显示数码管真值
        dynamic_led_msg_display(); // 数码管模块多个数码管动态显示
    }
}
#include "led.h" // led
#include "beep.h" // 蜂鸣器
#include "led_msg.h" // 数码管
#include "switch.h" // 独立按键开关

int main()
{
    for (;;)
    {
        // on_off_led1(); // LED模块LED1点亮-熄灭
        // horse_race_lamp(); // LED模块跑马灯效果
        // beep(3); // 蜂鸣器工作
        // static_led_msg_display_0(); // 数码管LED8静态显示数码管真值
        // static_led_msg_display(); // 数码管LED8动态显示数码管真值
        // dynamic_led_msg_display(); // 数码管模块多个数码管动态显示
        switch_ctl_led(); // 通过独立按键[K1...K4]控制led小灯[D1...D4]
    }
}
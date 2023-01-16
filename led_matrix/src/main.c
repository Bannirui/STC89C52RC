#include "led_matrix.h"

int main()
{
    for (;;)
    {
        scroll_led_matrix_up_2_down(); // 从上至下滚动点亮led点阵
        // on_left_top(); // 点亮点阵左上角led
        // display_img_0(); // led点阵上显示0
    }
}

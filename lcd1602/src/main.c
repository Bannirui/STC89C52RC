#include "lcd1602.h"

int main()
{
    lcd1602_init();
    lcd1602_display_str(0, 0, "HELLO WORLD");
    lcd1602_display_str(0, 1, "Bannirui");
    while (1);
}

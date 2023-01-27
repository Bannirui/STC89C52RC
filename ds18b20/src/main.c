#include "public.h"
#include "ds18b20.h"
#include "smsg.h"

int main()
{
    ds18b20_init();
    while (1)
    {
        delay_ms(1);
        int temp_value = ds18b20_read_temperature() * 10;
        u8 smsg_buf[5]; // 数码管
        if (temp_value < 0)
        {
            temp_value = -temp_value;
            smsg_buf[0] = 0x40; // 负号
        } else
            smsg_buf[0] = 0x00; // 不显示
        smsg_buf[1] = g_smg_code[temp_value / 1000];
        smsg_buf[2] = g_smg_code[(temp_value % 1000) / 100];
        smsg_buf[3] = g_smg_code[temp_value % 1000 % 100 / 10] | 0x80; // dp段小数点
        smsg_buf[4] = g_smg_code[temp_value % 1000 % 100 % 10];
        smsg_display(4, smsg_buf);

    }
}

#include "public.h"
#include "smsg.h"
#include "ds1302.h"

int main()
{
    ds1302_init();
    u8 time_buf[8];
    while (1)
    {
        ds1302_read_time();
        time_buf[0] = g_smg_code[g_ds1302_time[2] / 16]; // 时
        time_buf[1] = g_smg_code[g_ds1302_time[2] % 16];
        time_buf[2] = 0x40; // -
        time_buf[3] = g_smg_code[g_ds1302_time[1] / 16]; // 分
        time_buf[4] = g_smg_code[g_ds1302_time[1] % 16];
        time_buf[5] = 0x40; // -
        time_buf[6] = g_smg_code[g_ds1302_time[0] / 16]; // 秒
        time_buf[7] = g_smg_code[g_ds1302_time[0] % 16];

        smsg_display(1, time_buf);
    }
}

#include "smsg.h"
#include "ired.h"

int main()
{
    ired_init();
    u8 ired_buf[3];
    ired_buf[2] = 0x76; // H的段码
    while (1)
    {
        // 16进制
        ired_buf[0] = g_smg_code[g_ired_data[2] / 16];
        ired_buf[1] = g_smg_code[g_ired_data[2] % 16];
        smsg_display(6, ired_buf);
    }
}
#include <mcs51/8052.h>

/**
 * @brief 串口配置初始化
 * @param baud 波特率
 */
void uart_init(unsigned char baud)
{
    // 定时器1工作方式
    TMOD |= 0x20;
    /**
     * 串口控制寄存器SCON
     * SM0 SM1 SM2 REN TB8 RB8 TI RI
     *  0   1   0   1   0   0   0  0
     *  工作方式为1
     */
    SCON = 0x50;
    // 倍频
    PCON = 0x80;
    // 定时器初始值
    TH1 = baud;
    TL1 = baud;
    ES = 1; // 打开串口中断
    EA = 1; // 打开总中断
    TR1 = 1; // 打开定时器
}

/**
 * 串口通信
 * serial port monitor插件->usb->ch340->mcu
 * 收到信息后返回给pc的串口调试助手
 */
int main()
{
    // 定时器初值 波特率9600
    uart_init(0xFA);
    while (1);
}

/**
 * @brief 中断服务函数
 *        手动RI清零等待下一次串口的接收
 */
void uart() __interrupt(4)
{
    // 接收中断标识清零
    RI = 0;
    // 将接收的数据从SBUF中读取出来
    unsigned char recv_data = 0;
    recv_data = SBUF;
    // 将串口接收到的数据发送出去
    SBUF = recv_data;
    // 发送完成后TI会被置1 等到发送完成
    while (!TI);
    TI = 0; // 发送完成手动清0 等待下一次发送
}
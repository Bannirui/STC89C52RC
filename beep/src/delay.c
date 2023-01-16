//
// Created by dingrui on 2023/1/11.
//

#include "delay.h"
#include <mcs51/8052.h>

/**
 * @brief 延时1us
 *        1(us)=0.000001(s)=0.000001/(12/11059200)(机器周期)=0.9216(机器周期)
 */
void delay_1_us()
{
    TMOD = 0x001;
    int base_time = (65536 - 1);
    unsigned char tl = base_time;
    unsigned char th = base_time >> 8;
    TH0 = th;
    TL0 = tl;
    while (1)
    {
        if (TF0 == 1)
        {
            TF0 = 0;
            TH0 = th;
            TL0 = tl;
            return;
        }
    }
}

void delay_1_us_cnt(unsigned int cnt)
{
    while (cnt--)
    {
        delay_1_us();
    }
}

/**
 * @brief 延时实现
 *        晶振频率=11.0592MHz
 *        1时钟周期=1/11059200 (s)
 *        STC89C52RC架构下
 *        1机器周期=12*时钟周期=12/11059200 (s)
 *        1(ms)=0.001(s)=0.001/(12/11059200) (机器周期)=921.6(机器周期)
 *        每经过一个机器周期计数就自增1 以定时器计数溢出时抛出异常为临界值
 *        定时器T0方式1的计数阈值=2^16-1+1=65536
 * @param ten_ms_cnt 以10ms为步进值 需要延时多少个10ms
 */
void delay_1_ms()
{
    TMOD = 0x01; // 设置T0定时器为模式1
    int base_time = (65536 - 921); // 意味着定时器发生一定次数自增后就会溢出 将TF0设置为1 我们就通过检测TF0值判定计时
    unsigned char tl = base_time; // base_time是int 32位 低8位
    unsigned char th = base_time >> 8; // base_time的次8位
    TH0 = th;
    TL0 = tl;
    TR0 = 1; // 启动T0定时器
    for (;;)
    {
        // 轮询中检测TF0值 一旦变成了1就说明到达了指定的定时
        if (TF0 == 1)
        {
            TF0 = 0; // T0溢出后清0中断标志
            // 重新赋值
            TH0 = th;
            TL0 = tl;
            return;
        }
    }
}

void delay_1_ms_cnt(unsigned int cnt)
{
    while (cnt--)
    {
        delay_1_ms();
    }
}
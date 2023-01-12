//
// Created by dingrui on 2023/1/11.
//

#ifndef STC89C52RC_DELAY_H
#define STC89C52RC_DELAY_H

extern void delay_20ms(unsigned char twenty_ms_cnt);

extern void delay_10ms_cnt(unsigned int cnt);

// fixme 定时器中断回调好像有问题
extern void delay_1ms();

#endif //STC89C52RC_DELAY_H

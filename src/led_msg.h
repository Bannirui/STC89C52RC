//
// Created by dingrui on 2023/1/11.
//

#ifndef STC89C52RC_LED_MSG_H
#define STC89C52RC_LED_MSG_H

// 静态数码管
// 2个4位一体的共阴数码管 上连了38译码器
// 38译码器P2口[P2.2...p2.4]默认高电平为1 二进制111等于十进制7 输出Y7也就是LED8是0 表示低电平 LED8默认情况下是亮着的
// 就可以指定数码管真值表进行静态显示
extern void static_led_msg_display_0();

// LED8 指定数码管真值表进行静态显示
// 38译码器位选控制哪个数码管点亮
// 数码管真值表映射数码管显示内容
// 因此实现里面只要关注段选就是LED8的具体显示内容
extern void static_led_msg_display();

// 2个4位一体共阴数码管 就是8个数码管
// 38译码器位选控制哪个数码管点亮
// 数码管真值表映射数码管显示内容
// 从左到右[0...7]分别对应[LED8...LED1]
// 每个数码管显示-不显示延时控制人眼余晖效应
extern void dynamic_led_msg_display();

#endif //STC89C52RC_LED_MSG_H

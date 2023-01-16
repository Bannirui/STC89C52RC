//
// Created by dingrui on 2023/1/15.
//

// #ifndef STC89C52RC_MOTOR_H
// #define STC89C52RC_MOTOR_H

// #endif //STC89C52RC_MOTOR_H
#pragma once

/**
 * ULN2003D芯片没有外接上拉电阻 因此其输出的高电平并不是实际的高电平
 * 芯片输出连接在J47端子上
 *
 * 直流电机只能使用J47端子上的VCC提供的高电平
 * 让直流电机另一个引脚接在[OUT1...OUT4]上 控制为低电平
 * 因此只能一个方向转动
 *
 * P10输出高电平 经过ULN2003D芯片 OUT1为为低电平 电机旋转
 * P10输出低电平 经过ULN2003D芯片 OUT1为为高电平 电子停止
*/
void run_dc_motor();
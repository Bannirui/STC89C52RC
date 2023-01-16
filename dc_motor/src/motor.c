//
// Created by dingrui on 2023/1/15.
//

#include "motor.h"

#include <mcs51/8052.h>
#include "delay.h"

// 直流电机的阴极
#define DC_MOTOR_NEGATIVE P1_0

// 直流电机旋转时长
#define DC_MOTOR_RUN_TIME_MS 5000

void run_dc_motor()
{
    DC_MOTOR_NEGATIVE = 1; // OUT1输出为低电平 电机旋转
    delay_1_ms_cnt(DC_MOTOR_RUN_TIME_MS);
    DC_MOTOR_NEGATIVE = 0; // OUT1输出为高电平 电机停止
}
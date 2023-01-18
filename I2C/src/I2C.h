//
// Created by dingrui on 2023/1/18.
//

#pragma once

#include "public.h"

// I2C的信号管脚
#define I2C_SCL P2_1
#define I2C_SDA P2_0

// 主机接收从机响应
#define SLAVE_REPLAY_ACK 1<<0
#define SLAVE_REPLAY_NACK 1<<1

// 主机读取从机消息之后是否需要从机继续发送数据
#define SLAVE_SEND_CONTINUE 1<<0
#define SLAVE_SEND_STOP 1<<1

void i2c_start();

void i2c_stop();

void i2c_ack();

void i2c_nack();

u8 i2c_wait_ack();

void i2c_write_byte(u8 dat);

u8 i2c_read_byte(u8 mode);
//
// Created by dingrui on 2023/1/28.
//

#pragma once

#include "public.h"

// 管脚定义
#define LCD1602_RS P2_6
#define LCD1602_RW P2_5
#define LCD1602_E P2_7
#define LCD1602_DATA_PORT P0

void lcd1602_init();

void lcd1602_display_str(u8 x, u8 y, u8 *str);
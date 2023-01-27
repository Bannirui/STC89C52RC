//
// Created by dingrui on 2023/1/27.
//

#pragma once

#include "public.h"

#define DS1302_RST P3_5
#define DS1302_CLK P3_6
#define DS1302_IO P3_4

extern u8 g_ds1302_time[7];

void ds1302_init();

void ds1302_read_time();

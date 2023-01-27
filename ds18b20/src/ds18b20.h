//
// Created by dingrui on 2023/1/27.
//

#pragma once

#include "public.h"

#define DS18B20_PORT P3_7

u8 ds18b20_init();

float ds18b20_read_temperature();

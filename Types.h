//
//  Types.h
//  SCMS
//
//  Created by Zach Zahos on 2016-01-02.
//
//

#pragma once

#include <cstdint>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

#define L(__ID__) (((__ID__ & 0xFF000000) >> 24) | ((__ID__ & 0x00FF0000) >> 8) | ((__ID__ & 0x0000FF00) << 8) | ((__ID__ & 0x000000FF) << 24))

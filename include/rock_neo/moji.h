#ifndef ROCK_NEO_MOJI_H
#define ROCK_NEO_MOJI_H

#include "rock_neo.h"

unknown_t MojiTaskExec(unknown_t, unknown_t, unknown_t);
s32 MojiTaskKill(); // 0x80053A30
s32 func_80053788();

extern u32 Moji_flag;  // 0x80098A58
extern u32 Moji_flag3; // 0x80098B30

#define MOJI_TASK0_ON 0x8000000
#define MOJI3_PARTS_TASK 0x10000

#endif
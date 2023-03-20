#ifndef ROCK_NEO_H
#define ROCK_NEO_H

#include "common.h"

/* Symbols with unknown compile units */
unknown_t func_8005382C(unknown_t, unknown_t, unknown_t);
unknown_t func_80063FC0(unknown_t, unknown_t);
unknown_t func_8001D7AC(unknown_t);
unknown_t func_80012E98(unknown_t);
unknown_t func_80031AA4();
unknown_t func_80016D64();
unknown_t func_8001DA8C(unknown_t);
unknown_t func_8001F23C();
extern unknown_t D_8008CB94; // may be in sub_scrn.c
extern s32 D_80098B2C;

#define GET_PARTS_NO(x) ((u8*)&Moji_flag3)[x]
#define GET_SELECT_NO(x) ((u8*)&D_80098B2C)[x]

#endif

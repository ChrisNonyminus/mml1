#ifndef ROCK_NEO_H
#define ROCK_NEO_H

#include "common.h"

#include "psxsdk/libapi.h"
#include "psxsdk/libc.h"
#include "psxsdk/libgpu.h"

/* Symbols with unknown compile units */
unknown_t func_80063FC0(unknown_t, unknown_t);
unknown_t func_8001D7AC(unknown_t);
unknown_t func_80012E98(unknown_t);
unknown_t func_80031AA4();
unknown_t func_80016D64();
unknown_t Sce_flag_on(unknown_t);
unknown_t func_8001F23C();
extern unknown_t D_8008CB94; // may be in sub_scrn.c
extern s32 D_80098B2C;
unknown_t func_8001F3C8();
unknown_t func_80038648();
extern u8 D_800C356F;
unknown_t func_80017C30(unknown_t);
unknown_t func_8001B2F0(unknown_t);
unknown_t func_8005DF3C();
unknown_t func_8005DF4C();
unknown_t func_80063EF0();
unknown_t func_8001B314();
unknown_t func_8001B33C();
unknown_t func_8001D494(unknown_t, unknown_t, unknown_t);
unknown_t Sce_flag_off(unknown_t);
unknown_t func_80063BA8();
unknown_t func_800665E8();
extern u16 D_80098910;
extern DR_MODE D_80098A10[];
extern s16 D_80098A70;
extern s16 D_80098A72;
extern u8 D_80098788;

#define GET_PARTS_NO(x) ((u8*)&Moji_flag3)[x]
#define GET_SELECT_NO(x) ((u8*)&D_80098B2C)[x]

#define PRIM_PTR(t) (*(t** )0x1F800070)
#define PRIM_PTR_INC(t) PRIM_PTR(t); PRIM_PTR(t) = PRIM_PTR(t) + 1

typedef struct unkst_80098A28 {
    s8 xe0[3]; // tag?
    s8 unk3; // tag? (4th byte?)
    s8 unk4[3];
    s8 unk7; // code?
    s16 unk8, unkA;
    s16 unkC, unkE; // unkC is being set to 320 and unkE to 240, looks like the resolution
} unkst_80098A28; // may be a GTE primitive
extern unkst_80098A28 D_80098A28;

#endif

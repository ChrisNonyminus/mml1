#ifndef ROCK_NEO_SUB_SCRN_H
#define ROCK_NEO_SUB_SCRN_H

#include "rock_neo.h"
#include "rock_neo/player.h"

void Sub_screen_back_ground_set(); /* 0x80062368 */
s32 Sub_screen_basic_param_set();  /* 0x80061E0C */
typedef struct SUB_SCREEN_WORK {
    s8 routine_0, routine_1;
    s16 routine_2;
    u8 x4[0x8 - 0x4];
    u16 x8;
    u8 rb_parts_no_2;
    u8 weapon_no;
} SUB_SCREEN_WORK;
extern void (*D_8008DBB0[])(
    SUB_SCREEN_WORK*); // sub_scrn.c function/routine pointer table I think

extern SUB_SCREEN_WORK D_800A38F0;

void func_8005EC34(void);     /* 0x8005EC34 */
s32 func_8005EC80(s32* arg0); /* 0x8005EC80 */
unknown_t func_800605DC();
unknown_t func_80060248(SUB_SCREEN_WORK*);
s32 func_800600CC(SUB_SCREEN_WORK*);
void Sub_screen_shift_check(SUB_SCREEN_WORK*);
unknown_t func_80060DB8(SUB_SCREEN_WORK*);
void Sub_screen_sort_sub(PL_WORK*, s32, s32);

#endif

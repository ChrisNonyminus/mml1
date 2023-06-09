#ifndef ROCK_NEO_GAME_H
#define ROCK_NEO_GAME_H

#include "rock_neo.h"

void Game_logo_kill(unknown_t);

typedef struct GAME_WORK {
    s8 routine_0;
    s8 x1;
    u8 x2[0x4 - 0x2];
    s32 x4;
    s16 x8, xA;
    s32 time;
    s32 x10, x14;
    u16 difficultyUnlocked[2];
    s32 zennyCount;
    u8 x20[0x3C - 0x20];
    void* x3C;
    u8 x40[0x10];
    s8 stage_no, area_no;
    s8 x52, x53;
    s8 x54[0x5B - 0x54];
    s8 x5B;
    s8 x5C[0x68 - 0x5C];
    s16 x68, x6A, x6C;
    u8 x6E[0x70 - 0x6E];
    s16 x70, x72, x74, x76;
    s8 x78[0x81- 0x78];
    s8 x81;
    u8 x82;
    s8 x83;
} GAME_WORK;

typedef struct {
    u8 tag[4];
    u8 unk4, unk5, unk6, code;
    s16 unk8, unkA, unkC, unkE, unk10, unk12, unk14, unk16;
    s8 gap[16];

} UNK_PRIM_1;

typedef struct {
    int x0;
    s8 x4[0x74 - 0x4];
    void* x74;
    void* x78;
} UnkStruc_80098934;
extern UnkStruc_80098934* D_80098934;

extern GAME_WORK Game_work;

extern void (*Game_main_tbl[])(GAME_WORK*);

void func_80016BC0();
void func_80016BF4();

void func_800155A4(void);

// GAME_WORK tbl funcs, zero-indexed
void func_80015634(GAME_WORK*);
void func_80015734(GAME_WORK*);
void func_80015840(GAME_WORK*);
void func_800158F0(GAME_WORK*);
void func_80015FE8(GAME_WORK*);
void func_80016160(GAME_WORK*);
void func_800164B4(GAME_WORK*);
void func_80016528(GAME_WORK*);
void func_8001663C(GAME_WORK*);
void func_80016798(GAME_WORK*);
void func_800169AC(GAME_WORK*);

#endif

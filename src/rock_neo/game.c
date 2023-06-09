#include "common.h"

#include "rock_neo/cd.h"
#include "rock_neo/game.h"
#include "rock_neo/joy.h"
#include "rock_neo/moji.h"
#include "rock_neo/obj.h"
#include "rock_neo/player.h"
#include "rock_neo/sce.h"
#include "rock_neo/sound.h"
#include "rock_neo/sub_scrn.h"

#include "rock_neo/Code800133D8.h"

// clang-format off

#ifndef ACCEPT_REORDERING_BULLSHIT
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800155A4);
#else
// clang-format on
void func_800155A4(void) {
    GAME_WORK* gp;

    gp = &Game_work;

    *(s8*)0x1F800001 = 2; // TODO: make variable mapped to this address
    *(s32*)&gp->routine_0 = 0;
    while (1) {
        Game_main_tbl[gp->routine_0](gp);
        func_80031AA4();
        func_80016BC0();
        func_80016BF4();
        func_80012E98(1);
    }
}
// clang-format off
#endif

// https://decomp.me/scratch/OFeoF
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015634);

#ifndef ACCEPT_REORDERING_BULLSHIT
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015734);
#else
// clang-format on
void func_80015734(GAME_WORK* gw) {
    _unkstruc_800C3558* temp_v1 = &D_800C3558;

    switch (gw->x1) {
    case 0:
        Sce_flag_on(0x527);
        if (!((u8)gw->x82 & 1) && (gw->x54[7] == 0)) {
            Sce_flag_on(0x510);
            Sce_flag_on(0x522);
            Sce_flag_on(0x446);
            Sce_flag_on(0x448);
        }
        break;
    case 1:
        func_80016D64();
        break;
    }
    if (temp_v1->x15 == 0) {
        gw->stage_no = temp_v1->x16;
        gw->area_no = temp_v1->x17;
        gw->x52 = gw->x53;
        func_80015EE8(&Player_work, temp_v1, 1);
    }
    func_8001F23C();
    gw->routine_0 = 2; // queue up next routine
    gw->x1 = 1;
    gw->x82 = (u8)gw->x82 & 0xFE;
}
// clang-format off
#endif

#ifndef ACCEPT_REORDERING_BULLSHIT
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015840);
#else
void func_80015840(GAME_WORK* arg0) {
    _unkstruc_800C3558* temp_v1 = &D_800C3558;

    switch (arg0->x1) { /* irregular */
    case 0:
        if (temp_v1->x15 == 0) {
            arg0->area_no = (s8)temp_v1->x17;
            arg0->x52 = (s8)(u8)arg0->x53;
            func_80015EE8(&Player_work, &D_800C3558, 1);
        }
        func_80016D64();
        /* fallthrough */
    case 1:
        func_80038648();
        func_8001F3C8();
        temp_v1->x14 = 0;
        arg0->routine_0 = 3;
        arg0->x1 = 0;
        return;
    }
}
// clang-format off
#endif

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800158F0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015DB4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015EE8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015FE8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016160);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016434);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800164B4);

#ifndef ACCEPT_REORDERING_BULLSHIT
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016528);
#else
// clang-format on
void func_80016528(GAME_WORK* arg0) {
    PL_WORK* pp;

    pp = &Player_work;

    switch (arg0->x1) { /* irregular */
    case 0:
        func_8005DF3C();
        pp->xBD |= 0x40;
        MojiTaskKill();
        func_80063EF0();
        func_80017C30(0);
        func_8001B2F0(0x10);
        func_8001B2F0(0x16);
        func_8001B2F0(0x17);
        arg0->x1++;
        break;
    case 1:
        func_8005DF4C();
        if ((D_800C0C2A & 1) || (D_800C0C2A & 0x1000)) {
            Sub_screen_sound_reinit(pp);
            pp->xBD &= 0xBF;
            MojiTaskKill();
            Game_logo_kill(-1);
            arg0->routine_0 = 3;
            arg0->x1 = 1;
        }
        break;
    }
    return;
}

// clang-format off
#endif

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_8001663C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016798);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800169AC);


// clang-format on
void func_80016BC0(void) {
    if (++Game_work.time > 10799999u)
        Game_work.time = 10799999u;
}

// clang-format on
void func_80016BF4(void) {
    if (Game_work.routine_0 >= 3 && Game_work.routine_0 != 6 && !D_80098910) {
        if ((D_800C0C26 & 9) == 9) {
            if (Game_work.xA++ >= 61) {
                *(s8*)0x1F800001 = 2;
                MojiTaskKill();
                func_80063BA8();
                func_80063EF0();
                func_800665E8();
                func_8001B314();
                func_8001B33C();
                func_8001D494(0, 1, 0);
                D_80098A70 = 0;
                func_80017C30(8);
                Sce_flag_off(0x1FEu);
                Code800133D8_work.x0 = 1;
                func_80012F78(func_80013420);
            }
        } else {
            Game_work.xA = 0;
        }
    }
}

// clang-format on
void func_80016D0C(GAME_WORK* arg0) {
    if (D_80098A72 == 0) {
        arg0->x1++;
    }
}

void func_80016D38(GAME_WORK* arg0) { // lol, duplicate function
    if (D_80098A72 == 0) {
        arg0->x1++;
    }
}

// clang-format on
s32 func_80016D64(void) {
    while (D_80098788)
        func_80012E98(1);
    return func_8001B314();
}




void func_80016DAC(void) {
    POLY_FT4* v0;

    v0 = PRIM_PTR_INC(POLY_FT4); // not sure if POLY_FT4
    v0->tag[3] = 9;
    v0->code = 44;
    v0->tpage = GetTPage(0, 0, 320, 256);
    v0->clut = GetClut(0, 496);
    v0->x0 = 32;
    v0->y0 = 56;
    v0->x1 = 287;
    v0->y1 = 56;
    v0->x2 = 32;
    v0->y2 = 184;
    v0->x3 = 287;
    v0->y3 = 184;
    v0->u0 = 0;
    v0->v0 = 0;
    v0->u1 = 255;
    v0->v1 = 0;
    v0->u2 = 0;
    v0->v2 = 0x80;
    v0->u3 = -1;
    v0->v3 = 0x80;
    v0->r0 = 0x80;
    v0->g0 = 0x80;
    v0->b0 = 0x80;
    AddPrim(&D_80098934->x78, v0);
}

void func_80016E90(void) {
    GAME_WORK* gp;
    UNK_PRIM_1* temp_s0;
    UNK_PRIM_1* temp_s0_2;
    gp = &Game_work;

    temp_s0 = PRIM_PTR(UNK_PRIM_1);
    temp_s0->tag[3] = 5;
    temp_s0->code = 40;
    temp_s0->unk8 = 0;
    temp_s0->unkA = 0;
    temp_s0->unkC = 320;
    temp_s0->unkE = 0;
    temp_s0->unk10 = 0;
    temp_s0->unk12 = 120 - gp->x8;
    temp_s0->unk14 = 320;
    temp_s0->unk16 = 120 - gp->x8;
    temp_s0->unk4 = 0;
    temp_s0->unk5 = 0;
    temp_s0->unk6 = 0;
    temp_s0->code &= 0xFD;
    AddPrim(&D_80098934->x74, temp_s0++);
    temp_s0->tag[3] = 5;
    temp_s0->code = 40;
    temp_s0->unk8 = 0;
    temp_s0->unkA = gp->x8 + 119;
    temp_s0->unkC = 320;
    temp_s0->unkE = gp->x8 + 119;
    temp_s0->unk10 = 0;
    temp_s0->unk12 = 240;
    temp_s0->unk14 = 320;
    temp_s0->unk16 = 240;
    temp_s0->unk4 = 0;
    temp_s0->unk5 = 0;
    temp_s0->unk6 = 0;
    temp_s0->code = temp_s0->code & 0xFD;
    AddPrim(&D_80098934->x74, temp_s0++);
    (*(UNK_PRIM_1** )0x1F800070) = temp_s0;
}

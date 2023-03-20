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

// clang-format off

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

// https://decomp.me/scratch/OFeoF
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015634);

// clang-format on
void func_80015734(GAME_WORK* gw) {
    _unkstruc_800C3558* temp_v1 = &D_800C3558;

    switch (gw->x1) {
    case 0:
        func_8001DA8C(0x527);
        if (!((u8)gw->x82 & 1) && (gw->x54[7] == 0)) {
            func_8001DA8C(0x510);
            func_8001DA8C(0x522);
            func_8001DA8C(0x446);
            func_8001DA8C(0x448);
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

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800158F0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015DB4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015EE8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80015FE8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016160);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016434);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800164B4);

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

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_8001663C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016798);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_800169AC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016BC0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016BF4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016D0C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016D38);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016D64);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016DAC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016E90);

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

// clang-format on
void func_80016BC0(void) {
    if (++Game_work.time > 10799999u)
        Game_work.time = 10799999u;
}

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
                func_8001DCD0(0x1FEu);
                Code800133D8_work.x0 = 1;
                func_80012F78(func_80013420);
            }
        } else {
            Game_work.xA = 0;
        }
    }
}
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
s32 func_80016D64(void) {
    while (D_80098788)
        func_80012E98(1);
    return func_8001B314();
}
// clang-format off





INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016DAC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/game", func_80016E90);

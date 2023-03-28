#include "rock_neo.h"

#include "rock_neo/game.h"
#include "rock_neo/cd.h"
#include "rock_neo/moji.h"

// clang-format off

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", main);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", idk_Init_system_maybe);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_800120A8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_8001215C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_800121AC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012298);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_800122D0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012350);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", vsync_cb);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012424);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_8001246C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012938);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012988);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012A5C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012BC4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012C80);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012E10);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012E98);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012ECC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012F24);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012F78);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012FA4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012FC8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_80012FEC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_800130D0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_8001319C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/main", func_800131FC);

void func_8001326C(u8* arg0) {
    unkst_80098A28* var_s0;
    u32 var_s2;

    SetDispMask(1);
    var_s0 = &D_80098A28;
    for (var_s2 = 0; var_s2 < 2; var_s2++) {
        var_s0[var_s2].unk3 = 3;
        var_s0[var_s2].unk7 = 98;
        var_s0[var_s2].unkC = 320;
        var_s0[var_s2].unk8 = 0;
        var_s0[var_s2].unkA = 0;
        var_s0[var_s2].unkE = 240;
        SetDrawMode(&D_80098A10[var_s2], 0, 0, GetTPage(2, 2, 0, 0), 0);
    }
    func_80063EF0();
    func_80053788();
    func_800665E8();
    Cd_read_comb(INIT_DAT_BIN);
    Game_work.x5B = 1;
    *(s8* )0x1F800074 = 0;
    Game_work.x10 = 0;
    Game_work.x14 = 0;
    Game_work.difficultyUnlocked[0] = 0;
    Game_work.difficultyUnlocked[1] = 0;
    Game_work.x54[0] = 0;
    Game_work.x54[1] = 0;
    Game_work.x54[4] = 0;
    Game_work.x54[5] = 0;
    Game_work.x70 = -1;
    Game_work.x72 = -1;
    Game_work.x74 = -1;
    Game_work.x76 = -1;
    *arg0 += 1;
}

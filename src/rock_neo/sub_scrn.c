#include "common.h"

#include "rock_neo/sub_scrn.h"
#include "rock_neo/moji.h"
#include "rock_neo/cd.h"
#include "rock_neo/game.h"

#ifdef TEMP
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005EC34);
#else
void func_8005EC34(void) {
    Sub_screen_back_ground_set();
    D_8008DBB0[D_800A38F0.routine_0](&D_800A38F0);
}
#endif

#if 0
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005EC80);
#else
s32 func_8005EC80(s32* arg0) {
    MojiTaskKill();
    func_8005382C(0, D_8008CB94, -1);
    func_80063FC0(0, 0x20006); // sus second parameter, looks like an enum
    Sub_screen_basic_param_set();
    *arg0 = 1;
    return 0;
}
#endif

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005ECE0); // https://decomp.me/scratch/2QuPj

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005ED9C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F210);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F3D0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F608);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F9E8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FAE4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FBB4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FDE4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FFBC);

#if 0
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_800600CC); // https://decomp.me/scratch/XN3jK
#else
s32 func_800600CC(SUB_SCREEN_WORK* subp) {
    switch (subp->routine_1) {
        case 0:
            {
                MojiTaskKill();
                Game_logo_kill(-1);
                Cd_read_comb(205);
                subp->routine_1++;
                break; 
            }
        case 1:
            {
                if (Cd_read_sync2() != 0)
                {
                    break;
                }
                func_8001D7AC(22);
                func_8005382C(0, 0x801F2000, 0x1D); // ???
                func_80063FC0(2, 0x20007);
                func_800605DC();
                subp->routine_1++;
                break;
            }
        case 2:
            {
                if ((Moji_flag & 0x480000FF) == 0x48000002) {
                    Cd_read_comb(EXIT_SUB_BIN);
                    subp->routine_1++;
                    break;
                }
                if (!(Moji_flag & 0x8000000)) {
                    if (!(Moji_flag3 & 0x10000)){
                        if (Moji_flag3 & 0x80000) {
                            func_80060248(subp);
                        }
                    }
                    else {
                        if (Moji_flag3 & 0x40000) {
                           func_80060248(subp);
                        }
                    }
                }
                func_800605DC();
                Sub_screen_shift_check(subp);
                break;
            }
        case 3:
            {
                if (Cd_read_sync2() == 0) {
                    *(u32*)&subp->routine_0 = 0;
                }
                break;
            }
    }
    return 0;
}
#endif

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_80060248);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_800602A4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_800605DC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_80060618);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_80060B00);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_80060C70);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_80060DB8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_cancel_check);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_shift_check);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sort_attack);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sort_energy);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sort_range);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sort_rapid);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sort_sub);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_rb_parts_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_rb_parts_calc);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_rb_parts_calc_sub00);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_rb_parts_calc_sub01);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_status_calc);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_gauge_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_gauge_set2);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_basic_param_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_basic_param_set_sub);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_status_param_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_status_param_set_sub);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_back_ground_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Sub_screen_sound_reinit);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Map_screen_init);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", Map_screen_task);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", map_screen_set);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", map_cursor_set);

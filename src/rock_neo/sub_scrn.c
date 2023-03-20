#include "common.h"

#include "rock_neo/sub_scrn.h"

#ifdef TEMP
INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005EC34);
#else
void func_8005EC34(void) {
    Sub_screen_back_ground_set();
    D_8008DBB0[D_800A38F0.x0](&D_800A38F0);
}
#endif

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005EC80);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005ECE0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005ED9C);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F210);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F3D0);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F608);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005F9E8);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FAE4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FBB4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FDE4);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_8005FFBC);

INCLUDE_ASM("config/../asm/rock_neo/nonmatchings/sub_scrn", func_800600CC);

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

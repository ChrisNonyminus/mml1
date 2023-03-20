#ifndef ROCK_NEO_PLAYER_H
#define ROCK_NEO_PLAYER_H

#include "rock_neo.h"

typedef struct WPN_DATA {
    s8 attack_level;
    s8 bullet_level;
    s8 dist_level;
    s8 repeat_level;
    s8 unk[0x4];
} WPN_DATA;

extern WPN_DATA Rock_buster_parts_tbl[];

typedef struct PL_WORK {
    u8 x0[0x110];
    s8 x110;
    u8 x111[0x170 - 0x111];
    s8 weapon_right_no;
    u8 x171[0x450 - 0x171];
    u8 rb_parts_equip_data[4];
    u8 rb_parts_sort_data[0x454 + 0x20 - 0x454];
    u8 x474[0x474 + 0x80 - 0x474];
    WPN_DATA weapon_data[2];
} PL_WORK;
extern PL_WORK Player_work;

unknown_t Pl00_shot_enable_off(PL_WORK*);
unknown_t Pl00_shot_enable_on(PL_WORK*);

#define PL_KEY_ITEM_06 0x526

#endif

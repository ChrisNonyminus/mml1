#ifndef ROCK_NEO_PLAYER_H
#define ROCK_NEO_PLAYER_H

#include "rock_neo.h"

typedef struct BUSTER_PART {
  s8 x0[0x7];
  s8 attack_level;
} BUSTER_PART;

extern BUSTER_PART Rock_buster_parts_tbl[];

typedef struct PL_WORK {
  u8 x0[0x110];
  s8 x110;
  u8 x111[0x170 - 0x111];
  s8 weapon_right_no;
  u8 x171[0x450 - 0x171];
  u8 rb_parts_equip_data[4];
  u8 x454[0x500 - 0x454];
} PL_WORK;
extern PL_WORK Player_work;

unknown_t Pl00_shot_enable_off(PL_WORK *);
unknown_t Pl00_shot_enable_on(PL_WORK *);

#endif

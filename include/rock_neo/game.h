#ifndef ROCK_NEO_GAME_H
#define ROCK_NEO_GAME_H

#include "rock_neo.h"

void Game_logo_kill(unknown_t);

typedef struct GAME_WORK {
    u8 x0[0x50];
    s8 stage_no, area_no;
} GAME_WORK;

extern GAME_WORK Game_work;

extern void (*Game_main_tbl[])(GAME_WORK*);

#endif

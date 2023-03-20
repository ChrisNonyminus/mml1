#ifndef ROCK_NEO_SUB_SCRN_H
#define ROCK_NEO_SUB_SCRN_H

#include "rock_neo.h"

void Sub_screen_back_ground_set();                     /* 0x80062368 */
typedef struct _struc_800A38F0 {
    s8 x0;
} _struc_800A38F0;
extern void (*D_8008DBB0[])(_struc_800A38F0*) ;


extern _struc_800A38F0 D_800A38F0;

void func_8005EC34(void);

#endif

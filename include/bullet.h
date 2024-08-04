#ifndef _BULLET_
#define _BULLET_

#include "struct.h"

#define NUMBER_OF_BULLETS 4
#define BULLET_COOLDOWN 25
#define MAX_BULLET 64

bullet create_ammo();
bullet * create_ammo_belt();
bullet set_y(bullet b);
int is_any_bullet_left(bullet *b, int size);
void free_ammo_belt(bullet *ammo_belt);

#endif

#ifndef _HERO_
#define _HERO_

#include "struct.h"

hero *create_hero();
void free_hero(hero *protagonist);
int find_player(int x, int y, hero * player);
void hasBeenHit(hero *protagonist);
int isAlive(hero *protagonist);
void add_points(hero *protagonist);
void collision(hero *protagonist);
void setXAndY(hero *protagonist);
int hero_loop(hero *h, enemy ** enemies, bullet * ammo_belt);

#endif

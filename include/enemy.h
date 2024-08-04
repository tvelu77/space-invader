#ifndef _ENEMY_
#define _ENEMY_

#define NUMBER_OF_ENEMIES_X_AXIS 25
#define NUMBER_OF_ENEMIES_Y_AXIS 10

void fill_enemy_array(enemy * enemy_list[]);
enemy ** create_enemy_array();
void draw_enemies(enemy ** enemy_list, MLV_Image ** image);
int find_enemy(int x, int y, enemy ** enemies);
void moving_enemy(enemy ** array);
void enemies_loop(enemy ** enemies, hero *player, MLV_Image **images, bullet * ammo_belt);
void free_enemy_array(enemy ** array);


#endif

#ifndef _INTERFACE_
#define _INTERFACE_

#define HEIGHT_WINDOWS_PIX 600
#define WIDTH_WINDOWS_PIX 800
#define ENEMY_WIDTH (WIDTH_WINDOWS_PIX * 80 / 100) / 20

#define WAIT_TIME_MILLISEC 17

#include "hero.h"

void create_windows();
void free_windows();
void actualise_window();
void clear_window();
void pause_action();
void draw_hero(int x, int y, int width, int height);
void draw_bullet(int x, int y, int width, int height);
void create_title_text();
void draw_options(int number_of_options, char *options[number_of_options], int choosen_option);
void draw_scoreboard(char **scoreboard);
void draw_fps(int fps);
void create_win_text(int score);
MLV_Image *load_and_resize(char *directory);
void draw_infos_in_header(hero *h);
#endif

#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "interface.h"
#include "enemy.h"
#include "hero.h"
#include "bullet.h"
#include "gamedata.h"
#include "option.h"
#include "gamemaster.h"

void scoreboard_loop(char **scoreboard){
  while(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) != MLV_PRESSED){
    actualise_window();
    clear_window();
    draw_scoreboard(scoreboard);
  }
}

void game_over(hero *h){
  char ** scoreboard = create_scoreboard_array();
  check_scoreboard(scoreboard, h->score);
  scoreboard_loop(scoreboard);
  free_scoreboard(scoreboard);
}

int pause_screen(){
  title_screen_option *ts = create_pause_options();
  int choice;
  while(1){
    actualise_window();
    clear_window();
    create_title_text();
    switch(choice = pause_screen_loop(ts)){
      case 0:
        return 1;
      case 1:
        free_title_screen(ts);
        return 0;
    }
  }
}

/* La boucle du jeu */
int game_loop(){
  hero *h = create_hero();
  bullet * hero_ammo_belt = create_ammo_belt();
  enemy ** enemies = create_enemy_array();
  bullet * enemies_ammo_belt = create_ammo_belt();
  fill_enemy_array(enemies);
  MLV_Image **image_array = create_image_array();
  while(1){
    if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED){
      if (!pause_screen()){
        break;
      }
    }
    draw_infos_in_header(h);
    actualise_window();
    clear_window();
    if(hero_loop(h, enemies, hero_ammo_belt)){
      game_over(h);
      break;
    }
    enemies_loop(enemies, h, image_array, enemies_ammo_belt);
    MLV_delay_according_to_frame_rate();
  }
  free_enemy_array(enemies);
  free_hero(h);
  free_ammo_belt(hero_ammo_belt);
  free_ammo_belt(enemies_ammo_belt);
  free_image(image_array);
  return 0;
}

int title_screen_options(){
  char ** scoreboard = create_scoreboard_array();
  title_screen_option *ts = create_options();
  int choice;
  while(1){
    actualise_window();
    clear_window();
    switch(choice = title_screen_loop(ts)){
      case 0:
        break;
      case 1:
        scoreboard_loop(scoreboard);
        break;
      case 2:
        free_title_screen(ts);
        free_scoreboard(scoreboard);
        goto exit_loop;
        break;
    }
  }
  exit_loop: ;
  return 1;
}

int title_screen(){
  title_screen_option *ts = create_menu_options();
  int choice;
  while(1){
    actualise_window();
    clear_window();
    create_title_text();
    switch(choice = title_screen_loop(ts)){
      case 0:
        game_loop();
        break;
      case 1:
        title_screen_options();
        break;
      case 2:
        free_title_screen(ts);
        MLV_free_window();
        return 0;
    }
  }
  return 1;
}

void init_process(){
  srand(time(NULL));
  create_windows();
  MLV_change_frame_rate ( 60 );
  actualise_window();
  title_screen();
}

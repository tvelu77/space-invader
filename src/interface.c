#include <MLV/MLV_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "enemy.h"
#include "hero.h"

#define GAME_NAME "TnT's Space Invader"

void create_windows(void){
  MLV_create_window(GAME_NAME, NULL, WIDTH_WINDOWS_PIX, HEIGHT_WINDOWS_PIX);
}

void free_windows(void){
  MLV_free_window();
}

void actualise_window(void){
  MLV_actualise_window();
}

void clear_window(void){
  MLV_clear_window(MLV_rgba(0,0,0,255));
}

void pause_action(void){
  MLV_wait_milliseconds(WAIT_TIME_MILLISEC);
}

void draw_hero(int x, int y, int width, int height){
  MLV_draw_rectangle(x, y, width, height, MLV_COLOR_WHITE);
}

void draw_bullet(int x, int y, int width, int height){
  MLV_draw_rectangle(x, y, width, height, MLV_COLOR_WHITE);
}

void create_title_text(){
  char string[64];
  sprintf(string, GAME_NAME);
  int width, height;
  MLV_get_size_of_adapted_text_box(string, 9, &width, &height);
  MLV_draw_adapted_text_box((WIDTH_WINDOWS_PIX-width)/2, height, string, 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
}

void draw_fps(int fps){
  char end_string[64];
  sprintf(end_string, "%d", fps);
  int width, height;
  MLV_get_size_of_adapted_text_box(end_string, 9, &width, &height);
  MLV_draw_adapted_text_box(WIDTH_WINDOWS_PIX-width, HEIGHT_WINDOWS_PIX-height, end_string, 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
}

void draw_options(int number_of_options, char *options[number_of_options], int choosen_option){
  int i;
  int separation = HEIGHT_WINDOWS_PIX/20;
  int width, height;
  for(i = 0; i < number_of_options; i++){
    MLV_get_size_of_adapted_text_box(options[i], 9, &width, &height);
    if(i == choosen_option){
      MLV_draw_adapted_text_box((WIDTH_WINDOWS_PIX-width)/2, ((HEIGHT_WINDOWS_PIX-height)/4)+separation, options[i], 9, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    }
    else{
      MLV_draw_adapted_text_box((WIDTH_WINDOWS_PIX-width)/2, ((HEIGHT_WINDOWS_PIX-height)/4)+separation, options[i], 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    }
    separation += HEIGHT_WINDOWS_PIX/25;
  }
}

void draw_scoreboard(char **scoreboard){
  int i;
  int separation = HEIGHT_WINDOWS_PIX/20;
  int width, height;
  if(scoreboard == NULL){
    char *error = "Le fichier scoreboard est inexistant, désolé :(";
    MLV_get_size_of_adapted_text_box(error, 9, &width, &height);
    MLV_draw_adapted_text_box((WIDTH_WINDOWS_PIX-width)/2, ((HEIGHT_WINDOWS_PIX-height)/4)+separation, error, 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    return;
  }
  for(i = 0; i < 10; i++){
    MLV_get_size_of_adapted_text_box(scoreboard[i], 9, &width, &height);
    MLV_draw_adapted_text_box((WIDTH_WINDOWS_PIX-width)/2, ((HEIGHT_WINDOWS_PIX-height)/4)+separation, scoreboard[i], 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    separation += HEIGHT_WINDOWS_PIX/25;
  }
}

void create_win_text(int score){
  char end_string[64];
  sprintf(end_string, "%d", score);
  int width, height;
  MLV_get_size_of_adapted_text_box(end_string, 9, &width, &height);
  MLV_draw_adapted_text_box(WIDTH_WINDOWS_PIX/2, HEIGHT_WINDOWS_PIX/2, end_string, 9, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
}

void resize_image(MLV_Image *image){
  MLV_resize_image_with_proportions(image, ENEMY_WIDTH, ENEMY_WIDTH);
}

MLV_Image *load_image(char *directory){
  return MLV_load_image(directory);
}

MLV_Image *load_and_resize(char *directory){
  MLV_Image *final_image = load_image(directory);
  resize_image(final_image);
  return final_image;
}


void draw_infos_in_header(hero *h){
  char str1[64];
  sprintf(str1, "Score : %d", h->score);
  MLV_draw_text(600,5,str1,MLV_COLOR_BLACK );


  char str2[64];
  sprintf(str2, "Vies restantes : %d", h->life);
  MLV_draw_text(600,25,str2,MLV_COLOR_BLACK );



  MLV_draw_text(200,20,GAME_NAME,MLV_COLOR_BLACK );
}

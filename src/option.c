/* Ce fichier représente les options du jeu */

#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>

#include "option.h"
#include "interface.h"

#define COOLDOWN 150

/* Créer le tableau des options */
title_screen_option *create_menu_options(){
  title_screen_option *ts = malloc(sizeof(title_screen_option));
  ts->size = 3;
  ts->time_start = MLV_get_time();
  ts->time_end = 0;
  ts->options = malloc(sizeof(char*)*ts->size);
  int i;
  for(i = 0; i < ts->size; i++){
    switch(i){
      case 0:
        ts->options[i] = "JOUER";
        break;
      case 1:
        ts->options[i] = "OPTIONS";
        break;
      case 2:
        ts->options[i] = "QUITTER";
        break;
    }
  }
  ts->current_choice = 0;
  return ts;
}

/* Créer le tableau des options dans la section option */
title_screen_option *create_options(){
  title_screen_option *ts = malloc(sizeof(title_screen_option));
  ts->size = 3;
  ts->time_start = MLV_get_time();
  ts->time_end = 0;
  ts->options = malloc(sizeof(char*)*ts->size);
  int i;
  for(i = 0; i < ts->size; i++){
    switch(i){
      case 0:
        ts->options[i] = "AFFICHER FPS";
        break;
      case 1:
        ts->options[i] = "TABLEAU DES SCORES";
        break;
      case 2:
        ts->options[i] = "RETOUR";
        break;
    }
  }
  ts->current_choice = 0;
  return ts;
}


title_screen_option *create_pause_options(){
  title_screen_option *ts = malloc(sizeof(title_screen_option));
  ts->size = 2;
  ts->time_start = MLV_get_time();
  ts->time_end = 0;
  ts->options = malloc(sizeof(char*)*ts->size);
  int i;
  for(i = 0; i < ts->size; i++){
    switch(i){
      case 0:
        ts->options[i] = "REPRENDRE";
        break;
      case 1:
        ts->options[i] = "MENU PRINCIPAL";
        break;

    }
  }
  ts->current_choice = 0;
  return ts;
}

void user_input(title_screen_option *ts){
  if(MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED && ts->time_end - ts->time_start > COOLDOWN){
    ts->time_start = MLV_get_time();
    ts->current_choice--;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED && ts->time_end - ts->time_start > COOLDOWN){
    ts->time_start = MLV_get_time();
    ts->current_choice++;
  }
  if(ts->current_choice >= ts->size){
    ts->current_choice = 0;
  }
  if(ts->current_choice < 0){
    ts->current_choice = ts->size-1;
  }
}

int title_screen_loop(title_screen_option *ts){
  ts->time_end = MLV_get_time();
  user_input(ts);
  draw_options(ts->size, ts->options, ts->current_choice);
  if(MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) == MLV_PRESSED && ts->has_pushed_return == 0 && ts->time_end - ts->time_start > COOLDOWN){
    ts->has_pushed_return = 1;
    return ts->current_choice;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED && ts->has_pushed_return == 0 && ts->time_end - ts->time_start > COOLDOWN){
    ts->has_pushed_return = 1;
    return ts->current_choice = ts->size-1;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) != MLV_PRESSED && MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) != MLV_PRESSED){
    ts->has_pushed_return = 0;
  }
  return -1;
}

int pause_screen_loop(title_screen_option *ts){
  ts->time_end = MLV_get_time();
  user_input(ts);
  draw_options(ts->size, ts->options, ts->current_choice);
  if(MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) == MLV_PRESSED && ts->has_pushed_return == 0 && ts->time_end - ts->time_start > COOLDOWN){
    ts->has_pushed_return = 1;
    return ts->current_choice;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED && ts->has_pushed_return == 0 && ts->time_end - ts->time_start > COOLDOWN){
    ts->has_pushed_return = 1;
    return ts->current_choice = 0;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_RETURN) != MLV_PRESSED && MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) != MLV_PRESSED){
    ts->has_pushed_return = 0;
  }
  return -1;
}

void free_title_screen(title_screen_option *ts){
  free(ts->options);
  free(ts);
}

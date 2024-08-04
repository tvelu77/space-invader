#ifndef _OPTION_
#define _OPTION_

#define NUMBER_OF_OPTIONS 3

typedef struct{
  char **options;
  int size;
  int current_choice;
  int has_pushed_return;
  int time_start;
  int time_end;
} title_screen_option;

title_screen_option *create_menu_options();

title_screen_option *create_options();
title_screen_option *create_pause_options();


int title_screen_loop(title_screen_option *ts);
int pause_screen_loop(title_screen_option *ts);

void free_title_screen(title_screen_option *ts);

#endif

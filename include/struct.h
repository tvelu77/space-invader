#ifndef _STRUCT_
#define _STRUCT_

typedef struct{
  int pos_x;
  int pos_y;
  int width;
  int life;
  int has_shot;
} enemy;

typedef struct{
  int width;
  int height;
  int pos_x;
  int pos_y;
  int v_x;
  int life;
  int score;
  int has_shot;
} hero;

typedef struct{
  int width;
  int height;
  int pos_x;
  int pos_y;
  int v_y;
} bullet;

#endif

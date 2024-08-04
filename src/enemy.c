#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "enemy.h"
#include "bullet.h"
#include "interface.h"

#define time_between_moves 400


clock_t last_move = 0, new_frame;
int msec = 256;
int go_right = 1; /*defini le sens de déplacement : 1 pour la droite, 0 pour la gauche*/


/* Créer un enemy */
enemy create_enemy(int x, int y, int life){
  enemy e;
  e.pos_x = x;
  e.pos_y = y;
  e.width = (WIDTH_WINDOWS_PIX * 80 / 100) / 20;
  e.life = life;
  e.has_shot = 0;
  return e;
}

enemy ** create_enemy_array(){
  enemy ** array = (enemy**)malloc(sizeof(enemy)*NUMBER_OF_ENEMIES_Y_AXIS);
  int i = 0;
  for(i = 0; i < NUMBER_OF_ENEMIES_Y_AXIS; i++){
    array[i] = (enemy*)malloc(sizeof(enemy)*NUMBER_OF_ENEMIES_X_AXIS);
  }
  return array;
}

void fill_enemy_array(enemy ** array){
  int i,j;
  for (i = 0; i<NUMBER_OF_ENEMIES_Y_AXIS; i++){
    for (j=0;j<NUMBER_OF_ENEMIES_X_AXIS;j++){
      int r = rand() % 4;
      int true_or_false = rand() % 2;
      if(i == 0 || i > NUMBER_OF_ENEMIES_Y_AXIS / 2 || j == 0 || j == NUMBER_OF_ENEMIES_X_AXIS-1){
        array[i][j] = create_enemy(0, 0, 0);
      }
      else{
        if(true_or_false){
          array[i][j] = create_enemy(0, 0, r);
        }
        else{
          array[i][j] = create_enemy(0, 0, 0);
        }
      }
    }
  }
}

/* Cherche un enemy d'après une position x et y du bullet */
int find_enemy(int x, int y, enemy ** enemies){
  int y_axis, x_axis;
  for(y_axis = NUMBER_OF_ENEMIES_Y_AXIS-1; y_axis >= 0; y_axis--){
    for(x_axis = NUMBER_OF_ENEMIES_X_AXIS-1; x_axis >= 0; x_axis--){
      if((x >= enemies[y_axis][x_axis].pos_x && x <= enemies[y_axis][x_axis].pos_x + enemies[y_axis][x_axis].width) && (y >= enemies[y_axis][x_axis].pos_y && y <= enemies[y_axis][x_axis].pos_y + enemies[y_axis][x_axis].width) && (enemies[y_axis][x_axis].life != 0)){
        enemies[y_axis][x_axis].life -= 1;
        return 1;
      }
    }
  }
  return 0;
}

/* Dessine les ennemis, si aucun ennemi a été dessiné alors, la fonction renvoie un pour dire que le jeu est terminé (permet d'éviter une boucle de vérification en plus)*/
void draw_enemies(enemy ** enemy_list, MLV_Image **image){
  int border_score = WIDTH_WINDOWS_PIX / 16;
  int max_width = WIDTH_WINDOWS_PIX * 80 / 100;
  int enemy_size = max_width / 20;
  int i,j;
  MLV_draw_filled_rectangle(0,0,WIDTH_WINDOWS_PIX,border_score,MLV_COLOR_CYAN3);

  for (j = 0; j < NUMBER_OF_ENEMIES_Y_AXIS; j++){
    for (i = 0; i < NUMBER_OF_ENEMIES_X_AXIS; i++){
      if (enemy_list[j][i].life == 0){
        /*MLV_draw_rectangle(0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20, enemy_size,  enemy_size,MLV_COLOR_WHITE);*/
      }
      else if (enemy_list[j][i].life == 1){
        MLV_draw_image( image[0], 0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20);
        /*MLV_draw_rectangle(0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20, enemy_size,  enemy_size,MLV_COLOR_WHITE);*/
        enemy_list[j][i] = create_enemy(0 + i * enemy_size, 0 + (j*enemy_size) + border_score + 20, 1);
      }

    else if (enemy_list[j][i].life == 2){
        MLV_draw_image( image[1], 0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20);
        /*MLV_draw_rectangle(0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20, enemy_size,  enemy_size,MLV_COLOR_WHITE);*/
        enemy_list[j][i] = create_enemy(0 + i * enemy_size, 0 + (j*enemy_size) + border_score + 20, 2);
      }

      else if (enemy_list[j][i].life == 3){
        MLV_draw_image( image[2], 0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20);
        /*MLV_draw_rectangle(0 + i * enemy_size , 0 + (j*enemy_size) + border_score + 20, enemy_size,  enemy_size,MLV_COLOR_WHITE);*/
        enemy_list[j][i] = create_enemy(0 + i * enemy_size, 0 + (j*enemy_size) + border_score + 20, 3);
      }
    }
  }
}

/* Initialise la position de la balle et sa vitesse */
bullet shot_by_enemy(bullet b, enemy e){
  b.width = e.width/10;
  b.height = e.width/10;
  b.pos_x = e.pos_x+e.width/2;
  b.pos_y = e.pos_y+e.width;
  b.v_y = 2;
  return b;
}

/* Permet aux ennemies de tirer aléatoirement, la fonction est très très sale, O(n^3) */
void shooting(enemy ** array, bullet * ammo_belt){
  int i = 0;
  int j = 0;
  int bullet = 0;
  int is_enemy_in_line = 0;
  for(j = NUMBER_OF_ENEMIES_Y_AXIS - 1; j > 0; j--){
    if(is_enemy_in_line){
      break;
    }
    for(i = 0; i < NUMBER_OF_ENEMIES_X_AXIS; i++){
      if(array[j][i].life != 0){
        int r = rand() % 1000;
        if(r < 1){
          while(ammo_belt[bullet].v_y != 0){
            bullet++;
            if(bullet > MAX_BULLET){
              return;
            }
          }
          ammo_belt[bullet] = shot_by_enemy(ammo_belt[bullet], array[j][i]);
          return;
        }
      }
    }
  }
}

void pushing(enemy ** e){
  int i = 0;
  for(i = 0; i < NUMBER_OF_ENEMIES_X_AXIS; i++){
    if(e[1][i].life != 0){
      return;
    }
  }
  for(i = 0; i < NUMBER_OF_ENEMIES_X_AXIS; i++){
    int r = rand() % 4;
    int true_or_false = rand() % 2;
    if(i == 0 || i == NUMBER_OF_ENEMIES_X_AXIS-1){
      e[1][i] = create_enemy(0, 0, 0);
    }
    else{
      if(true_or_false){
        e[1][i] = create_enemy(0, 0, r);
      }
      else{
        e[1][i] = create_enemy(0, 0, 0);
      }
    }
  }
}

/* Si la balle est sortie de l'écran, ou a touché le joueur */
int is_enemy_bullet_out(hero * h, bullet b, enemy ** enemies){
  if(b.v_y == 0){
    return 0;
  }
  if(b.pos_y >= HEIGHT_WINDOWS_PIX){
    return 1;
  }
  if(find_player(b.pos_x, b.pos_y, h) == 1){
    return 1;
  }
  return 0;
}

void bullet_loop_enemies(enemy ** e, hero * player, bullet * ammo_belt){
  int i = 0;
  for(i = 0; i < MAX_BULLET; i++){
    if(ammo_belt[i].v_y == 0){
      continue;
    }
    if(is_enemy_bullet_out(player, ammo_belt[i], e) == 1){
      ammo_belt[i] = create_ammo();
    }
    draw_bullet(ammo_belt[i].pos_x, ammo_belt[i].pos_y, ammo_belt[i].width, ammo_belt[i].height);
    ammo_belt[i] = set_y(ammo_belt[i]);
  }
}

void moving_enemy(enemy ** array){





  new_frame = clock();
  if(last_move != -1){
    msec = (new_frame-last_move) * 1000 / CLOCKS_PER_SEC;
  }


  /*Si l'on se déplace vers la droite*/
  if (go_right == 1){
    /*verifie si aucun ennemi n'est tout a droite*/
    int i=0, j=0;
    int verify_right = 1, verify_bottom = 1;
    for (i=0; i<NUMBER_OF_ENEMIES_Y_AXIS;i++){

      if (array[i][24].life != 0){

        verify_right = 0;
      }
    }

    /*decale à droite*/
    if (verify_right == 1 && msec > time_between_moves){
      for (i = 0 ; i < NUMBER_OF_ENEMIES_Y_AXIS; i++){
        for (j = NUMBER_OF_ENEMIES_X_AXIS -1 ; j > 0 ; j--){
          array[i][j] = array[i][j-1];
        }
        array[i][0].life = 0;
      }
      last_move = clock();
    }

    /*descend d'un rang car un ennemi est a droite*/
    else if (!verify_right && msec > time_between_moves ){
      for ( i=0; i<NUMBER_OF_ENEMIES_X_AXIS;i++){
        if (array[9][i].life != 0){
          verify_bottom = 0;
        }
      }
      if (verify_bottom){
        for (i = NUMBER_OF_ENEMIES_Y_AXIS -1; i>0; i--){
          for (j = 0; j < NUMBER_OF_ENEMIES_X_AXIS ; j++){

            array[i][j] = array[i-1][j];

          }
        }
        last_move = clock();
        go_right = 0;
      }
      else {
        go_right = 0;
      }

    }



  }
  else if (go_right == 0){
    /*verifie si aucun ennemi n'est tout a gauche*/
    int i=0, j=0;
    int verify_left = 1, verify_bottom = 1;
    for (i=0; i<NUMBER_OF_ENEMIES_Y_AXIS;i++){

      if (array[i][0].life != 0){

        verify_left = 0;
      }
    }

    /*decale à droite*/
    if (verify_left == 1 && msec > time_between_moves){
      for (i = 0 ; i < NUMBER_OF_ENEMIES_Y_AXIS; i++){
        for (j = 0; j< NUMBER_OF_ENEMIES_X_AXIS -1 ; j++){
          array[i][j] = array[i][j+1];
        }
        array[i][24].life = 0;
      }



      last_move = clock();
    }

    /*descend d'un rang car un ennemi est a gauche*/
    else if (!verify_left && msec > time_between_moves ){
      for ( i=0; i<NUMBER_OF_ENEMIES_X_AXIS;i++){
        if (array[9][i].life != 0){
          verify_bottom = 0;
        }
      }
      if (verify_bottom){
        for (i = NUMBER_OF_ENEMIES_Y_AXIS -1; i>0; i--){
          for (j = 0; j < NUMBER_OF_ENEMIES_X_AXIS ; j++){

            array[i][j] = array[i-1][j];

          }
        }
        last_move = clock();
        go_right = 1;
      }
      else {
        go_right = 1;
      }

    }
  }
}

void enemies_loop(enemy ** enemies, hero * player, MLV_Image **images, bullet * ammo_belt){
  draw_enemies(enemies, images);
  moving_enemy(enemies);
  shooting(enemies, ammo_belt);
  bullet_loop_enemies(enemies, player, ammo_belt);
  pushing(enemies);
}

void free_enemy_array(enemy ** enemies){
  int i = 0;
  for(i = 0; i < NUMBER_OF_ENEMIES_Y_AXIS; i++){
    free(enemies[i]);
  }
  free(enemies);
}

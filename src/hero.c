/* Ce fichier représente le héros du jeu, c'est-à-dire, l'utilisateur */

#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "enemy.h"
#include "bullet.h"
#include "interface.h"

/* Crée le personnage principal */
hero *create_hero(){
  hero *h = (hero *)malloc(sizeof(hero));
  h->width = WIDTH_WINDOWS_PIX/25;
  h->height = HEIGHT_WINDOWS_PIX/25;
  h->pos_x = WIDTH_WINDOWS_PIX/2 - h->width;
  h->pos_y = (HEIGHT_WINDOWS_PIX*0.9) - h->height;
  h->v_x = 0;
  h->life = 3;
  h->score = 0;
  h->has_shot = 0;
  return h;
}

/* Permet de libérer la mémoire alloué au personnage principal */
void free_hero(hero *h){
  free(h);
}

/* Donne des points au joueur pour la destruction d'ennemi */
void add_points(hero *h){
  h->score += 25;
}

/* Permet de gérer le cas où le personnage est touché */
void has_been_hit(hero *h){
  h->life -= 1;
}

/* Initialise la position de la balle et sa vitesse */
bullet shot_by_hero(bullet b, hero *h){
  b.width = h->width/10;
  b.height = h->height/10;
  b.pos_x = h->pos_x+h->width/2;
  b.pos_y = h->pos_y-b.height;
  b.v_y = -4;
  return b;
}

/* Le héros tire, la balle est alors dessiné et en mouvement */
void shoot(hero * h, bullet * ammo_belt){
  int i = 0;
  while(ammo_belt[i].v_y != 0){
    i++;
    if(i > MAX_BULLET){
      return;
    }
  }
  ammo_belt[i] = shot_by_hero(ammo_belt[i], h);
}

/* Si la balle est sortie de l'écran, ou a touché un ennemi TODO */
int is_hero_bullet_out(hero *h, bullet b, enemy ** enemies){
  if(b.v_y == 0){
    return 0;
  }
  if(b.pos_y <= WIDTH_WINDOWS_PIX / 16){
    return 1;
  }
  if(find_enemy(b.pos_x, b.pos_y, enemies) == 1){
    add_points(h);
    return 1;
  }
  return 0;
}

int find_player(int x, int y, hero * player){
  if((x >= player->pos_x && x <= player->pos_x + player->width) && (y >= player->pos_y && y <= player->pos_y + player->width) && (player->life != 0)){
    player->life -= 1;
    return 1;
  }
  return 0;
}

/* Gère les collisions */
void collision(hero *h){
  if((h->pos_x + h->width >= WIDTH_WINDOWS_PIX-1) && (h->v_x > 0)){
    h->v_x = 0;
  }
  if((h->pos_x <= 1) && (h->v_x < 0)){
    h->v_x = 0;
  }

}

/* Regarde les touches FLECHE GAUCHE/DROITE et ESPACE pour soit se déplacer, soit tirer */
void input(hero *h, bullet * ammo_belt){
  if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED && h->has_shot == 0){
    h->has_shot = 1;
    shoot(h, ammo_belt);
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED){
    h->v_x = -3;
  }
  else if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED){
    h->v_x = 3;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) != MLV_PRESSED){
    h->has_shot = 0;
  }
  if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) != MLV_PRESSED && MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) != MLV_PRESSED){
    h->v_x = 0;
  }
}

/* Change la position du personnage en fonction de la vitesse */
void set_x(hero *h){
  h->pos_x += h->v_x;
}

/* Boucle pour les balles du héros, complexité O(n) */
void bullet_loop_for_hero(hero *h, enemy ** enemies, bullet * ammo_belt){
  int i;
  for(i = 0; i < MAX_BULLET; i++){
    if(is_hero_bullet_out(h, ammo_belt[i], enemies) == 1){
      ammo_belt[i] = create_ammo();
    }
    if(ammo_belt[i].v_y != 0){
      draw_bullet(ammo_belt[i].pos_x, ammo_belt[i].pos_y, ammo_belt[i].width, ammo_belt[i].height);
      ammo_belt[i] = set_y(ammo_belt[i]);
    }
  }
}

/* Boucle principal du hero */
int hero_loop(hero *h, enemy ** enemies, bullet * ammo_belt){
  input(h, ammo_belt);
  collision(h);
  set_x(h);
  bullet_loop_for_hero(h, enemies, ammo_belt);
  draw_hero(h->pos_x, h->pos_y, h->width, h->height);
  if(h->life == 0){
    return 1;
  }
  return 0;
}

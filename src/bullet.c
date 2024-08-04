/* Ce fichier représente les balles des ennemies ou du héros */

#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>

#include "bullet.h"

/* Crée une balle */
bullet create_ammo(){
  bullet b;
  b.width = -1;
  b.height =-1;
  b.pos_x = -1;
  b.pos_y = -1;
  b.v_y = 0;
  return b;
}

bullet * create_ammo_belt(){
  bullet * ammo_belt = (bullet*)malloc(sizeof(bullet)*MAX_BULLET);
  int i = 0;
  for(i = 0; i < MAX_BULLET; i++){
    ammo_belt[i] = create_ammo();
  }
  return ammo_belt;
}

/* Regarde si le joueur/ennemi a encore des munitions et renvoie l'index de la balle disponible, retourne -1 si aucune balle disponible */
int is_any_bullet_left(bullet *b, int size){
  int i;
  for(i = 0; i < size; i++){
    if(b[i].pos_x == -1){
      return i;
    }
  }
  return -1;
}

/* Modifie la position de la balle avec la vitesse donnée */
bullet set_y(bullet b){
  b.pos_y += b.v_y;
  return b;
}

/* Libère la mémoire attribué pour les balles */
void free_ammo_belt(bullet *ammo_belt){
  free(ammo_belt);
}

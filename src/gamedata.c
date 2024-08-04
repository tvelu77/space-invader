#define  _GNU_SOURCE
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>

#include "interface.h"

#define NUMBER_OF_LINES 10
#define MAX_CHAR 256

/* Lit le directoire gamedata/pictures pour créer un tableau d'images utilisables par le jeu */
MLV_Image **create_image_array(){
  char **found;
  glob_t gstruct;
  int r = 0;
  int i = 0;

  r = glob("gamedata/pictures/*.png", GLOB_ERR , NULL, &gstruct);
  /* Vérification pour les erreurs */
  if(r!=0){
    /* Nous n'avons pas trouvé d'images en .png */
    if(r==GLOB_NOMATCH){
      fprintf(stderr,"No matches ! No png found in gamedata/pictures\n");
      return NULL;
    }
    /* La librairie glob a eu un bug */
    else{
      fprintf(stderr, "Error when reading the files, please launch the program again\n");
      exit(1);
    }
  }
  /* Normalement, nous avons trouvé les images png */
  MLV_Image **image_array = malloc(sizeof(MLV_Image*)*gstruct.gl_pathc);
  found = gstruct.gl_pathv;
  while(*found){
    image_array[i] = load_and_resize(*found);
    found++;
    i++;
  }
  return image_array;
}

char **create_scoreboard_array(){
  FILE *file;
  file = fopen("gamedata/scoreboard/scoreboard.txt", "r");
  if(file == NULL){
    return NULL;
  }
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  char **scoreboard = malloc(sizeof(char*)*NUMBER_OF_LINES);
  while((read = getline(&line, &len, file)) != -1 || i < NUMBER_OF_LINES){
    scoreboard[i] = malloc(MAX_CHAR);
    strcpy(scoreboard[i], line);
    i++;
  }
  fclose(file);
  return scoreboard;
}

void rewrite_file(char **scoreboard){
  if(scoreboard == NULL){
    return;
  }
  FILE *file;
  file = fopen("gamedata/scoreboard/scoreboard.txt", "w");
    if(file == NULL){
    return;
  }
  int i = 0;
  while(i < NUMBER_OF_LINES){
    fprintf(file, "%s", scoreboard[i]);
    i++;
  }
  fclose(file);
}

void check_scoreboard(char **scoreboard, int score){
  if(scoreboard == NULL){
    return;
  }
  int i = 0;
  int line_has_been_changed = 0;
  char *score_string = (char*)malloc(MAX_CHAR*2);
  char *changed_score = (char*)malloc(MAX_CHAR*2);
  char *last_line = (char*)malloc(MAX_CHAR*2);
  char *temp = (char*)malloc(MAX_CHAR*2);
  while(i < NUMBER_OF_LINES){
    int range = 7;
    strncpy(score_string, (scoreboard[i])+range, MAX_CHAR - range);
    int score_int = atoi(score_string);
    if(score_int < score && line_has_been_changed == 0){
      strcpy(last_line, scoreboard[i]);
      sprintf(changed_score, "%d\n", score);
      strncpy((scoreboard[i])+range, changed_score, MAX_CHAR - range);
      line_has_been_changed = 1;
    }
    if(line_has_been_changed == 1){
      if(i+1 >= NUMBER_OF_LINES){
        break;
      }
      strcpy(temp, scoreboard[i+1]);
      strcpy(scoreboard[i+1], last_line);
      strcpy(last_line, temp);
    }
    i++;
  }
  free(score_string);
  free(changed_score);
  free(last_line);
  free(temp);
  rewrite_file(scoreboard);
}

void free_image(MLV_Image **array){
  free(array);
}

void free_scoreboard(char **strings){
  int i;
  for(i = 0; i < NUMBER_OF_LINES; i++){
    free(strings[i]);
  }
  free(strings);
}

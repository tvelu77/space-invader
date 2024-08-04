#ifndef _GAMEDATA_
#define _GAMEDATA_

MLV_Image **create_image_array();
char **create_scoreboard_array();
int check_scoreboard(char **scoreboard, int score);
void free_scoreboard(char **scoreboard);
void free_image(MLV_Image **array);

#endif

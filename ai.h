#ifndef AI_H
#define AI_H

#include "7colors.h"
#include <string.h>
#include <math.h>
#include "list.h"

char rand_play();
char rand_valid_play(char* board, char player);
char biggest_move(char* board, char player);
int calculatePerimeter(list* points);
char expand_perimeter(char *board, char player);

#endif

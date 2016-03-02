#ifndef AI_H
#define AI_H

#include "7colors.h"
#include <string.h>
#include <limits.h>

char rand_play();
char rand_valid_play(char* board, char player);
char biggest_move(char* board, char player);
char expand_perimeter(char *board, char player);
char minimax(char *board, char player);
char alphabeta(char *board, char player);

#endif

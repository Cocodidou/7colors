#include "ai.h"

char rand_play() {
  char r = rand() % 7;
  return r + 65;
}

char rand_valid_play(char *board, char player) {
  char colors_valid[7] = {0, 0, 0, 0, 0, 0, 0};
  int i, j;
  for(i = 0; i < BOARD_SIZE; i++)
  for(j = 0; j < BOARD_SIZE; j++)
    if (is_adjacent(board, i, j, player) && get_cell(board, i, j) >= 'A' &&
        get_cell(board, i, j) <= 'G')
      colors_valid[get_cell(board, i, j) - 65] = 1;
  char move = (rand() % 7) + 65;
  while(!colors_valid[move - 65])
    move = (rand() % 7) + 65;
  return move;
}

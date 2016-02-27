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


char biggest_move(char* board, char player) {
  int score_best_move = 0;
  char best_move = 'A';
  char* board_copy = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(char));
  int i;
  for(i = 0; i < 8; i++) {
    memcpy(board_copy, board, BOARD_SIZE * BOARD_SIZE);
    int score_move = update_board(board_copy, player, i + 65);
    if(score_move > score_best_move) {
      score_best_move = score_move;
      best_move = i + 65;
    }
  }
  free(board_copy);
  return best_move;
}

int compute_score(char *board, char player) {
  int res = 0;
  int i, j;
  for(i = 0; i < BOARD_SIZE; i++)
  for(j = 0; j < BOARD_SIZE; j++)
    if(get_cell(board, i, j) == player)
      res++;
  return res;
}

typedef struct {
  int score;
  char move;
} res_minimax;

res_minimax minimax_through(char *board, char player, char curPlayer,
    int depth) {
  res_minimax res;
  res.score = (player == curPlayer)?INT_MIN:INT_MAX;
  res.move = 'A';
  if(!depth){
    res.move = biggest_move(board, player);
    return res;
  }

  int i;
  for(i = 0; i < 8; i++) {
    int current_score = compute_score(board, curPlayer);
    char* board_copy = malloc(BOARD_SIZE * BOARD_SIZE);
    memcpy(board_copy, board, BOARD_SIZE * BOARD_SIZE);
    current_score += update_board(board_copy, curPlayer, i + 65);
    res_minimax child;
    child = minimax_through(board_copy, player, (curPlayer+1) % 2, depth - 1);
    current_score += child.score;

    free(board_copy);
    if(current_score > BOARD_SIZE * BOARD_SIZE / 2) {  // Game is won
      res.score = (player == curPlayer)?INT_MIN:INT_MAX;
      return res;
    }
    if((current_score > res.score && player == curPlayer) ||
        (current_score < res.score && player != curPlayer)) {
      res.score = current_score;
      res.move = i + 65;
    }
  }
  return res;
}

char minimax(char *board, char player) {
  return minimax_through(board, player, player, 5).move;
}

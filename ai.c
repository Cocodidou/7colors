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

void recursivePerimeter(char* board, int i0, int j0, int i1, int j1, 
                        list** points)
{
    int i = (i0 + i1) / 2;
    int j = (j0 + j1) / 2;
    // this isn't a good condition since we're gonna have
    // multiple instances of the same point
    if( i == i0 || j == j0  || i == i1 || j == j1 )
        return;
    
    // we have two distinct points. Let's calculate !
    double i_dev = (double)(j1 - j0) / (i1 - i0);
    double j_dev = 1.0;
    double ip = (double)i, jp = (double)j;
    if(get_cell(board, i, j) == SYMBOL_1)
    {
        // Extend our area !
        while(get_cell(board, (int)ip, (int)jp) == SYMBOL_1 && ip > 0.0 && jp > 
            0.0 && jp < BOARD_SIZE && ip < BOARD_SIZE)
        {
            ip -= i_dev;
            jp += j_dev;
        }
    }
    else 
    {
        while(get_cell(board, (int)ip, (int)jp) == SYMBOL_1 && ip > 0.0 && jp > 
            0.0 && jp < BOARD_SIZE && ip < BOARD_SIZE)
        {
            ip += i_dev;
            jp -= j_dev;
        }
    }
    i = (int)ip;
    j = (int)jp;
    
    list* point = (list*)malloc(sizeof(list));
    point->succ = *(points);
    point->i = i;
    point->j = j;
    
    *points = point;
    
    // recursive building !
    recursivePerimeter(board, i0, j0, i, j, points);
    recursivePerimeter(board, i, j, i1, j1, points);
    
}

int calculatePerimeter(list* points) {
    // Calculate perimeter recursively
    if(points == NULL)
       return 0;
    return 1 + calculatePerimeter(points->succ);
}

char expand_perimeter(char *board, char player)
{
    // Dichotomic span
    
    // Find the extremal point on the first row, and the extremal point
    // on the first column
    //list* points = empty_list;
    int i = BOARD_SIZE, j = 0;
    
    for(;get_cell(board, 0, j) != player; j++) {}
    
    for(;get_cell(board, i, BOARD_SIZE-1) != player; i++) {}
    
    int maxPerim = 0;
    char argmaxPerim = 0x00;
    //points = concat(i, BOARD_SIZE-1, points);
    // what we do here is clear, isn't it ?
    char* board_copy = (char*)malloc(BOARD_SIZE * BOARD_SIZE * sizeof(char));
    for(char color = 'A'; color <= 'G'; color++)
    {
        memcpy(board_copy, board, BOARD_SIZE * BOARD_SIZE);
        update_board(board_copy, player, color);
        list* points = NULL;
        recursivePerimeter(board, i, BOARD_SIZE-1, 0, j, &points);
        int perim = calculatePerimeter(points);
        if(perim > maxPerim) {
            maxPerim = perim;
            argmaxPerim = color;
        }
    }
    //points = concat(0, j, points);
    
    // calculate perimeter there
    
    
    // don't let a random variable swallow us....
    //return (char)(rand() % 6 + 'A');
    return argmaxPerim;
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
  // res.move = 'A';
  if(!depth){
    res.score = compute_score(board, player);
    return res;
  }
  if(compute_score(board, curPlayer?SYMBOL_0:SYMBOL_1) >= BOARD_SIZE *
      BOARD_SIZE / 2)  //game is won
    return res;

  char *board_copy = malloc(BOARD_SIZE * BOARD_SIZE);
  int i;
  for(i = 0; i < 8; i++) {
    memcpy(board_copy, board, BOARD_SIZE * BOARD_SIZE);
    int move = update_board(board_copy, curPlayer, i + 65);
    if(move == 0)  // this move doesn't change anyth
      continue;
    res_minimax child = minimax_through(board_copy, player,
        (curPlayer==SYMBOL_1)?SYMBOL_0:SYMBOL_1, depth - 1);
    if((player == curPlayer && child.score > res.score) ||
        (player != curPlayer && child.score < res.score)) {
      // Need the score equal to have a somewhat valid move
      res.score = child.score;
      res.move = i + 65;
    }
  }
  free(board_copy);
  return res;
}

char minimax(char *board, char player) {
  return minimax_through(board, player, player, 5).move;
}

char minimax_with_depth(char *board, char player, int depth) {
  return minimax_through(board, player, player, depth).move;
}

res_minimax alphabeta_through(char *board, char player, char curPlayer,
    int depth, int lower_bound, int upper_bound) {
  res_minimax res;
  res.score = (player == curPlayer)?INT_MIN:INT_MAX;
  // res.move = 'A';
  if(!depth){
    res.score = compute_score(board, player);
    return res;
  }
  if(compute_score(board, curPlayer?SYMBOL_0:SYMBOL_1) >= BOARD_SIZE *
      BOARD_SIZE / 2)  //game is won
    return res;

  char *board_copy = malloc(BOARD_SIZE * BOARD_SIZE);
  int i;
  for(i = 0; i < 8; i++) {
    memcpy(board_copy, board, BOARD_SIZE * BOARD_SIZE);
    int move = update_board(board_copy, curPlayer, i + 65);
    if(move == 0)  // this move doesn't change anyth
      continue;
    res_minimax child = alphabeta_through(board_copy, player,
        (curPlayer==SYMBOL_1)?SYMBOL_0:SYMBOL_1, depth - 1, lower_bound,
        upper_bound);
    if((player == curPlayer && child.score >= res.score) ||
        (player != curPlayer && child.score <= res.score)) {
      // Need the score equal to have a somewhat valid move
      res.score = child.score;
      res.move = i + 65;
    }
    // Pruning
    if(player == curPlayer) {
      if(lower_bound < res.score) {
        lower_bound = res.score;
        if(upper_bound <= lower_bound)
          break;
      }
    } else {
      if(upper_bound > res.score) {
        upper_bound = res.score;
        if(upper_bound <= lower_bound)
          break;
      }
    }
  }
  free(board_copy);
  return res;
}

char alphabeta(char *board, char player) {
  return alphabeta_through(board, player, player, 6, INT_MIN, INT_MAX).move;
}

char alphabeta_with_depth(char *board, char player, int depth) {
  return alphabeta_through(board, player, player, depth, INT_MIN, INT_MAX).move;
}

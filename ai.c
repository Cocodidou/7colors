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



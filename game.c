#include "game.h"

bool is_game_finished(char* board, char pl0, char pl1)
{
   for(i = 0; i < BOARD_SIZE -; i++) {
    for(j = 0; j < BOARD_SIZE; j++) {
      if(j < BOARD_SIZE -1 && get_cell(board, i, j+1) == pl0 && get_cell(board, i, j) == pl1)
    }
  }
}

void game(char* board)
{
    char curPlayer = 0;
    bool isFinished = false;
    while(!isFinished)
    {
        printf("It's player %d's turn. Which color will they choose ?");
        char nextColor = getchar();
        if(nextColor >= 'A' && nextColor <= 'G') {
            // good choice !
            update_board(board, (curPlayer)?'^':'v', nextColor);
            print_board(board);
            curPlayer = (curPlayer + 1) % 2;
            
            // TODO determine whether the game IS finished
            
            
        }
        else continue;
    }
}
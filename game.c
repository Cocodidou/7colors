#include "game.h"

bool is_game_finished(int nb_cells[])
{
  return (nb_cells[0] >= BOARD_SIZE * BOARD_SIZE / 2 || nb_cells[1] >= BOARD_SIZE * BOARD_SIZE / 2);
}

void game(char* board)
{
    char curPlayer = 0;
    bool isFinished = false;
    int nb_cells[2] = {1, 1};
    while(!isFinished)
    {
        printf("It's player %d's turn. Which color will they choose ? ", curPlayer);
        char nextColor = getchar();
        getchar();
        printf("Oki %c\n", nextColor);
        if(nextColor >= 'A' && nextColor <= 'G') {
            // good choice !
            nb_cells[(int) curPlayer] += update_board(board, (curPlayer)?'^':'v', nextColor);
            print_board(board);
            curPlayer = (curPlayer + 1) % 2;

            // TODO determine whether the game IS finished
            if(is_game_finished(nb_cells)) {
              printf("Player %d won.", curPlayer);
              break;
            }
        }
        else continue;
    }
}

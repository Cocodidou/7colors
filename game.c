#include "game.h"

bool is_game_finished(int nb_cells[])
{
  return (nb_cells[0] >= BOARD_SIZE * BOARD_SIZE / 2 || nb_cells[1] >=
      BOARD_SIZE * BOARD_SIZE / 2);
}

void game(char* board)
{
  char curPlayer = 0;
  bool isFinished = false;
  int nb_cells[2] = {1, 1};
  char type_game = '9';
  while(type_game > '3' || type_game < '1') {
    printf("1: 2 human players | 2: against random AI -> ");
    type_game = getchar();
    getchar();
  }

  while(!isFinished)
  {
    char nextColor;
    if(type_game == '1' || curPlayer == 0) {
      printf("It's player %d's turn. Which color will they choose ? ",
          curPlayer);
      nextColor = getchar();
      getchar();
    }
    else {
      nextColor = rand_valid_play(board, (curPlayer)?'^':'v');
      printf("AI played %c\n", nextColor);
    }
    if(nextColor >= 'A' && nextColor <= 'G') {
      // good choice !
      nb_cells[(int) curPlayer] += update_board(board, (curPlayer)?'^':'v',
          nextColor);
      print_board(board);

      if(is_game_finished(nb_cells)) {
        printf("Player %d won with an occupation rate of %.2fp.c.", curPlayer,
            (double) 100.0 * nb_cells[(int) curPlayer] / (BOARD_SIZE *
              BOARD_SIZE));
        break;
      }
      curPlayer = (curPlayer + 1) % 2;
      printf("| P0: %.2fp.c. | P1: %.2fp.c. |\n",
          (double) 100.0 * nb_cells[0] / (BOARD_SIZE * BOARD_SIZE),
          (double) 100.0 * nb_cells[1] / (BOARD_SIZE * BOARD_SIZE));
    }
    else continue;
  }
}

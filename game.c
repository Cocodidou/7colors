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
  while(type_game > '4' || type_game < '1') {
    printf("1: 2 human players | 2: against random AI | 3: AI against AI |\n"
           "4: against MinMax -> ");
    type_game = getchar();
    getchar();
  }
  printf("\033[2J");  // clear screen
  print_board(board);
  printf("| P0: %.2f%% | P1: %.2f%% |\n\n",
      (double) 100.0 * nb_cells[0] / (BOARD_SIZE * BOARD_SIZE),
      (double) 100.0 * nb_cells[1] / (BOARD_SIZE * BOARD_SIZE));

  while(!isFinished)
  {
    char nextColor;
    if(type_game == '3' && curPlayer == 0) {
      nextColor = minimax(board, (curPlayer)?SYMBOL_1:SYMBOL_0);
      printf("\033[H\033[KAI %d (minimax) played %c\n", curPlayer, nextColor);
    }
    else if(type_game == '1' || curPlayer == 0) {
      printf("It's player %d's turn. Which color will they choose ? \033[K",
          curPlayer);
      nextColor = getchar();
      while(nextColor == '\n') {  // Player has hit enter instead of a color
        printf("\033[FIt's player %d's turn. Which color will they choose ? "
            "\033[K", curPlayer);
        nextColor = getchar();
      }
      getchar();
      while(nextColor > 'G' || nextColor < 'A') {
        printf("\033[F\033[K");  // clear previous line
        printf("It's player %d's turn. Which color will they choose ? ",
            curPlayer);
        nextColor = getchar();
        getchar();
      }
    }
    else {
      if (type_game == '4') {
        nextColor = minimax(board, (curPlayer)?SYMBOL_1:SYMBOL_0);
        printf("\033[H\033[KAI (minimax) played %c\n", nextColor);
      }
      else {
        nextColor = alphabeta(board, (curPlayer)?SYMBOL_1:SYMBOL_0);
        printf("\033[H\033[KAI (alphabeta) played %c\n", nextColor);
      }
    }
    // if(type_game == '3') usleep(100000);
    if(nextColor >= 'A' && nextColor <= 'G') {
      // good choice !
      nb_cells[(int) curPlayer] += update_board(board,
          (curPlayer)?SYMBOL_1:SYMBOL_0, nextColor);
      print_board(board);

      printf("| P0: %.2f%% | P1: %.2f%% |\n\n",
          (double) 100.0 * nb_cells[0] / (BOARD_SIZE * BOARD_SIZE),
          (double) 100.0 * nb_cells[1] / (BOARD_SIZE * BOARD_SIZE));
      if(is_game_finished(nb_cells)) {
        printf("\033[KPlayer %d won with an occupation rate of %.2f%%\n",
            curPlayer, (double) 100.0 * nb_cells[(int) curPlayer] / (BOARD_SIZE
              * BOARD_SIZE));
        break;
      }
      curPlayer = (curPlayer + 1) % 2;
    }
    else continue;
  }
}

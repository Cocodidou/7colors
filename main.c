#include "7colors.h"
#include <stdio.h>
#include "game.h"

/** Program entry point */
int main()
{
  //RNG init
  srand(time(0));
//   char board[BOARD_SIZE * BOARD_SIZE];
  //    = { 'A' };


  printf("\n\n  Welcome to the 7 wonders of the world of the 7 colors\n"
      "  *****************************************************\n\n"
      "Current board state:\n");
//   fill_board(board);
  init_game();

  //game(&board[0]);
  // printf("AI n.0 won %.2f%% of the time\n", tournament());

  return 0; // Everything went well
}

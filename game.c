#include "game.h"

bool is_game_finished(int nb_cells[])
{
  return (nb_cells[0] >= BOARD_SIZE * BOARD_SIZE / 2 || nb_cells[1] >=
      BOARD_SIZE * BOARD_SIZE / 2);
}

void init_game()
{
  char game_types[2]; // we don't have to malloc' it as it will keep alive
  int depths[2];
  unsigned int nb_games = ask_tournament();
  
  ask_game_type(&(game_types[0]), &(depths[0]), (char)0x00);
  ask_game_type(&(game_types[0]), &(depths[0]), (char)0x01);
  
  if(nb_games > 1)
    tournament(game_types, depths, nb_games);
  else {
    char* board = malloc(BOARD_SIZE * BOARD_SIZE);
    fill_board(board);
    game(board, depths, game_types);
  }
}

unsigned int ask_tournament() 
{
    printf("How many turns will there be ?\nIf there is more than one turn,"
           " then this is a tournament and stats will be displayed."
           "\n>");
    unsigned int ans;
    scanf("%d", &ans);
    getchar(); // get rid of the '\n'
    return ans;
}

void ask_game_type(char* game_types, int* depths, char player_id)
{
    printf("How will player %d act ?\n"
    "[1] Human input | [2] AlphaBeta AI | [3] Minimax AI | [4] Hegemonic AI\n"
    ">", player_id);
    char ans;
    while((ans = getchar()) == '\n' || ans > '4' || ans < '1')
        printf(">");
    
    game_types[(int)player_id] = ans;
    
    getchar(); // get rid of the '\n'
    
    if(ans == '2' || ans == '3') {
      int depth;
      printf("How deep will the search go in the tree ?\n>");
      scanf("%d", &depth);
      depths[(int)player_id] = depth;
      getchar();
    }
}

char ask(int curPlayer)
{
  printf("It's player %d's turn. Which color will they choose ? \033[K\n>",
    curPlayer);
  char nextColor = getchar();
  while(nextColor == '\n') {  // Player has hit enter instead of a color
    printf("\033[FIt's player %d's turn. Which color will they choose ? "
        "\033[K\n>", curPlayer);
    nextColor = getchar();
  }
  getchar();
  while(nextColor > 'G' || nextColor < 'A') {
    printf("\033[F\033[K");  // clear previous line
    printf("It's player %d's turn. Which color will they choose ?\n>",
        curPlayer);
    nextColor = getchar();
    getchar();
  }
  return nextColor;
}

char game(char* board, int* depths, char* game_types)
{
  char curPlayer = 0;
  bool isFinished = false;
  int nb_cells[2] = {1, 1};
  
  printf("\033[2J");  // clear screen
  print_board(board);
  printf("| P0: %.2f%% | P1: %.2f%% |\n\n",
      (double) 100.0 * nb_cells[0] / (BOARD_SIZE * BOARD_SIZE),
      (double) 100.0 * nb_cells[1] / (BOARD_SIZE * BOARD_SIZE));

  while(!isFinished)
  {
    char nextColor = 'A';
    switch(game_types[(int)curPlayer])
    {
      case '1': // human v. human
        nextColor = ask(curPlayer);
        break;
      case '2': // alphabeta
        nextColor = alphabeta_with_depth(board, (curPlayer)?SYMBOL_1:SYMBOL_0, 
                                         depths[(int)curPlayer]);
        printf("\033[H\033[KAI %d (alphabeta) played %c\n", curPlayer, 
                nextColor);
        break;
      case '3': // minimax
        nextColor = minimax_with_depth(board, (curPlayer)?SYMBOL_1:SYMBOL_0, 
                                       depths[(int)curPlayer]);
        printf("\033[H\033[KAI %d (minimax) played %c\n", curPlayer, 
                nextColor);
        break;
      case '4': // hegemonic
        nextColor = hegemon(board, (curPlayer)?SYMBOL_1:SYMBOL_0, 
                    (curPlayer)?BOARD_SIZE-1:0, 
                    (curPlayer)?0:BOARD_SIZE-1, 
                    (curPlayer)?-1:1, (curPlayer)?1:-1);
        printf("\033[H\033[KAI %d (hegemonic) played %c\n", curPlayer, 
                nextColor);
        break;
      default:
        break;
    }
      
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
  return curPlayer;
}

char ai2(char* board, char player) {
  return alphabeta_with_depth(board, player, 3);
}

char ai1(char* board, char player) {
  return minimax_with_depth(board, player, 4);
}

void tournament(char* game_types, int* depths, int nb_games) 
{
  int res[2] = {0, 0};
  char *board = malloc(BOARD_SIZE * BOARD_SIZE);
  int i;
  for(i = 0; i < nb_games; i++) {
    fill_board(board);
      char winner = game(board, depths, game_types);
      res[(int)winner]++;
  }
  printf("AI n.0 won %.2f%% of the time\n", (double) 100 * res[0] / nb_games);
  printf("AI n.1 won %.2f%% of the time\n", (double) 100 * res[1] / nb_games);
  
}

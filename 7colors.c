#include "7colors.h"


/** Represent the actual current board game
 *
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *  an appropriate data structure would also be preferred), but don't worry.
 *  For this first assignment, no dinosaure will get you if you do that.
 */
// char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

/** Retrieves the color of a given board cell */
char get_cell(char* board, int x, int y)
{
   return board[y*BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(char* board, int x, int y, char color)
{
   board[y*BOARD_SIZE + x] = color;
}

/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
void print_board(char* board)
{
   int i, j;
   for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++)
	 printf("%c ", get_cell(board, i, j));
      printf("\n");
   }
}

void fill_board(char* board)
{
  int i,j;
  for(i = 0; i < BOARD_SIZE; i++) {
    for(j = 0; j < BOARD_SIZE; j++) {
      board[BOARD_SIZE * i + j] = (char)(rand() % 0x07) + 65;
    }
  }
  board[BOARD_SIZE -1] = 'v';
  board[(BOARD_SIZE - 1) * BOARD_SIZE] = '^';

}

bool is_adjacent(char* board, int i, int j, char player) {
   if(!i)
      return board[BOARD_SIZE * j + i - 1] == player;
   if (!j)
      return board[BOARD_SIZE * (j-1) + i] == player;
   if (i != BOARD_SIZE - 1)
      return board[BOARD_SIZE * j + i + 1] == player;
   if (j != BOARD_SIZE - 1)
      return board[BOARD_SIZE * (j-1) + i] == player;
   return false;
}

void update_board(char* board, char player, char color) {
   bool hasChanged = true;
   while(hasChanged) {
      int i, j;
      for(i = 0; i < BOARD_SIZE; i++) {
	 for(j = 0; j < BOARD_SIZE; j++) {
	    if (get_cell(board, i, j) == color && is_adjacent(board, i, j, player))
	       board[BOARD_SIZE * j + i] = player;
	 }
      }
   }
}



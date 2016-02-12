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
	 printf("%c", get_cell(board, i, j));
      printf("\n");
   }
}


/** Program entry point */
int main() 
{
   char board[BOARD_SIZE * BOARD_SIZE];
//    = { 'A' };
   
   
   printf("\n\n  Welcome to the 7 wonders of the world of the 7 colors\n"
	      "  *****************************************************\n\n"
	 "Current board state:\n");
   
   print_board(&(board[0]));
   
   return 0; // Everything went well
}

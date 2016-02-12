#ifndef HAVE_7COLORS_H
#define HAVE_7COLORS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* We want a 30x30 board game by default */
#define BOARD_SIZE 30 


typedef char color;
char get_cell(char* board, int x, int y);
void set_cell(char* board, int x, int y, char color);
void print_board(char* board);
void fill_board(char* board);


#endif
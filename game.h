#ifndef HAVE_GAME_H
#define HAVE_GAME_H

#include <stdbool.h>
#include "7colors.h"
#include "ai.h"
#include <unistd.h>

bool is_game_finished(int*);
char ask(int);
void game();
double tournament();

#endif

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

void initGame();
void initSnakes(Board *b, Snake *s1, Snake *s2);
void updateSnake(Board *b, Snake *s);
void moveSnake(Board *b, Snake *s);

#endif

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

Board* initGame();
void initSnake(Board *b, Snake *s1, Snake *s2);
void avanceSnake(Board *b, Snake *s);
void updateSnake(Board *b, Snake *s);
void playRound();
void endGame();

#endif

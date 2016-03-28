#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

typedef struct Game *Game;
Game gameCreate();

// Get
Board* gameGetBoard(Game g);
Snake* gameGetSnake(Game g, int player);
bool gameGetIsPlaying(Game g);

// Set
void gameEnd(Game g);


void initSnakes(Board *b, Snake *s1, Snake *s2);
void updateSnake(Board *b, Snake *s);
bool moveSnake(Board *b, Snake *s);

#endif

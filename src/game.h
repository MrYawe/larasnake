#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

/**
 * \enum Direction
 * \brief Permet de gérer la direction du snake
 * \details Contient toutes les directions possibles pour le snake
 **/
typedef enum BoardSize {SMALL, MEDIUM, LARGE} BoardSize;

typedef struct Game *Game;

Game gameCreate(BoardSize size);

// Get
Board* gameGetBoard(Game g);
Snake* gameGetSnake(Game g, int player);
bool gameGetIsPlaying(Game g);

// Set
void gameEnd(Game g);

void gameInitSnakes(Board *b, Snake *s1, Snake *s2);
void gameUpdateSnake(Board *b, Snake *s);
bool gameMoveSnake(Board *b, Snake *s);

#endif

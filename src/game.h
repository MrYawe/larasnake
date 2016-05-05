#ifndef GAME_H
#define GAME_H

/**
 * \file game.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Headers of game file
 * \details All header of the game file functions
 */

#include "board.h"
#include "snake.h"
#include "item.h"
#include "enum.h"

/**
 * \enum Direction
 * \brief Permet de gérer la direction du snake
 * \details Contient toutes les directions possibles pour le snake
 **/
typedef enum BoardSize {SMALL, MEDIUM, LARGE} BoardSize;

//////////////////////////////////////////
//				STRUCTURE				//
//////////////////////////////////////////
typedef struct Game *Game;

//////////////////////////////////////////
//		INIT/CONSTRUCTOR/DESTRUCTOR		//
//////////////////////////////////////////
Game gameCreate(BoardSize size);
void gameFree(Game game);

void gameInitSnakes(Board b, Snake s1, Snake s2);

//////////////////////////////////////////
//				ACCESSORS				//
//////////////////////////////////////////
Board gameGetBoard(Game g);
Snake gameGetSnake(Game g, int player);
Item gameGetItemList(Game g);
//getItems

//////////////////////////////////////////
//				UTILITARY				//
//////////////////////////////////////////
void gameUpdateSnake(Board b, Snake s);
bool gameMoveSnake(Game g, Snake s);

Item gameGetFood(Game game);

Coord boardNextPosCell(int x, int y, Direction dir);
//bool boardIsNextCellSnake(Board b, int x, int y, Direction dir);
//bool boardIsNextCellBorder(Board b, int x, int y, Direction dir);
//bool boardIsSnake(Board b, Coord coord);

//bool boardIsCellType(Board b, int x, int y, int n, ...);
bool boardIsNextCellType(Board b, int x, int y, Direction dir, int n, ...);

void gameFeed(Game game);

bool gameGetIsPlaying(Game g);
void gameEnd(Game g);
#endif

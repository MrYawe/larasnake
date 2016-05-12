#ifndef BOARD_H
#define BOARD_H

/**
 * \file board.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Entêtes des fonctions et structure pour la gestion du plateau
 * \details Toutes les entêtes de fonctions et structure necessaires à gérer le plateau : création, récupérer des valeurs, les modifier, afficher le plateau et libérer la mémoire
 */

#include <stdbool.h>
#include "coord.h"
#include "snake.h"
#include "item.h"

//////////////////////////////////////////
//				STRUCTURE				//
//////////////////////////////////////////
typedef struct Board* Board;

//////////////////////////////////////////
//		CONSTRUCTOR/DESTRUCTOR			//
//////////////////////////////////////////
Board boardInit(int sizeX, int sizeY, int sizeCell);
void boardFree(Board b);

//////////////////////////////////////////
//				ACCESSORS				//
//////////////////////////////////////////
int boardGetValue(Board b, int x, int y);
void boardSetValue(Board b, int x, int y, int val);

int boardGetHeight(Board b);
int boardGetWidth(Board b);

Item boardGetItemList(Board board);

void boardsetType(Board board, bool b);
bool boardGetType(Board b);
int boardGetFieldValue(Board b, int x, int y);
void boardSetFieldValue(Board b, int x, int y, char v);
//////////////////////////////////////////
//				UTILITARY				//
//////////////////////////////////////////
bool boardInside(Board b, int x, int y);
void boardDisplay(Board b);
Board boardCopy(Board b);

Item boardItemAdd(Board board, Item list, int x, int y, BoardValue value);
int boardItemDelete(Board board, Item item);

// TODO: bordure qui se grise
// TODO: bordure qui se dégrise

#endif

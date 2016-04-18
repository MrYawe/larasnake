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

typedef struct Board Board;

/* ***************
 *   Init Board  *
 *************** */
Board* boardInit(int sizeX, int sizeY, int sizeCell);

/* ****************
 *    Accessors   *
 **************** */
int boardGetValue(Board *b, int posx, int posy);
void boardSetValue(Board *b, int posx, int posy, int val);

//Item boardGetFood(Board *b);
//void boardSetFood(Board *b, Item food);

int boardGetHeight(Board *b);
int boardGetWidth(Board *b);

/* ***************
 *   Utilitary   *
 *************** */
void boardDisplay(Board *b);
void boardFree(Board *b);
bool boardInside(Board *b, Coord coord);
bool boardIsSnake(Board *b, Coord coord);
//void boardFeed(Board *b);

Coord boardNextPosCell(int x, int y, Direction dir);
bool boardIsNextCellSnake(Board *b, int x, int y, Direction dir);
bool boardIsNextCellBorder(Board *b, int x, int y, Direction dir);

// TODO: bordure qui se grise
// TODO: bordure qui se dégrise

#endif

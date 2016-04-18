#ifndef SNAKE_H
#define SNAKE_H
/**
 * \file snake.h
 * \author groupe Larakis
 * \version 1
 * \date 21/02/2016
 * \brief Entêtes des fonctions et structures pour la gestion du snake
 * \details Toutes les entêtes de fonctions et structures necessaires à gérer le snake : création, récupération des valeurs, changer de direction, affichage et libération de la mémoire
 */

#include <stdbool.h>
#include "coord.h"

/**
 * \enum Direction
 * \brief Permet de gérer la direction du snake
 * \details Contient toutes les directions possibles pour le snake
 **/
typedef enum Direction {UP, RIGHT, DOWN, LEFT} Direction;

/**
 * \enum Type
 * \brief Permet de gérer le type du snake
 * \details Contient tous les types possibles pour le snake
 **/
typedef enum SnakeType {WATER, FIRE, GRASS} SnakeType;

typedef struct Element Element;
typedef struct Snake Snake;


/* ***************
 *   Init Snake  *
 *************** */
Snake* snakeCreate(int size, int id, Direction d, SnakeType type);

/* ***************
 *   Move Snake  *
 *************** */
void snakeGoUp(Snake *s);
void snakeGoDown(Snake *s);
void snakeTurnLeft(Snake *s);
void snakeTurnRight(Snake *s);
void snakeTeleportation(Snake *s, int posX, int posY);

/* ****************
 *    Accessors   *
 **************** */
Coord snakeGetPos(Snake *s, int posBloc);

Direction snakeGetDirection(Snake *s);
void snakeSetDirection(Snake *s, Direction d);

int snakeGetSize(Snake *s);

int snakeGetSpeed(Snake *s);
void snakeSetSpeed(Snake *s, int speed);

Direction snakeElementGetOrientation(Snake *s, int posElem);
void snakeElementSetOrientation(Snake *s, int posElem, Direction d);

void snakeSetGhost(Snake *s, bool b);
bool snakeIsGhost(Snake *s);

int snakeGetId(Snake *s);

SnakeType snakeGetType(Snake *s);
void snakeSetType(Snake *s, SnakeType t);

/* ***************
 *   Utilitary   *
 *************** */
void snakeInverseWay(Snake *s);
void snakeDisplay(Snake *s);
void snakeUpdateElement(Snake *s, int posElem, int posX, int posY);
void snakeDeleteSnake(Snake *s);

// TODO: Augmenter la taille de X elements
// TODO: Diminuer la taille de X elements

#endif

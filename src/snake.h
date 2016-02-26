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

/**
 * \enum Direction
 * \brief Permet de gérer la direction du snake
 * \details Contient toutes les directions possibles pour le snake
 **/
typedef enum Direction {UP, LEFT, RIGHT, DOWN, NIL} Direction;
/**
 * \enum Way
 * \brief Permet de gérer le sens du Snake
 * \details Contient les sens possibles pour le Snake
 **/
typedef enum Way {Normal, Reversed} Way;

// ifndef pour être sûr de définir l'enum Control qu'une seule fois
#ifndef ControlDef
 /**
 * \enum Control
 * \brief Valeurs de gestion du snake
 * \details Contient toutes les valeurs pour la gestion du snake
 **/
typedef enum Control {Line, Column} Control;
#define ControlDef
#endif

typedef struct Element Element;
typedef struct Snake Snake;


/* ***************
 *   Init Snake  *
 *************** */
Snake* snakeCreate(int taille);

/* ***************
 *   Move Snake  *
 *************** */
void snakeGoUp(Snake *s);
void snakeGoDown(Snake *s);
void snakeTurnLeft(Snake *s);
void snakeTurnRight(Snake *s);

/* ****************
 *    Accessors   *
 **************** */
int snakeGetPos(Snake *s, int pos, Control c);

Way snakeGetWay(Snake *s);
void snakeSetWay(Snake *s, Way w);

int snakeGetSize(Snake *s);

void snakeSetGhost(Snake *s, bool b);
bool snakeIsGhost(Snake *s);

/* ***************
 *   Utilitary   *
 *************** */
void snakeDisplay(Snake *s);
void snakeUpdateElement(Snake *s, int posElem, int posX, int posY);
void snakeDeleteSnake(Snake *s);

// TODO: Augmenter la taille de X elements
// TODO: Diminuer la taille de X elements
// TODO: TP d'une case à une autre

#endif

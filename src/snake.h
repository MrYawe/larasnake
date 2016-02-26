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
Snake* createSnake(int taille);

/* ***************
 *   Move Snake  *
 *************** */
void goUp(Snake *s);
void goDown(Snake *s);
void turnLeft(Snake *s);
void turnRight(Snake *s);

/* ****************
 *    Accessors   *
 **************** */
int getPos(Snake *s, int pos, Control c);

Way getWay(Snake *s);
void setWay(Snake *s, Way w);

int getSize(Snake *s);

void setIsGhost(Snake *s, bool b);
bool isGhost(Snake *s);

/* ***************
 *   Utilitary   *
 *************** */
void displaySnake(Snake *s);
void updateElement(Snake *s, int posElem, int posX, int posY);
void deleteSnake(Snake *s);

// TODO: Augmenter la taille de X elements
// TODO: Diminuer la taille de X elements
// TODO: TP d'une case à une autre

#endif

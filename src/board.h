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
typedef struct Board Board;

/* ***************
 *   Init Board  *
 *************** */
Board* initBoard(int sizeX, int sizeY);

/* ****************
 *    Accessors   *
 **************** */
int getValue(Board *b, int posx, int posy);
void setValue(Board *b, int posx, int posy, int val);
int getTaille(Board *b, Control c);

/* ***************
 *   Utilitary   *
 *************** */
void displayBoard(Board *b);
void freeBoard(Board *b);

// TODO: bordure qui se grise 
// TODO: bordure qui se dégrise

#endif

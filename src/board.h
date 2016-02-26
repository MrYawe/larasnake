/**
 * \file board.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Entêtes des fonctions et structure pour la gestion du plateau
 * \details Toutes les entêtes de fonctions et structure necessaires à gérer le plateau : création, récupérer des valeurs, les modifier, afficher le plateau et libérer la mémoire
 */

 /**
 * \enum BoardControl
 * \brief Valeurs de gestion du tableau
 * \details Contient toutes les valeurs pour la gestion du tableau
 **/
typedef enum BoardControl {Line, Column} BoardControl;
typedef struct Board Board;

Board* initBoard(int sizeX, int sizeY);

int getValue(Board *b, int posx, int posy);
void setValue(Board *b, int posx, int posy, int val);
int getTaille(Board *b, BoardControl c);

void displayBoard(Board *b);
void freeBoard(Board *b);

// TODO: bordure qui se grise 
// TODO: bordure qui se dégrise

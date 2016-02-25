/**
 * \file plateau.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Entêtes des fonctions et structure pour la gestion du plateau
 * \details Toutes les entêtes de fonctions et structure necessaires à gérer le plateau : création, récupérer des valeurs, les modifier, afficher le plateau et libérer la mémoire
 */

typedef struct Board Board;

Board* initBoard(int sizeX, int sizeY);
int getValue(Board *b, int posx, int posy);
void setValue(Board *b, int posx, int posy, int val);
int getTailleX(Board *b);
int getTailleY(Board *b);
void displayBoard(Board *b);
void freeBoard(Board *b);

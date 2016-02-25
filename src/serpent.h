/**
 * \file serpent.h
 * \author groupe Larakis
 * \version 1
 * \date 21/02/2016
 * \brief Entêtes des fonctions et structures pour la gestion du snake
 * \details Toutes les entêtes de fonctions et structures necessaires à gérer le snake : création, récupération des valeurs, changer de direction, affichage et libération de la mémoire
 */


/**
 * \enum Direction
 * \brief Permet de gérer la direction du snake
 * \details Contient toutes les directions possibles pour le snake
 **/
typedef enum Direction {UP, LEFT, RIGHT, DOWN, NIL} Direction;

/**
 * \struct Element
 * \brief La structure représente un élément de la liste chainée qui contient le snake
 * \details La structure contient 4 éléments : la position X, la position Y, l'élément suivant et précedent de la liste
 **/
typedef struct Element Element;
struct Element 
{
	int posX;
	int posY;
	Element *next;
	Element *previous;
};

/**
 * \struct Snake
 * \brief La structure représente le snake
 * \details La structure contient un pointeur vers le début et la fin de la liste, un attribut taille de la liste, et un attribut direction qui représente la direction actuelle du snake
 **/
typedef struct Snake
{
	Element *first;
	Element *last;
	int size;
	Direction direction;
} Snake;


Snake createSnake(int taille);

void goUp(Snake *s);
void goDown(Snake *s);
void turnLeft(Snake *s);
void turnRight(Snake *s);
int getPosX(Snake *s, int pos);
int getPosY(Snake *s, int pos);

void displaySnake(Snake *s);
void deleteSnake(Snake *s);

void addFirstElement(Snake *s, int posX, int posY);
void addLastElement(Snake *s, int posX, int posY);
void deleteFirstElement(Snake *s);
void deleteLastElement(Snake *s);
void updateElement(Snake *s, int posElem, int posX, int posY);

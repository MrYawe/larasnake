/**
 * \file snake.h
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
 * \enum Way
 * \brief Permet de gérer le sens du Snake
 * \details Contient les sens possibles pour le Snake
 **/
typedef enum Way {Normal, Reversed} Way;

typedef struct Element Element;
typedef struct Snake Snake;


Snake* createSnake(int taille);

void goUp(Snake *s);
void goDown(Snake *s);
void turnLeft(Snake *s);
void turnRight(Snake *s);

int getPosX(Snake *s, int pos);
int getPosY(Snake *s, int pos);
Way getWay(Snake *s);
void setWay(Snake *s, Way w);
int getSize(Snake *s);

void displaySnake(Snake *s);
void updateElement(Snake *s, int posElem, int posX, int posY);
void deleteSnake(Snake *s);

// TODO: Augmenter la taille de X elements
// TODO: Diminuer la taille de X elements
// TODO: TP
// TODO: Rajouter un isGhost dans la structure

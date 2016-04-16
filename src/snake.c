/**
 * \file snake.c
 * \author groupe Larakis
 * \version 1
 * \date 21/02/2016
 * \brief Classe qui contient toute la gestion du snake
 * \details Toutes les fonctions necessaires à gérer le snake : création, récupération des valeurs, changer de direction, affichage et libération de la mémoire
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "constants.h"

// Headers for static functions of snake file
static void snakeAddFirstElement(Snake *s, int posX, int posY, Direction orientation);
static void snakeAddLastElement(Snake *s, int posX, int posY, Direction orientation);
static void snakeDeleteFirstElement(Snake *s);
//static void snakeDeleteLastElement(Snake *s);
//static int mod(int a, int b);

/**
 * \struct Snake
 * \brief La structure représente le snake
 * \details La structure contient un pointeur vers la tête et la queue, un attribut taille du serpent, et un attribut direction qui représente la direction actuelle du snake
 **/
struct Snake
{
	int id;
	Element *first;
	Element *last;
	int size;
	int speed;
	Direction direction;
	SnakeType type;
	bool isGhost;
};

/**
 * \struct Element
 * \brief La structure représente un élément de la liste chainée qui compose le snake
 * \details La structure contient 4 éléments : la position X, la position Y, l'élément suivant et précedent de la liste
 **/
struct Element
{
	int posX;
	int posY;
	Element *next;
	Element *previous;
	Direction orientation;
};

/**
 * \fn snakeCreate
 * \brief La fonction crée et renvoie un snake
 * \details La fonction alloue la mémoire necessaire à un snake et remplit les éléments de la structure
 * \param size Entier qui correspond au nombre d'anneaux pour le snake
 * \param id Entier qui correspond à l'id du snake
 * \return Variable de type Snake qui contiendra un snake
 */
Snake* snakeCreate(int size, int id, Direction d)
{
	Snake *s = malloc(sizeof(struct Snake));
	s->first = NULL;
	s->last = NULL;
	s->size = 0;
	s->speed = SNAKE_DEFAULT_SPEED;
	s->id = id;
	s->direction = d;
	s->isGhost = false;
	srand(rand()*time(NULL));
	s->type = (int)rand()%NB_TYPES;
	int i;
	for (i=0; i<size; i++)
	{
		snakeAddFirstElement(s, 0, 0, s->direction);
	}
	return s;
}

/**
 * \fn snakeGoUp
 * \brief La fonction ajuste le snake pour que sa position monte d'une case
 * \details La fonction rajoute un élément en tête de liste (queue) et supprime le last (tête) de manière à permettre au snake de goUpr
 * \param s Variable de type Snake* qui pointe vers le snake à faire goUpr
 */
void snakeGoUp(Snake *s)
{
	snakeAddLastElement(s, s->last->posX, s->last->posY - 1, s->direction);
	//snakeAddLastElement(s, s->last->posX, mod(s->last->posY - 1, BOARD_SIZE));
	snakeDeleteFirstElement(s);
	s->direction = UP;
}

/**
 * \fn snakeGoDown
 * \brief La fonction ajuste le snake pour que sa position goDowne d'une case
 * \details La fonction rajoute un élément en tête de liste (queue) et supprime le last (tête) de manière à permettre au snake de goDownre
 * \param s Variable de type Snake* qui pointe vers le snake à faire goDownre
 */
void snakeGoDown(Snake *s)
{
	snakeAddLastElement(s, s->last->posX, s->last->posY + 1, s->direction);
	//snakeAddLastElement(s, s->last->posX, mod(s->last->posY + 1, BOARD_SIZE));
	snakeDeleteFirstElement(s);
	s->direction = DOWN;
}

/**
 * \fn snakeTurnLeft
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la gauche
 * \details La fonction rajoute un élément en tête de liste (queue) et supprime le last (tête) de manière à permettre au snake de tourner à gauche
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à gauche
 */
void snakeTurnLeft(Snake *s)
{
	snakeAddLastElement(s, s->last->posX - 1, s->last->posY, s->direction);
	//snakeAddLastElement(s, mod(s->last->posX - 1, BOARD_SIZE), s->last->posY);
	snakeDeleteFirstElement(s);
	s->direction = LEFT;
}

/**
 * \fn snakeTurnRight
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la droite
 * \details La fonction rajoute un élément en tête de liste (queue) et supprime le last (tête) de manière à permettre au snake de tourner à droite
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à droite
 */
void snakeTurnRight(Snake *s)
{
	snakeAddLastElement(s, s->last->posX + 1, s->last->posY, s->direction);
	//snakeAddLastElement(s, mod(s->last->posX + 1, BOARD_SIZE), s->last->posY);
	snakeDeleteFirstElement(s);
	s->direction = RIGHT;
}

/**
 * \fn snakeTeleportation
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la case cible
 * \details La fonction rajoute un élément en tête de liste à la position cible et supprime le last de manière à permettre au snake de se téléporter
 * \param s Variable de type Snake* qui pointe vers le snake à téléporter
 * \param posX Variable de type int qui correspond à la position en X de la case ciblée
 * \param posY Variable de type int qui correspond à la position en Y de la case ciblée
 */
void snakeTeleportation(Snake *s, int posX, int posY)
{
	snakeAddLastElement(s, posX, posY, s->direction);
	snakeDeleteFirstElement(s);
}

/**
 * \fn snakeGetPos
 * \brief La fonction renvoie la valeur pos d'un maillon
 * \details La fonction se déplace dans la liste jusqu'à l'endroit voulu puis renvoie la valeur. Une erreur est levée si la valeur passée en paramètre n'est pas bonne
 * \param s Variable de type Snake* qui pointe vers le snake à analyser
 * \param pos Variable de type int qui correspond à l'emplacement voulu
 * \param c Variable de type enum Control qui correspond à ligne ou colonne suivant ce que l'on souhaite récupérer
 */
Coord snakeGetPos(Snake *s, int posBloc)
{
	Coord res = coordNew(0,0);
	if (posBloc < 0 || posBloc >= s->size)
	{
		printf("snakeGetPosition : Error pos parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posBloc; i++)
		{
			e = e->next;
		}
		res->x=e->posX;
		res->y=e->posY;
	}
	return res;
}

Direction snakeGetDirection(Snake *s)
{
	return s->direction;
}

void snakeSetDirection(Snake *s, Direction d)
{
	bool update = true;
	switch (s->direction)
	{
		case UP:
			if (d == DOWN)
				update = false;
		break;
		case DOWN:
			if (d == UP)
				update = false;
		break;
		case LEFT:
			if (d == RIGHT)
				update = false;
		break;
		case RIGHT:
			if (d == LEFT)
				update = false;
		break;
		default:
		break;
	}
	if (update)
	{
		s->direction = d;
	}
}


/**
 * \fn snakeGetSize
 * \brief La fonction renvoie la taille du serpent
 * \details La fonction récupère la taille dans la structure
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 */
int snakeGetSize(Snake *s)
{
	return s->size;
}

/**
 * \fn snakeGetSpeed
 * \brief La fonction renvoie la vitesse du serpent
 * \details La fonction récupère la vitesse dans la structure
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 */
int snakeGetSpeed(Snake *s)
{
	return s->speed;
}

void snakeSetSpeed(Snake *s, int speed)
{
	s->speed = speed;
}

Direction snakeElementGetOrientation(Snake *s, int posElem)
{
	Direction res = 0;
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeElementGetOrientation : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		res = e->orientation;
	}
	return res;
}

void snakeElementSetOrientation(Snake *s, int posElem, Direction d)
{
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeElementSetOrientation : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		e->orientation = d;
	}
}


/**
 * \fn snakeSetGhost
 * \brief La fonction modifie le serpent pour le passer ou non en fantôme
 * \details La fonction modifie l'attribue isGhost serpent dans la structure par la valeur passée en paramètre
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 * \param b Variable de type bool qui est la valeur à attribuer au snake
 */
void snakeSetGhost(Snake *s, bool b)
{
	s->isGhost = b;
}


/**
 * \fn snakeIsGhost
 * \brief La fonction renvoie le booleen qui dit si le Snake est un fantome ou non
 * \details La fonction récupère le booleen isGhost dans la structure du snake
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 */
bool snakeIsGhost(Snake *s)
{
	return s->isGhost;
}

/**
 * \fn snakeGetId
 * \brief La fonction renvoie l'id du serpent
 * \details La fonction récupère l'id dans la structure
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 * \return Variable de type int
 */
int snakeGetId(Snake *s)
{
	return s->id;
}

/**
 * \fn snakeGetType
 * \brief La fonction renvoie le type du serpent
 * \details La fonction récupère le type du serpent dans la structure
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 */
SnakeType snakeGetType(Snake *s)
{
	return s->type;
}

/**
 * \fn snakeGetType
 * \brief La fonction modifie le type du serpent
 * \details La fonction modifie le type du serpent dans la structure par la valeur passée en paramètre
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 * \param t Variable de type Type qui est la valeur à attribuer au snake
 */
void snakeSetType(Snake *s, SnakeType t)
{
	s->type = t;
}

void snakeInverseWay(Snake *s)
{
	Element *tampon = s->first;
	s->first = s->last;

	Element* tempElem = NULL;
	while (tampon)
	{
		Element* suivant = tampon->next;
		tampon->next = tempElem;
		tampon->previous = suivant;
	 	tempElem = tampon;
		tampon = suivant;
	}
	s->last = tempElem;
}

/**
 * \fn snakeDisplay
 * \brief La fonction affiche le contenu du snake
 * \details La fonction affiche pour chaque element du plateau son contenu ainsi que la direction du snake
 * \param s Variable de type Snake* qui pointe vers le snake à afficher
 */
void snakeDisplay(Snake *s)
{
	// char const* direc[] = {"le haut", "la gauche", "la droite", "le bas", "indéfini"};
	// printf("Le snake va vers %s\n", direc[s->direction]);
	// printf("L'id du snake est : %d\n", s->id);
	// char const* type[] = {"feu", "eau", "plante"};
	// printf("Le type du snake est : %s\n", type[s->type]);
printf("\n");printf("\n");
	Element *curseur = s->first;
	int i=0;
	while(curseur != NULL)
	{
		printf("Actuel : %p | précédent : %p | suivant %p | posX %d | posY %d\n", curseur, curseur->previous, curseur->next, curseur->posX, curseur->posY);
		//printf("Maillon %d : [posX: %d, posY: %d]\n", i, curseur->posX, curseur->posY);
		curseur = curseur->next;
		i++;
	}
}

/**
 * \fn snakeUpdateElement
 * \brief La fonction modifie les valeurs d'un élément de la liste
 * \details La fonction attribue les valeurs passées en paramètres à l'élément situé à la posElem position
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posElem Variable de type int qui correspond à l'emplacement dans la liste de l'element à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
void snakeUpdateElement(Snake *s, int posElem, int posX, int posY)
{
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeUpdateElement : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		e->posX = posX;
		e->posY = posY;
	}
}


/**
 * \fn snakeDelete
 * \brief La fonction libère le serpent de la mémoire
 * \details La fonction libère entièrement chaque élément de la liste chainée
 * \param s Variable de type Snake* qui pointe vers le snake à libérer
 */
void snakeDelete(Snake *s)
{
	Element *curs = s->first;
	Element *curssuiv;
	while(curs != NULL)
	{
		curssuiv = curs->next;
		free(curs);
		curs = curssuiv;
	}
}


/**
 * \fn snakeAddFirstElement
 * \brief La fonction ajoute un élément au début de la liste chaînée
 * \details La fonction crée un élément en mémoire, lui attribue les valeurs passées en paramètres et gère le cas de la liste vide et l'ajoute en début de liste
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
static void snakeAddFirstElement(Snake *s, int posX, int posY, Direction orientation)
{
	Element *e = (Element*) malloc(sizeof(struct Element));
	e->posX = posX;
	e->posY = posY;
	e->orientation = orientation;
	e->previous = NULL;
	if (s->size == 0)
	{
		e->next = NULL;
		s->last = e;
	}
	else
	{
		s->first->previous = e;
		e->next = s->first;
	}
	s->first = e;
	s->size ++;
}

/**
 * \fn snakeAddLastElement
 * \brief La fonction ajoute un élément à la fin de la liste chaînée
 * \details La fonction crée un élément en mémoire, lui attribue les valeurs passées en paramètres et gère le cas de la liste vide et l'ajoute en fin de liste
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
static void snakeAddLastElement(Snake *s, int posX, int posY, Direction orientation)
{
	if (s->size == 0)
	{
		snakeAddFirstElement(s, posX, posY, orientation);
	}
	else
	{
		Element *e = (Element*) malloc(sizeof(struct Element));
		e->posX = posX;
		e->posY = posY;
		e->orientation = orientation;
		e->previous = s->last;
		e->next = NULL;
		s->last->next = e;
		s->last = e;
		s->size++;
	}
}

/**
 * \fn snakeDeleteFirstElement
 * \brief La fonction supprime un élément au début de la liste chaînée
 * \details La fonction supprime le first élément de la liste et envoie un message d'erreur si la liste est vide
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 */
static void snakeDeleteFirstElement(Snake *s)
{
	if (s->size == 0)
	{
		printf("snakeDeleteFirstElement : Empty list\n");
	}
	else
	{
		Element *e = s->first;
		s->first = s->first->next;
		s->first->previous = NULL;
		free(e);
		s->size --;
	}
}

/**
 * \fn snakeDeleteLastElement
 * \brief La fonction supprime un élément à la fin de la liste chaînée
 * \details La fonction supprime le last élément de la liste et envoie un message d'erreur si la liste est vide
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 */
/*
static void snakeDeleteLastElement(Snake *s)
{
	if (s->size == 0)
	{
		printf("snakeDeleteLastElement : Empty List !\n");
	}
	else
	{
		Element *e = s->last;
		s->last = s->last->previous;
		s->last->next = NULL;
		free(e);
		s->size --;
	}
}

static int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}
*/

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
#include "snake.h"

// Headers for static functions of snake file
static void snakeAddFirstElement(Snake *s, int posX, int posY);
static void snakeAddLastElement(Snake *s, int posX, int posY);
static void snakeDeleteFirstElement(Snake *s);
static void snakeDeleteLastElement(Snake *s);


/**
 * \struct Snake
 * \brief La structure représente le snake
 * \details La structure contient un pointeur vers le début et la fin de la liste, un attribut taille de la liste, et un attribut direction qui représente la direction actuelle du snake
 **/
struct Snake
{
	Element *first;
	Element *last;
	int size;
	Direction direction;
	Way way;
	bool isGhost;
};

/**
 * \struct Element
 * \brief La structure représente un élément de la liste chainée qui contient le snake
 * \details La structure contient 4 éléments : la position X, la position Y, l'élément suivant et précedent de la liste
 **/
struct Element 
{
	int posX;
	int posY;
	Element *next;
	Element *previous;
};

/**
 * \fn snakeCreate
 * \brief La fonction crée et renvoie un snake
 * \details La fonction alloue la mémoire necessaire à un snake et remplit les éléments de la structure
 * \param size Entier qui correspond au nombre d'anneaux pour le snake
 * \return Variable de type Snake qui contiendra un snake
 */
Snake* snakeCreate(int size)
{
	Snake *s = malloc(sizeof(Snake));
	s->first = NULL;
	s->last = NULL;
	s->direction = NIL;
	s->size = 0;
	s->way = Normal;
	s->isGhost = false;
	int i;
	for (i=0; i<size; i++)
	{
		snakeAddFirstElement(s, 0, 0);
	}	
	return s;
}

/**
 * \fn snakeGoUp
 * \brief La fonction ajuste le snake pour que sa position monte d'une case
 * \details La fonction rajoute un élément en tête de liste et supprime le last de manière à permettre au snake de goUpr
 * \param s Variable de type Snake* qui pointe vers le snake à faire goUpr
 */
void snakeGoUp(Snake *s)
{
	if (s->way == Normal)
	{
		snakeAddLastElement(s, s->last->posX, s->last->posY + 1);
		snakeDeleteFirstElement(s);
	}
	else if (s->way == Reversed)
	{
		snakeAddFirstElement(s, s->first->posX, s->first->posY + 1);
		snakeDeleteLastElement(s);
	}	
	s->direction = UP;
}

/**
 * \fn snakeGoDown
 * \brief La fonction ajuste le snake pour que sa position goDowne d'une case
 * \details La fonction rajoute un élément en tête de liste et supprime le last de manière à permettre au snake de goDownre
 * \param s Variable de type Snake* qui pointe vers le snake à faire goDownre
 */
void snakeGoDown(Snake *s)
{
	if (s->way == Normal)
	{
		snakeAddLastElement(s, s->last->posX, s->last->posY - 1);
		snakeDeleteFirstElement(s);
	}
	else if (s->way == Reversed)
	{
		snakeAddFirstElement(s, s->first->posX, s->first->posY - 1);
		snakeDeleteLastElement(s);
	}	
	s->direction = DOWN;
}

/**
 * \fn snakeTurnLeft
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la gauche
 * \details La fonction rajoute un élément en tête de liste et supprime le last de manière à permettre au snake de tourner à gauche
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à gauche
 */
void snakeTurnLeft(Snake *s)
{
	if (s->way == Normal)
	{
		snakeAddLastElement(s, s->last->posX - 1, s->last->posY);
		snakeDeleteFirstElement(s);
	}
	else if (s->way == Reversed)
	{
		snakeAddFirstElement(s, s->first->posX - 1, s->first->posY);
		snakeDeleteLastElement(s);
	}	
	s->direction = LEFT;
}

/**
 * \fn snakeTurnRight
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la droite
 * \details La fonction rajoute un élément en tête de liste et supprime le last de manière à permettre au snake de tourner à droite
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à droite
 */
void snakeTurnRight(Snake *s)
{
	if (s->way == Normal)
	{
		snakeAddLastElement(s, s->last->posX + 1, s->last->posY);
		snakeDeleteFirstElement(s);
	}
	else if (s->way == Reversed)
	{
		snakeAddFirstElement(s, s->first->posX + 1, s->first->posY);
		snakeDeleteLastElement(s);
	}
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
void snakeTP(Snake *s, int posX, int poxY)
{
	if (s->way == Normal)
	{
		snakeAddFirstElement(s, posX, posY);
		snakeDeleteLastElement(s);
	}
	else if (s->way == Reversed)
	{
		snakeAddLastElement(s, posX, posY);
		snakeDeleteFirstElement(s);
	}	
}

/**
 * \fn snakeGetPos
 * \brief La fonction renvoie la valeur pos d'un maillon
 * \details La fonction se déplace dans la liste jusqu'à l'endroit voulu puis renvoie la valeur. Une erreur est levée si la valeur passée en paramètre n'est pas bonne
 * \param s Variable de type Snake* qui pointe vers le snake à analyser
 * \param pos Variable de type int qui correspond à l'emplacement voulu
 * \param c Variable de type enum Control qui correspond à ligne ou colonne suivant ce que l'on souhaite récupérer
 */
int snakeGetPos(Snake *s, int pos, Control c)
{
	int res = 0;
	if (pos < 0 || pos >= s->size)
	{
		printf("snakeGetPosition : Error pos parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < pos; i++)
		{
			e = e->next;
		}
		if (c == Line)
		{
			res = e->posX;
		}
		else if (c == Column)
		{
			res = e->posY;
		}
		
	}		
	return res;
}

/**
 * \fn snakeGetWay
 * \brief La fonction renvoie le sens du serpent
 * \details La fonction récupère le sens du serpent dans la structure
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 */
Way snakeGetWay(Snake *s)
{
	return s->way;
}

/**
 * \fn snakeGetWay
 * \brief La fonction modifie le sens du serpent
 * \details La fonction modifie le sens du serpent dans la structure par la valeur passée en paramètre
 * \param s Variable de type Snake* qui pointe vers le snake à parcourir
 * \param w Variable de type Way qui est la valeur à attribuer au snake
 */
void snakeSetWay(Snake *s, Way w)
{
	s->way = w;
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
 * \fn snakeDisplay
 * \brief La fonction affiche le contenu du snake
 * \details La fonction affiche pour chaque element du plateau son contenu ainsi que la direction du snake
 * \param s Variable de type Snake* qui pointe vers le snake à afficher
 */
void snakeDisplay(Snake *s)
{
	char const* direc[] = {"le haut", "la gauche", "la droite", "le bas", "indéfini"};
	printf("Le snake va vers %s\n", direc[s->direction]);

	Element *curseur = s->first;
	int i=0;
	while(curseur != NULL)
	{
		printf("Maillon %d : [posX: %d, posY: %d]\n", i, curseur->posX, curseur->posY);
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
static void snakeAddFirstElement(Snake *s, int posX, int posY)
{
	Element *e = (Element*) malloc(sizeof(Element));
	e->posX = posX;
	e->posY = posY;
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
static void snakeAddLastElement(Snake *s, int posX, int posY)
{
	if (s->size == 0)
	{
		snakeAddFirstElement(s, posX, posY);
	}
	else
	{
		Element *e = (Element*) malloc(sizeof(Element));
		e->posX = posX;
		e->posY = posY;
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
	free(s);
}

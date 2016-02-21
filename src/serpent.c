/**
 * \file serpent.c
 * \author groupe Larakis
 * \version 1
 * \date 21/02/2016
 * \brief Classe qui contient toute la gestion du snake
 * \details Toutes les fonctions necessaires à gérer le snake : création, récupération des valeurs, changer de direction, affichage et libération de la mémoire
 */
#include <stdio.h>
#include <stdlib.h>
#include "serpent.h"

/**
 * \fn createSnake
 * \brief La fonction crée et renvoie un snake
 * \details La fonction alloue la mémoire necessaire à un snake et remplit les éléments de la structure
 * \param taille Entier qui correspond au nombre d'anneaux pour le snake
 * \return Variable de type Snake qui contiendra un snake
 */
Snake createSnake(int taille)
{
	Snake s;
	s.premier = NULL;
	s.dernier = NULL;
	s.direction = NIL;
	s.taille = 0;
	int i;
	for (i=0; i<taille; i++)
	{
		addFirstElement(&s, 0, 0);
	}	
	return s;
}

/**
 * \fn monte
 * \brief La fonction ajuste le snake pour que sa position monte d'une case
 * \details La fonction rajoute un élément en tête de liste et supprime le dernier de manière à permettre au snake de monter
 * \param s Variable de type Snake* qui pointe vers le snake à faire monter
 */
void monte(Snake *s)
{
	addLastElement(s, s->dernier->posX, s->dernier->posY + 1);
	deleteFirstElement(s);
	s->direction = UP;
}

/**
 * \fn descend
 * \brief La fonction ajuste le snake pour que sa position descende d'une case
 * \details La fonction rajoute un élément en tête de liste et supprime le dernier de manière à permettre au snake de descendre
 * \param s Variable de type Snake* qui pointe vers le snake à faire descendre
 */
void descend(Snake *s)
{
	addLastElement(s, s->dernier->posX, s->dernier->posY - 1);
	deleteFirstElement(s);
	s->direction = DOWN;
}

/**
 * \fn tourneGauche
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la gauche
 * \details La fonction rajoute un élément en tête de liste et supprime le dernier de manière à permettre au snake de tourner à gauche
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à gauche
 */
void tourneGauche(Snake *s)
{
	addLastElement(s, s->dernier->posX - 1, s->dernier->posY);
	deleteFirstElement(s);
	s->direction = LEFT;
}

/**
 * \fn tourneDroite
 * \brief La fonction ajuste le snake pour qu'il soit déplacé vers la droite
 * \details La fonction rajoute un élément en tête de liste et supprime le dernier de manière à permettre au snake de tourner à droite
 * \param s Variable de type Snake* qui pointe vers le snake à faire tourner à droite
 */
void tourneDroite(Snake *s)
{
	addLastElement(s, s->dernier->posX + 1, s->dernier->posY);
	deleteFirstElement(s);
	s->direction = RIGHT;
}

/**
 * \fn displaySnake
 * \brief La fonction affiche le contenu du snake
 * \details La fonction affiche pour chaque element du plateau son contenu ainsi que la direction du snake
 * \param s Variable de type Snake* qui pointe vers le snake à afficher
 */
void displaySnake(Snake *s)
{
	char const* direc[] = {"le haut", "la gauche", "la droite", "le bas", "indéfini"};
	printf("Le snake va vers %s\n", direc[s->direction]);

	Element *curseur = s->premier;
	int i=0;
	while(curseur != NULL)
	{
		printf("Maillon %d : [posX: %d, posY: %d]\n", i, curseur->posX, curseur->posY);
		curseur = curseur->suivant;
		i++;
	}
}

/**
 * \fn deleteSnake
 * \brief La fonction libère le serpent de la mémoire
 * \details La fonction libère entièrement chaque élément de la liste chainée
 * \param s Variable de type Snake* qui pointe vers le snake à libérer
 */
void deleteSnake(Snake *s)
{
	Element *curs = s->premier;
	Element *curssuiv;
	while(curs != NULL)
	{
		curssuiv = curs->suivant;
		free(curs);
		curs = curssuiv;
	}
}


/**
 * \fn addFirstElement
 * \brief La fonction ajoute un élément au début de la liste chaînée
 * \details La fonction crée un élément en mémoire, lui attribue les valeurs passées en paramètres et gère le cas de la liste vide et l'ajoute en début de liste
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
void addFirstElement(Snake *s, int posX, int posY)
{
	Element *e = (Element*) malloc(sizeof(Element));
	e->posX = posX;
	e->posY = posY;
	e->precedent = NULL;	
	if (s->taille == 0)
	{
		e->suivant = NULL;
		s->dernier = e;
	}		
	else
	{
		s->premier->precedent = e;
		e->suivant = s->premier;		
	}
	s->premier = e;
	s->taille ++;
}

/**
 * \fn addFirstElement
 * \brief La fonction ajoute un élément à la fin de la liste chaînée
 * \details La fonction crée un élément en mémoire, lui attribue les valeurs passées en paramètres et gère le cas de la liste vide et l'ajoute en fin de liste
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
void addLastElement(Snake *s, int posX, int posY)
{
	if (s->taille == 0)
	{
		addFirstElement(s, posX, posY);
	}
	else
	{
		Element *e = (Element*) malloc (sizeof(Element));
		e->posX = posX;
		e->posY = posY;
		e->precedent = s->dernier;
		e->suivant = NULL;
		s->dernier->suivant = e;
		s->dernier = e;
		s->taille++;
	}	
}

/**
 * \fn deleteFirstElement
 * \brief La fonction supprime un élément au début de la liste chaînée
 * \details La fonction supprime le premier élément de la liste et envoie un message d'erreur si la liste est vide
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 */
void deleteFirstElement(Snake *s)
{
	if (s->taille == 0)
	{
		printf("deleteFirstElement : Liste déjà vide\n");
	}
	else
	{
		Element *e = s->premier;
		s->premier = s->premier->suivant;
		s->premier->precedent = NULL;
		free(e);
		s->taille --;
	}	
}

/**
 * \fn deleteLastElement
 * \brief La fonction supprime un élément à la fin de la liste chaînée
 * \details La fonction supprime le dernier élément de la liste et envoie un message d'erreur si la liste est vide
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 */
void deleteLastElement(Snake *s)
{
	if (s->taille == 0)	
	{
		printf("deletaLastElement : Liste déjà vide\n");
	}
	else
	{
		Element *e = s->dernier;
		s->dernier = s->dernier->precedent;
		s->dernier->suivant = NULL;
		free(e);
		s->taille --;
	}
}

/**
 * \fn updateElement
 * \brief La fonction modifie les valeurs d'un élément de la liste
 * \details La fonction attribue les valeurs passées en paramètres à l'élément situé à la posElem position
 * \param s Variable de type Snake* qui pointe vers le snake à modifier
 * \param posElem Variable de type int qui correspond à l'emplacement dans la liste de l'element à modifier
 * \param posX Variable de type int qui correspond à la valeur à rajouter pour la position X
 * \param posY Variable de type int qui correspond à la valeur à rajouter pour la position Y
 */
void updateElement(Snake *s, int posElem, int posX, int posY)
{
	if (posElem < 0 || posElem >= s->taille)
	{
		printf("updateElement : Error posElem out of range\n");
	}
	else
	{
		int i;
		Element *e = s->premier;
		for (i = 0; i < posElem; i++)
		{
			e = e->suivant;
		}
		e->posX = posX;
		e->posY = posY;
	}	
}

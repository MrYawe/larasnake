/**
 * \file plateau.c
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Contrôle la gestion du plateau
 * \details Toutes les fonctions necessaires à gérer le plateau : création, récupérer des valeurs, les modifier, afficher le plateau et libérer la mémoire
 */

#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

/**
 * \fn initBoard
 * \brief La fonction crée le plateau
 * \details La fonction alloue la mémoire necessaire au plateau et remplit les éléments de la structure
 * \param sizeX Entier qui done la taille en X du plateau créé
 * \param sizeY Entier qui done la taille en Y du plateau créé
 * \return Variable de type Board qui contiendra le plateau
 */
Board initBoard(int sizeX, int sizeY)
{
  Board b;
  // Check for negative sizes
  if (sizeX >= 0 && sizeY >=0)
  {
    // Allocation of tab
    b.tab = (int**) malloc(sizeY*sizeof(int*));
    int i;
    for ( i = 0; i < sizeY; i++ )
    {
      b.tab[i] = (int*) malloc(sizeX*sizeof(int));
    }
    // Set sizes
    b.tailleX = sizeX;
    b.tailleY = sizeY;
  }
  else
  {
    printf("InitBoard: error negative size!\n");
  }
  return b;
}

/**
 * \fn getValue
 * \brief La fonction renvoie la valeur d'un emplacement du plateau
 * \details La fonction teste si les paramètres sont corrects et renvoie, le cas échéant, la valeur correspondante
 * \param b Variable de type Board qui correspond au tableau à parcourir pour trouver la valeur
 * \param posx Variable de type Int qui correpond à l'emplacement X de la valeur à récupérer
 * \param posy Variable de type Int qui correpond à l'emplacement Y de la valeur à récupérer
 * \return Variable de type int qui correspond à l'entier situé l'emplacement voulu sur le plateau
 */
int getValue(Board *b, int posx, int posy)
{
  // Check for out of range exceptions
  if (posx < b->tailleX && posy < b->tailleY && posx >= 0 && posy >=0)
  {
    return b->tab[posx][posy];
  }
  else
  {
    printf("GetValue: error out of range\n");
    return -1;
  }
}

/**
 * \fn setValue
 * \brief La fonction attribue une valeur à un emplacement du plateau
 * \details La fonction teste si les paramètres sont corrects et attribue, le cas échéant, la valeur correspondante au bon emplacement du plateau
 * \param b Variable de type Board qui correspond au tableau à parcourir pour attribuer la valeur
 * \param posx Variable de type Int qui correpond à l'emplacement X de la valeur à attriber
 * \param posy Variable de type Int qui correpond à l'emplacement Y de la valeur à attribuer
 * \param val Variable de type Int qui correpond à la valeur à attribuer
 */
void setValue(Board *b, int posx, int posy, int val)
{
  // Check for out of range exceptions
  if (posx < b->tailleX && posy < b->tailleY && posx >= 0 && posy >=0)
  {
    b->tab[posx][posy] = val;
  }
  else
  {
    printf("SetValue: error out of range\n");
  }
}

/**
 * \fn displayBoard
 * \brief La fonction affiche le plateau dans la console
 * \details La fonction affiche pour chaque case du plateau sa valeur dans la console
 * \param b Variable de type Board qui correspond au tableau à afficher
 */
void displayBoard(Board *b)
{
  int i, j;
  for(j=0; j<b->tailleY; j++)
  {
    for (i=0; i<b->tailleX; i++)
    {
      printf(" %d ", getValue(b, i, j));
    }
    printf("\n");
  }
}

/**
 * \fn freeBoard
 * \brief La fonction libère la mémoire du plateau
 * \details La fonction libère entièrement le tableau à deux dimensions de la mémoire
 * \param b Variable de type Board qui correspond au tableau à effacer
 */
void freeBoard(Board *b)
{
  int i;
  for ( i = 0; i < b->tailleY; i++ )
  {
    free(b->tab[i]);
  }
  free(b->tab);
}


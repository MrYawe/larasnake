#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

Board initBoard(int sizeX, int sizeY)
{
  Board b;
  // allocation of tab
  b.tab = malloc(sizeY*sizeof(int*));
  int i;
  for ( i = 0; i < sizeY; i++ )
  {
    b.tab[i] = malloc(sizeX*sizeof(int));
  }
  // set sizes
  b.tailleX = sizeX;
  b.tailleY = sizeY;
  return b;
}

int getValue(Board b, int posx, int posy)
{
  // Check for out of range exceptions
  if (posx < b.tailleX && posy < b.tailleY)
  {
    return b.tab[posx][posy];
  }
  else
  {
    printf("Erreur : getValue out of range\n");
    return -1;
  }
}

void setValue(Board b, int posx, int posy, int val)
{
  // Check for out of range exceptions
  if (posx < b.tailleX && posy < b.tailleY)
  {
    b.tab[posx][posy] = val;
  }
  else
  {
    printf("Erreur : setValue out of range\n");
  }
}

void displayBoard(Board b)
{
  int i, j;
  for(j=0; j<b.tailleY; j++)
  {
    for (i=0; i<b.tailleX; i++)
    {
      printf(" %d ", getValue(b, i, j));
    }
    printf("\n");
  }
}

void freeBoard(Board b)
{
  int i;
  for ( i = 0; i < b.tailleY; i++ )
  {
    free(b.tab[i]);
  }
  free(b.tab);
}

#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

Board initBoard(int sizeX, int sizeY)
{
  Board b;
  // Check for negative sizes
  if (sizeX >= 0 && sizeY >=0)
  {
    // Allocation of tab
    b.tab = malloc(sizeY*sizeof(int*));
    int i;
    for ( i = 0; i < sizeY; i++ )
    {
      b.tab[i] = malloc(sizeX*sizeof(int));
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

int getValue(Board b, int posx, int posy)
{
  // Check for out of range exceptions
  if (posx < b.tailleX && posy < b.tailleY && posx >= 0 && posy >=0)
  {
    return b.tab[posx][posy];
  }
  else
  {
    printf("GetValue: error out of range\n");
    return -1;
  }
}

void setValue(Board b, int posx, int posy, int val)
{
  // Check for out of range exceptions
  if (posx < b.tailleX && posy < b.tailleY && posx >= 0 && posy >=0)
  {
    b.tab[posx][posy] = val;
  }
  else
  {
    printf("SetValue: error out of range\n");
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


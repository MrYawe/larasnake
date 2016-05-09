/**
 * \file board.c
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Everything about the board class
 * \details Contains all functions to create, edit, delete and access the board
 */

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//////////////////////////////////////////
//				STRUCTURE				//
//////////////////////////////////////////

/**
 * \struct Board
 * \brief The structure of the board
 * \details The struture contains a double dimensions array, the size of the board and of the cells
 **/
struct Board
{
	int** tab;
	int sizeX;
	int sizeY;
	int sizeCell; // size by pixels of a cell
	Item itemList;
};

//////////////////////////////////////////
//		CONSTRUCTOR/DESTRUCTOR			//
//////////////////////////////////////////

/**
 * \fn Board boardInit(int sizeX, int sizeY, int sizeCell)
 * \brief The function creates an instance of the board
 * \details The function store the board in the memory and initialize it
 * \param sizeX Int Represents the size X of the board to create
 * \param sizeY Int Represents the size Y of the board to create
 * \param sizeCell Int Represents the size of the cells of the board when it will be printed
 * \return Returns a pointer to the created board
 */
Board boardInit(int sizeX, int sizeY, int sizeCell)
{
	Board b;
	// Check for negative sizes
	if (sizeX >= 0 && sizeY >=0 && sizeCell >= 0)
	{
		b = (Board) malloc(sizeof(struct Board));

		// Allocation of tab
		b->tab = (int**) malloc(sizeY*sizeof(int*));
		int i;
		
		for ( i = 0; i < sizeY; i++)
		  b->tab[i] = (int*) calloc(sizeX, sizeof(int));

		// Set sizes
		b->sizeX = sizeX;
		b->sizeY = sizeY;
		b->sizeCell = sizeCell;

		b->itemList = itemCreate(-1, -1, SENTRY);
	}
	else
		printf("boardInit: error negative size!\n");

	return b;
}

/**
 * \fn void boardFree(Board b)
 * \brief The function free the board
 * \details The function free the board of the memory
 * \param b Board : The board to free
 */
void boardFree(Board b)
{
	int i;
	if(b!=NULL) {
		for ( i = 0; i < b->sizeY; i++)
			free(b->tab[i]);
		free(b->tab);
		free(b);
	}
}

//////////////////////////////////////////
//				ACCESSORS				//
//////////////////////////////////////////

/**
 * \fn int boardGetValue(Board b, int posx, int posy)
 * \brief The function allow to get a value in the board
 * \details The function tests if the parameters are correct and if it's the case, it returns the value
 * \param b Board : Represents the board to access
 * \param x int : The position to access
 * \param y int : The position to access
 * \return Returns int which correspond to the correct value / -1 if out of range
 */
int boardGetValue(Board b, int x, int y)
{
	// Check for out of range exceptions
	if (b!=NULL && boardInside(b, x, y))
		return b->tab[y][x];
	else
	{
		printf("boardGetValue: outside of range (%d, %d) max(%d, %d)\n", x, y, b->sizeX-1, b->sizeY-1);
		return -1;
	}
}

/**
 * \fn void boardSetValue(Board b, int posx, int posy, int val)
 * \brief The function allow to set a value in the board
 * \details The function test if the parameters are correct and if it's the case, it puts the value in the board
 * \param b Board : Represents the board to set
 * \param x int : The x position to set
 * \param y int : The y position to set
 * \param val Int : The value to set in the board
 */
void boardSetValue(Board b, int x, int y, int val)
{
	// Check for out of range exceptions
	if (b!=NULL && boardInside(b, x, y))
		b->tab[y][x] = val;
	else
		printf("boardSetValue: error out of range\n");
}

/**
 * \fn int boardGetHeight(Board b)
 * \brief The function returns the value of the height of the board
 * \details The function returns the value of sizeY of the structure board
 * \param b Board : The board to access
 * \return Returns int which correspond to the height of the current board
 */
int boardGetHeight(Board b)
{
  int res = -1;
  if (b != NULL)
      res = b->sizeY;
  return res;
}

/**
 * \fn int boardGetWidth(Board b)
 * \brief The function returns the value of the width of the board
 * \details The function returns the value of sizeX of the structure board
 * \param b Board : The board to access
 * \return Returns int which correspond to the width of the current board
 */
int boardGetWidth(Board b)
{
  int res = -1;
  if (b != NULL)
      res = b->sizeX;
  return res;
}


Item boardGetItemList(Board board) {
	return board->itemList;
}

//////////////////////////////////////////
//				UTILITARY				//
//////////////////////////////////////////

/**
 * \fn bool boardInside(Board b, Coord coord)
 * \brief La fonction vérifie si la position est dans le board
 * \param b Variable de type Board qui correspond au tableau à effacer
 * \param x position X de la case à tester
 * \param y position Y de la case à tester
 */
bool boardInside(Board b, int x, int y)
{
  bool res = false;
  if (x >= 0 && y >= 0 && x < boardGetWidth(b) && y < boardGetHeight(b))
      res = true;
  return res;
}

/**
 * \fn void boardDisplay(Board b)
 * \brief The function allow to print the board in the console
 * \details The console display all cells of the board in the console
 * \param b Board : The board to print
 */
void boardDisplay(Board b)
{
	system("clear");
	int i, j;
	for(j=0; j<b->sizeY; j++)
	{
		for (i=0; i<b->sizeX; i++)
  			printf(" %d ", boardGetValue(b, i, j));
		printf("\n");
	}

}

/*
 * \fn boardCopy
 * \brief The function returns a copy of the board
 * \details The function copy everything of the board and put it in an other variable
 * \param b Board : The board to access
 * \return Returns Board which point to the new copied board
 */
Board boardCopy(Board b)
{
	if (b == NULL)
		return NULL;
	Board res = boardInit(b->sizeX, b->sizeY, b->sizeCell);
	int j, i;
	
	for(j=0; j<b->sizeY; j++)
	{
		for (i=0; i<b->sizeX; i++)
		  boardSetValue(res, i, j, boardGetValue(b, i, j));
	}
	return res;
}

// ajout en fin
Item boardItemAdd(Board board, Item list, int x, int y, BoardValue value) {
    itemAdd(list, x, y, value);
    boardSetValue(board, x, y, value);
    return list;
}

int boardItemDelete(Board board, Item item) {
    if(itemDelete(item))
    {
        boardSetValue(board, item->posX, item->posY, EMPTY);
        itemFree(item);
        return 1;
    }
    return 0;
}
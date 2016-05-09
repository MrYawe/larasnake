/**
 * \file ia.c
 * \author groupe Larakis
 * \version 1
 * \date 17/04/2016
 * \brief Intelligence Artificielle
 * \details Fichier regroupant les différentes Intelligences Artificielles.
 */
#include <stdlib.h>
#include <stdio.h>

#include "ia.h"
#include "coord.h"


void iaDirectionsAvailable(Board board, Coord coord, int* tab, int testDirection) {
	Direction dir;
	if(testDirection==-1){
		for(dir=UP;dir<=LEFT;dir++) {
			if(!boardIsNextCellType(board, coord->x, coord->y, dir, 3, OUTSIDE, SNAKE1, SNAKE2))
				tab[dir]+=1;
		}
	}else {
		for(dir=UP;dir<=LEFT;dir++) {
			if(!boardIsNextCellType(board, coord->x, coord->y, dir, 3, OUTSIDE, SNAKE1, SNAKE2))
				tab[testDirection]+=1;
		}
	}
}

Direction iaDirectionRandomize(int* tab, int value) {
	int choose = (rand()%4);
	int i=0;
	int j=0;

	do {
		while(tab[i]!=value){
			i++;
			i%=4;
		}
		if(j!=choose){
			i++;
			i%=4;
		}
	} while(j++!=choose);

	return i;
}

int iaDirectionMaxValue(int* tab){
	Direction dir;
	Direction dirMax;

	dirMax = UP;
	for(dir=UP;dir<=LEFT;dir++) {
		//printf("tab SENS:%d valeur: %d\n", dir, tab[dir]);
		if(tab[dirMax]<tab[dir]){
			dirMax=dir;
		}
	}
	return tab[dirMax];
}

void iaDirectionItem(Board board, Snake snake, int* tab) {
	Item item = boardGetItemList(board);

    if(item->next != NULL) {
        Item item1 = item->next;
    }

}



Direction iaSurviveDepth(Board board, Snake snake) {
	Direction dirSnake = snakeGetDirection(snake);
	Coord posSnakeHead = snakeGetPos(snake, snakeGetSize(snake)-1);
	Coord posInter = coordNew(posSnakeHead->x,posSnakeHead->y);
	Coord posNext = coordNew(posSnakeHead->x,posSnakeHead->y);

    Board boardIa = boardCopy(board);

	//printf("POSITION SNAKE : x:%d y:%d \n", posSnake->x, posSnake->y);

	int* tab = calloc(4, sizeof(int));
	int i=0;
	int j=0;

	iaDirectionItem(board, snake, tab);
	iaDirectionsAvailable(boardIa, posSnakeHead, tab, -1);

	for(j=0;j<4;j++){
		//printf("\nAvailable Direction %d \n", j);
		posNext->x=posSnakeHead->x;
		posNext->y=posSnakeHead->y;
		for(i=0;i<5;i++){

			if(tab[j]!=0){
				posInter = boardNextPosCell(posNext->x, posNext->y, j);

				if(boardInside(boardIa, posInter->x, posInter->y)) {
					boardSetValue(boardIa, posInter->x, posInter->y, snakeGetId(snake));
				}

				//printf("Positions testées x:%d y:%d\n", posInter->x, posInter->y);
				iaDirectionsAvailable(boardIa, posInter, tab, j);
				posNext->x=posInter->x;
				posNext->y=posInter->y;
			}
		}
	}
	dirSnake = iaDirectionRandomize(tab,iaDirectionMaxValue(tab));
	//
	free(posNext);
	free(posInter);
	free(tab);
	free(boardIa);
	//printf("direction: %d\n", dirSnake);
	return dirSnake;
}

Direction iaRandom (Board board, Snake snake) {
	Direction dirSnake = snakeGetDirection(snake);
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);
	int* tab = calloc(4, sizeof(int));

	iaDirectionsAvailable(board, posSnake, tab, -1);
	int choose = (rand()%4);
	int i=0;
	int j=0;

	//printf("UP:%d RIGHT:%d DOWN:%d LEFT:%d \n", tab[0], tab[1], tab[2], tab[3]);
	//printf("choose:%d\n", choose);
	if(!(tab[0]==0 && tab[1]==0 && tab[2]==0 && tab[3]==0)){
		do {
			while(tab[i]==0){
				i++;
				i%=4;
			}
			if(j!=choose){
				i++;
				i%=4;
			}
		} while(j++!=choose);
	}


	dirSnake=i;

	//printf("direction choisie: %d\n\n", dirSnake);
	free(tab);

	return dirSnake;
}

/**
 * \fn Direction iaSurvive (Board board, Snake snake)
 * \brief Function used to get a direction for the snake to follow to not die
 * \details Function that checks if the snake can go forward. If not, it tries to go right then left.
 * \param board Variable representing the board
 * \param snake Variable representing the snake
 * \return <Direction> used to change the snake direction
 */
Direction iaSurvive (Board board, Snake snake) {
	Direction snakeDir = snakeGetDirection(snake);
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);

	//Checking if the next Cell in front of the snake would make him die
	if(boardIsNextCellType(board, posSnake->x, posSnake->y, snakeDir, 3, OUTSIDE, SNAKE1, SNAKE2))
	{
		if(snakeDir==UP || snakeDir==DOWN)//Checking if the snake is going up or down
		{
			//Checking if the snake can go to the right without dying
			if(!boardIsNextCellType(board, posSnake->x, posSnake->y, RIGHT, 3, OUTSIDE, SNAKE1, SNAKE2))
				snakeDir=RIGHT;
			//Checking if the snake can go to the left without dying
			else if(!boardIsNextCellType(board, posSnake->x, posSnake->y, LEFT, 3, OUTSIDE, SNAKE1, SNAKE2))
				snakeDir=LEFT;
		}
		else if(snakeDir==RIGHT || snakeDir==LEFT)//Checking if the snake is going to the right or to the left
		{
			//Checking if the snake can go down without dying
			if(!boardIsNextCellType(board, posSnake->x, posSnake->y, DOWN, 3, OUTSIDE, SNAKE1, SNAKE2))
				snakeDir=DOWN;
			//Checking if the snake can go up without dying
			else if(!boardIsNextCellType(board, posSnake->x, posSnake->y, UP, 3, OUTSIDE, SNAKE1, SNAKE2))
				snakeDir=UP;
		}
	}

	return snakeDir;
}

/**
 * \fn Direction iaJambon (Game game, Snake snake)
 * \brief Function used to chase the given bonus without dying
 * \details Function that goes to the given bonus and that is calling iaSurvive to not die
 * \param board Variable representing the board
 * \param snake Variable representing the snake
 * \return <Direction> used to change the snake direction
 */

/*
Direction iaJambon (Game game, Snake snake) {

	Direction snakeDir = snakeGetDirection(snake);
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);
	Item food = gameGetFood(game);
	Coord posBonus = coordNew(food->posX, food->posY);
	Board board = gameGetBoard(game);

	if(!(posBonus->x == 0 && posBonus->y == 0))//Checking if there is a bonus to chase
	{
		if(snakeDir==UP || snakeDir==DOWN)//Checking if the snake is going UP or DOWN
		{
			if (posSnake->x < posBonus->x)//Checking if the bonus is on the right
			{
				//Checking if the snake can go to the right without dying
				if(!boardIsNextCellType(board, posSnake->x, posSnake->y, RIGHT, 3, OUTSIDE, SNAKE1, SNAKE2))
					snakeDir=RIGHT;
			}
			else if(posSnake->x > posBonus->x) //Checking if the bonus is on the left
			{
				//Checking if the snake can go to the right without dying
				if(!boardIsNextCellType(board, posSnake->x, posSnake->y, LEFT, 3, OUTSIDE, SNAKE1, SNAKE2))
					snakeDir=LEFT;
			}
			else if(posSnake->x == posBonus->x) //Checking if the snake is on the right x
			{
				if((snakeDir==UP && posSnake->y < posBonus->y) || (snakeDir==DOWN && posSnake->y > posBonus->y))//Checking if the snake is in the good direction
				{
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellType(board, posSnake->x, posSnake->y, RIGHT, 3, OUTSIDE, SNAKE1, SNAKE2))
						snakeDir=RIGHT;
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellType(board, posSnake->x, posSnake->y, LEFT, 3, OUTSIDE, SNAKE1, SNAKE2))
						snakeDir=LEFT;
				}
			}
		}
		else if(snakeDir==RIGHT || snakeDir==LEFT)//Checking if the snake is going RIGHT or LEFT
		{
			if(posSnake->y > posBonus->y)//Checking if the bonus is somewhere over the snake
			{
				//Checking if the snake can go up without dying
				if(!boardIsNextCellType(board, posSnake->x, posSnake->y, UP, 3, OUTSIDE, SNAKE1, SNAKE2))
					snakeDir=UP;
			}
			else if(posSnake->y < posBonus->y)//Checking if the bonus is somewhere down the snake
			{
				//Checking if the snake can go down without dying
				if(!boardIsNextCellType(board, posSnake->x, posSnake->y, DOWN, 3, OUTSIDE, SNAKE1, SNAKE2))
					snakeDir=DOWN;
			}
			else if(posSnake->y == posBonus->y) { //Checking if the snake is on the right y
				if((snakeDir==RIGHT && posSnake->x > posBonus->x) || (snakeDir==LEFT && posSnake->x < posBonus->x)) //Checking if the direction is wrong
				{
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellType(board, posSnake->x, posSnake->y, DOWN, 3, OUTSIDE, SNAKE1, SNAKE2))
						snakeDir=DOWN;
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellType(board, posSnake->x, posSnake->y, UP, 3, OUTSIDE, SNAKE1, SNAKE2))
						snakeDir=UP;
				}
			}
		}
		//Checking if the chosen direction won't kill the snake (used when the snake is on the right x posSnakeition)
		if(boardIsNextCellType(board, posSnake->x, posSnake->y, snakeDir, 3, OUTSIDE, SNAKE1, SNAKE2))
			snakeDir = iaSurvive(board, snake);
	}
	else//If there is no bonus to chase, then just survive
	{
		snakeDir = iaSurvive(board, snake);
	}

	// /!\ Just to test out with the jambon /!\
	if(coordEquals(boardNextPosCell(posSnake->x, posSnake->y, snakeDir),posBonus))
	{
		free(gameGetFood(game));
		gameFeed(game);
	}


	free(posSnake);
	free(posBonus);
	return snakeDir;
}
*/

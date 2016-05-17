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
#include <math.h>

#include "ia.h"
#include "coord.h"


void iaDirectionsAvailable(Board board, Coord coord, double* tab, int testDirection) {
	Direction dir;
	if(testDirection==-1){
		for(dir=UP;dir<=LEFT;dir++) {
			if(!boardIsNextCellType(board, coord->x, coord->y, dir, 3, OUTSIDE, SNAKE1, SNAKE2))
				tab[dir]+=10000;
		}
	}else {
		for(dir=UP;dir<=LEFT;dir++) {
			if(!boardIsNextCellType(board, coord->x, coord->y, dir, 3, OUTSIDE, SNAKE1, SNAKE2))
				tab[testDirection]+=50;
		}
	}
}

Direction iaDirectionRandomize(double* tab, double value) {
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

double iaDirectionMaxValue(double* tab){
	Direction dir;
	Direction dirMax;

	dirMax = UP;
	for(dir=UP;dir<=LEFT;dir++) {
		if(tab[dirMax]<tab[dir]){
			dirMax=dir;
		}
	}
	return tab[dirMax];
}

double iaDistance(Coord pos1, Coord pos2){
	//return sqrt((pos2->x-pos1->x)*(pos2->x-pos1->x) + (pos2->y-pos1->y)*(pos2->y-pos1->y));
	return fabs(pos1->x-pos2->x) + fabs(pos1->y-pos2->y);
}

void iaDirectionItem(Board board, Snake snake, double* tab) {
	Item item = boardGetItemList(board);
	
	if(item->next != NULL) 
	{
		item=item->next;
		iaValueGoToCell(board, snake, item->posX, item->posY, tab);
	}
}

void iaKillEnnemySnake(Board board, Snake snake, Snake ennemySnake, double* tab) {
	Coord posEnnemySnakeHead = snakeGetPos(ennemySnake, snakeGetSize(snake)-1);
	Direction dirSnake = snakeGetDirection(ennemySnake);
	Coord posGoTo = boardNextPosCell(posEnnemySnakeHead->x, posEnnemySnakeHead->y, dirSnake);

	if(boardInside(board, posGoTo->x, posGoTo->y))
		iaValueGoToCell(board, snake, posGoTo->x, posGoTo->y, tab);

	free(posGoTo);
}

void iaValueSurviveCollisionSnake(Board board, Snake snake, double* tab)
{
	Coord posSnakeHead = snakeGetPos(snake, snakeGetSize(snake)-1);
	Coord posInter = coordNew(posSnakeHead->x,posSnakeHead->y);
	Coord posNext = coordNew(posSnakeHead->x,posSnakeHead->y);
	Board boardIa  = boardCopy(board);

	Direction dirSnake = snakeGetDirection(snake);
	Direction dirSnakeInverse = (dirSnake+2)%4;
	//double value = 100.0;

	Direction i = UP;
	int j=0;

	for(i=UP;i<=LEFT;i++){
		posNext->x=posSnakeHead->x;
		posNext->y=posSnakeHead->y;
		for(j=0;j<10;j++){

			if(i!=dirSnakeInverse){
				posInter = boardNextPosCell(posNext->x, posNext->y, i);

				if(boardInside(boardIa, posInter->x, posInter->y)) {
					boardSetValue(boardIa, posInter->x, posInter->y, snakeGetId(snake));
				}

				//printf("Positions testées x:%d y:%d\n", posInter->x, posInter->y);
				iaDirectionsAvailable(boardIa, posInter, tab, i);
				posNext->x=posInter->x;
				posNext->y=posInter->y;
			}
		}
	}
	free(posNext);
	free(posInter);
	boardFree(boardIa);
	//free(boardIa);
}

void iaValueSurviveCollisionBorder(Board board, Snake snake, double* tab){
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);
	Direction dirSnake = snakeGetDirection(snake);
	Direction dirSnakeInverse = (dirSnake+2)%4;
	double value = 100.0;

	Direction i = UP;

	for(i=UP;i<=LEFT;i++){
		if(i!=dirSnakeInverse){
			if(i==UP) {
				tab[i] += (1.0*posSnake->y/(1.0*boardGetHeight(board))) * value;
			}
			else if(i==RIGHT) {
				tab[i] += 1.0*(boardGetWidth(board)-1-(posSnake->x))/(1.0*boardGetWidth(board))*value;
			}
			else if(i==DOWN) {
				tab[i] += 1.0*(boardGetHeight(board)-1-(posSnake->y))/(1.0*boardGetHeight(board))*value;
			}
			else if(i==LEFT) {
				tab[i] += 1.0*(posSnake->x/(1.0*boardGetWidth(board))) * value;
			}
		}
		//printf("tab[%d] = %f\n", i, tab[i]);
	}
}

/**
 * \fn void iaValueGoToCell(Board board, Snake snake, int x, int y, double* tab)
 * \brief function that puts in the tab the values depending on the cell where the snake should go
 * \details function that puts in the tab the values depending on the cell where the snake should go
 * \param board Variable representing the board
 * \param snake Variable representing the ai snake
 * \param int Variable position x where the snake should go
 * \param int Variable position y where the snake should go
 * \param double Variable array used to memorise the values for each direction
 */
void iaValueGoToCell(Board board, Snake snake, int x, int y, double* tab)
{
	Coord posSnakeHead = snakeGetPos(snake, snakeGetSize(snake)-1);
	Direction dirSnake = snakeGetDirection(snake);
	Direction dirSnakeInverse = (dirSnake+2)%4;

	Coord posGoTo = coordNew(x, y);
	Coord posInter;

	double value = 100.0;
	double distance = 0.0;
	double distanceMax = 0.0;
	Coord cornerUpLeft = coordNew(0,0);
	Coord cornerDownRight = coordNew(boardGetWidth(board)-1,boardGetHeight(board)-1);
	distanceMax = iaDistance(cornerUpLeft,cornerDownRight);


	int i=0;

	for(i=UP;i<=LEFT;i++)
	{
		if(i!=dirSnakeInverse){
			posInter = boardNextPosCell(posSnakeHead->x, posSnakeHead->y, i);
			distance = iaDistance(posGoTo, posInter);
			tab[i]+=(distanceMax/distance)*value;
			//printf("tab[%d] = %f\n", i , tab[i]);
			free(posInter);
		}
	}
	free(posGoTo);
	free(cornerDownRight);
	free(cornerUpLeft);
}

/**
 * \fn Direction iaSurviveDepth (Board board, Snake snake, Snake ennemySnake)
 * \brief Ia that uses a valued tab to choose the best position to survive and to either kill the ennemy or go to an item
 * \details Ia that uses a valued tab to choose the best position to survive and to either kill the ennemy or go to an item
 * \param board Variable representing the board
 * \param snake Variable representing the ai snake
 * \param snake Variable representing the ennemy snake
 * \return <Direction> used to change the snake direction
 */
Direction iaSurviveDepth(Board board, Snake snake, Snake ennemySnake) {
	Direction dirSnake = snakeGetDirection(snake);
	Coord posSnakeHead = snakeGetPos(snake, snakeGetSize(snake)-1);

    Board boardIa = boardCopy(board);

	double* tab = calloc(4, sizeof(double));

	iaDirectionsAvailable(boardIa, posSnakeHead, tab, -1);
	//iaDirectionItem(board, snake, tab);
	iaKillEnnemySnake(board, snake, ennemySnake, tab);
	iaValueSurviveCollisionSnake(board, snake, tab);

	dirSnake = iaDirectionRandomize(tab,iaDirectionMaxValue(tab));
	
	free(tab);
	boardFree(boardIa);
	return dirSnake;
}

/**
 * \fn Direction iaRandom (Game game, Snake snake)
 * \brief Ia that choose a random direction beetween the case available around 
 * \details Ia that choose a random direction beetween the case available around 
 * \param board Variable representing the board
 * \param snake Variable representing the snake
 * \return <Direction> used to change the snake direction
 */
Direction iaRandom (Board board, Snake snake) {
	Direction dirSnake = snakeGetDirection(snake);
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);
	double* tab = calloc(4, sizeof(int));

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

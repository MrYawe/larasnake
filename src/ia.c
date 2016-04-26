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

/*
int* iaDirectionsAvailable(Board board, Coord coord, Direction dir) {
	int *res = malloc(4 * sizeof(int));
	for(dir=UP;dir<=LEFT;dir++) {
		if(!boardIsNextCellType(board, coord->x, coord->y, dir, 2, SNAKE1, SNAKE2) && !boardIsNextCellBorder(board, coord->x, coord->y, dir))
			res[dir]=1;
	}
	return res;
}*/
/*
Direction iaRandom (Board board, Snake snake) {
	Direction snakeDir = snakeGetDirection(snake);
	Coord posSnake = snakeGetPos(snake, snakeGetSize(snake)-1);

	//Checking if the next Cell in front of the snake would make him die
	if(boardIsNextCellBorder(board, posSnake->x, posSnake->y, snakeDir) || boardIsNextCellSnake(board, posSnake->x, posSnake->y, snakeDir))
	{
		if(snakeDir==UP || snakeDir==DOWN)//Checking if the snake is going up or down
		{
			//Checking if the snake can go to the right without dying
			if(!boardIsNextCellSnake(board, posSnake->x, posSnake->y, RIGHT) && !boardIsNextCellBorder(board, posSnake->x, posSnake->y, RIGHT))
				snakeDir=RIGHT;
			//Checking if the snake can go to the left without dying
			else if(!boardIsNextCellSnake(board, posSnake->x, posSnake->y, LEFT) && !boardIsNextCellBorder(board, posSnake->x, posSnake->y, LEFT))
				snakeDir=LEFT;
		}
		else if(snakeDir==RIGHT || snakeDir==LEFT)//Checking if the snake is going to the right or to the left
		{
			//Checking if the snake can go down without dying
			if(!boardIsNextCellSnake(board, posSnake->x, posSnake->y, DOWN) && !boardIsNextCellBorder(board, posSnake->x, posSnake->y, DOWN))
				snakeDir=DOWN;
			//Checking if the snake can go up without dying
			else if(!boardIsNextCellSnake(board, posSnake->x, posSnake->y, UP) && !boardIsNextCellBorder(board, posSnake->x, posSnake->y, UP))
				snakeDir=UP;
		}
	}
	//free(posSnake);
	return snakeDir;
}*/

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

	free(posSnake);
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

	/* /!\ Just to test out with the jambon /!\ */ 
	if(coordEquals(boardNextPosCell(posSnake->x, posSnake->y, snakeDir),posBonus))
	{
		free(gameGetFood(game));
		gameFeed(game);
	}	


	free(posSnake);
	free(posBonus);
	return snakeDir;
}
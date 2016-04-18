/**
 * \file ia.c
 * \author groupe Larakis
 * \version 1
 * \date 17/04/2016
 * \brief Intelligence Artificielle
 * \details Fichier regroupant les différentes Intelligences Artificielles.
 */
 
#include "ia.h"
#include "coord.h"
#include "game.h"

/**
 * \fn iaSurvive
 * \brief Function used to get a direction for the snake to follow to not die
 * \details Function that checks if the snake can go forward. If not, it tries to go right then left.
 * \param board Variable representing the board
 * \param snake Variable representing the snake
 * \return <Direction> used to change the snake direction
 */
Direction iaSurvive (Board* board, Snake* snake) {
	Direction snakeDir = snakeGetDirection(snake);
	Coord snakePos = snakeGetPos(snake, snakeGetSize(snake)-1);

	//Checking if the next Cell in front of the snake would make him die
	if(boardIsNextCellBorder(board, snakePos->x, snakePos->y, snakeDir) || boardIsNextCellSnake(board, snakePos->x, snakePos->y, snakeDir))
	{
		if(snakeDir==UP || snakeDir==DOWN)//Checking if the snake is going up or down
		{
			//Checking if the snake can go to the right without dying
			if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, RIGHT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, RIGHT))
				snakeDir=RIGHT;
			//Checking if the snake can go to the left without dying
			else if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, LEFT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, LEFT))
				snakeDir=LEFT;
		}
		else if(snakeDir==RIGHT || snakeDir==LEFT)//Checking if the snake is going to the right or to the left
		{
			//Checking if the snake can go down without dying
			if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, DOWN) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, DOWN))
				snakeDir=DOWN;
			//Checking if the snake can go up without dying
			else if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, UP) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, UP))
				snakeDir=UP;
		}
	}
	return snakeDir;
}

//TO MODIFY WHEN THERE WILL BE A LIST OF BONUS

/**
 * \fn iaJambon
 * \brief Function used to chase the given bonus without dying
 * \details Function that goes to the given bonus and that is calling iaSurvive to not die
 * \param board Variable representing the board
 * \param snake Variable representing the snake
 * \return <Direction> used to change the snake direction
 */
Direction iaJambon (Board *board, Snake *snake) {

	Direction snakeDir = snakeGetDirection(snake);
	Coord snakePos = snakeGetPos(snake, snakeGetSize(snake)-1);
	Coord posBonus = boardGetJambon(board);

	if(!(boardGetJambon(board)->x == 0 && boardGetJambon(board)->y == 0))//Checking if there is a bonus to chase
	{
		if(snakeDir==UP || snakeDir==DOWN)//Checking if the snake is going UP or DOWN
		{
			if (snakePos->x < posBonus->x)//Checking if the bonus is on the right
			{
				//Checking if the snake can go to the right without dying
				if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, RIGHT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, RIGHT))
					snakeDir=RIGHT;
			}
			else if(snakePos->x > posBonus->x) //Checking if the bonus is on the left
			{
				//Checking if the snake can go to the right without dying
				if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, LEFT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, LEFT))
					snakeDir=LEFT;
			} 
			else if(snakePos->x == posBonus->x) //Checking if the snake is on the right x
			{
				if((snakeDir==UP && snakePos->y < posBonus->y) || (snakeDir==DOWN && snakePos->y > posBonus->y))//Checking if the snake is in the good direction 
				{
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, RIGHT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, RIGHT))
						snakeDir=RIGHT;
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, LEFT) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, LEFT))
						snakeDir=LEFT;
				}
			}
		} 
		else if(snakeDir==RIGHT || snakeDir==LEFT)//Checking if the snake is going RIGHT or LEFT
		{
			if(snakePos->y > posBonus->y)//Checking if the bonus is somewhere over the snake
			{
				//Checking if the snake can go up without dying
				if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, UP) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, UP))
					snakeDir=UP;
			}
			else if(snakePos->y < posBonus->y)//Checking if the bonus is somewhere down the snake
			{
				//Checking if the snake can go down without dying
				if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, DOWN) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, DOWN))
					snakeDir=DOWN;
			}
			else if(snakePos->y == posBonus->y) { //Checking if the snake is on the right y
				if((snakeDir==RIGHT && snakePos->x > posBonus->x) || (snakeDir==LEFT && snakePos->x < posBonus->x)) //Checking if the direction is wrong
				{
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, DOWN) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, DOWN))
						snakeDir=DOWN;
					//Checking if the snake can go to the right without dying
					if(!boardIsNextCellSnake(board, snakePos->x, snakePos->y, UP) && !boardIsNextCellBorder(board, snakePos->x, snakePos->y, UP))
						snakeDir=UP;
				}
			}
		}
		//Checking if the chosen direction won't kill the snake (used when the snake is on the right x snakePosition)
		if(boardIsNextCellSnake(board, snakePos->x, snakePos->y, snakeDir) || boardIsNextCellBorder(board, snakePos->x, snakePos->y, snakeDir))
			snakeDir = iaSurvive(board, snake);
	} 
	else//If there is no bonus to chase, then just survive
	{
		snakeDir = iaSurvive(board, snake);
	}

	/* /!\ Just to test out with the jambon /!\ */
	if(coordEquals(boardNextPosCell(snakePos->x, snakePos->y, snakeDir),posBonus))
		boardSetJambon(board, 0, 0);
	
	return snakeDir;
}


int iaFront(Board *board, int x, int y, Direction dir) 
{
	int res = 0;
	Coord nextPos;
	while(!boardIsNextCellSnake(board, x, y, dir) && !boardIsNextCellBorder(board, x, y, dir)) 
	{
		res++;
		nextPos = boardNextPosCell(x, y, dir);
		x=nextPos->x;
		y=nextPos->y;
	}
	//free(nextPos);
	return res;
}

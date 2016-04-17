#include "ia.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "coord.h"
#include "game.h"

Direction iaSurvive (Board *board, Snake *snake) {
	Direction dir = snakeGetDirection(snake);
	Coord pos = snakeGetPos(snake, snakeGetSize(snake)-1);

	if(isNextCellBorder(board, snake) || isNextCellSnake(board, snake)) {
		if(dir==UP || dir==DOWN) 
		{
			if(!boardIsNextCellSnake(board, pos->x, pos->y, RIGHT) && !boardIsNextCellBorder(board, pos->x, pos->y, RIGHT))
			{
				dir=RIGHT;
			} 
			else if(!boardIsNextCellSnake(board, pos->x, pos->y, LEFT) && !boardIsNextCellBorder(board, pos->x, pos->y, LEFT))
			{
				dir=LEFT;
			}

		}
		else if(dir==RIGHT || dir==LEFT)
		{
			if(!boardIsNextCellSnake(board, pos->x, pos->y, UP) && !boardIsNextCellBorder(board, pos->x, pos->y, UP))
			{
				dir=UP;
			} 
			else if(!boardIsNextCellSnake(board, pos->x, pos->y, DOWN) && !boardIsNextCellBorder(board, pos->x, pos->y, DOWN))
			{
				dir=DOWN;
			}
		}
	}
	return dir;
}

Direction iaJambon (Board *board, Snake *snake) {
	Direction dir = snakeGetDirection(snake);

	Coord pos = snakeGetPos(snake, snakeGetSize(snake)-1);
	Coord posJambon = boardGetJambon(board);
	if(!(boardGetJambon(board)->x == 0 && boardGetJambon(board)->y == 0)){
		if(dir==UP || dir==DOWN) {
			if (pos->x < posJambon->x)
			{
				//Aller à droite
				if(!boardIsNextCellSnake(board, pos->x, pos->y, RIGHT) && !boardIsNextCellBorder(board, pos->x, pos->y, RIGHT)){
					dir=RIGHT;
				}
			}
			else if(pos->x > posJambon->x) 
			{
				//aller à gauche
				if(!boardIsNextCellSnake(board, pos->x, pos->y, LEFT) && !boardIsNextCellBorder(board, pos->x, pos->y, LEFT)){
					dir=LEFT;
				}
			}
			if(boardIsNextCellSnake(board, pos->x, pos->y, dir) || boardIsNextCellBorder(board, pos->x, pos->y, dir)){
				dir = iaSurvive(board, snake);
			}
		} 
		else if(dir==RIGHT || dir==LEFT)
		{
			if(pos->y > posJambon->y)
			{
				//aller en haut
				if(!boardIsNextCellSnake(board, pos->x, pos->y, UP) && !boardIsNextCellBorder(board, pos->x, pos->y, UP)){
					dir=UP;
				}
			}
			else if(pos->y < posJambon->y)
			{
				//aller en bas
				if(!boardIsNextCellSnake(board, pos->x, pos->y, DOWN) && !boardIsNextCellBorder(board, pos->x, pos->y, DOWN)){
					dir=DOWN;
				}
			}
			if(boardIsNextCellSnake(board, pos->x, pos->y, dir) || boardIsNextCellBorder(board, pos->x, pos->y, dir)){
				dir = iaSurvive(board, snake);
			}
		}
	} 
	else 
	{
		dir = iaSurvive(board, snake);
	}
	if(coordEquals(boardNextPosCell(pos->x, pos->y, dir),posJambon)) {
		boardSetJambon(board, 0, 0);
	}
	return dir;
}

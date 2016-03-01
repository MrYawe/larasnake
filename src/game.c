#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"

static void checkMovement(Snake *s);

Board* initGame()
{
	Board *b = boardInit(14, 14);
	Snake *s1 = snakeCreate(3, 1);
	Snake *s2 = snakeCreate(3, 2);
	initSnakes(b, s1, s2);
	boardDisplay(b);
	while(1)
	{
		moveSnake(b, s1);
		moveSnake(b, s2);
		boardDisplay(b);
		sleep(1);
	}
	return b;
}

void initSnakes(Board *b, Snake *s1, Snake *s2)
{
	int i;
	for (i=0; i<snakeGetSize(s1); i++)
	{
		snakeUpdateElement(s1, snakeGetSize(s1) - i -1, boardGetSize(b, Line)/3-i, boardGetSize(b, Column)/2-1);
	}
	snakeSetDirection(s1, RIGHT);
	for (i=0; i<snakeGetSize(s2); i++)
	{
		snakeUpdateElement(s2, snakeGetSize(s2) - i -1, boardGetSize(b, Line)/3*2+i, boardGetSize(b, Column)/2);
	}
	snakeSetDirection(s2, LEFT);
	updateSnake(b, s1);
	updateSnake(b, s2);
}

void updateSnake(Board *b, Snake *s)
{
	int i;
	for (i=0; i<snakeGetSize(s); i++)
	{
		boardSetValue(b, snakeGetPos(s, i, Line), snakeGetPos(s, i, Column), snakeGetId(s));
	}
}

void moveSnake(Board *b, Snake *s)
{
	Way w = snakeGetWay(s);
	snakeDisplay(s);
	if (w == Normal)
	{
		boardSetValue(b, snakeGetPos(s, 0, Line), snakeGetPos(s, 0, Column), 0);
		checkMovement(s);
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1, Line), snakeGetPos(s, snakeGetSize(s)-1, Column), snakeGetId(s));
	}
	else if (w == Reversed)
	{
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1, Line), snakeGetPos(s, snakeGetSize(s)-1, Column), 0);
		checkMovement(s);
		boardSetValue(b, snakeGetPos(s, 0, Line), snakeGetPos(s, 0, Column), snakeGetId(s));
	}	
}

static void checkMovement(Snake *s)
{
	switch (snakeGetDirection(s))
	{ 
		case UP:
			snakeGoUp(s);
		break;
		case DOWN:
			snakeGoDown(s);
		break;
		case LEFT:
			snakeTurnLeft(s);
		break;
		case RIGHT:
			snakeTurnRight(s);
		break;
		default:
			printf("Error checkMovement\n");
		break;
	}	
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"

static void checkMovement(Snake *s, Board *b);
static bool isNextCellBorder(Board *b, Snake *s);

void initGame(sizeX, sizeY)
{
	Board *b = boardInit(sizeX, sizeY);
	Snake *s1 = snakeCreate(3, 1);
	Snake *s2 = snakeCreate(3, 2);
	initSnakes(b, s1, s2);
	boardDisplay(b);
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
	// updateSnake(b, s2);
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
	boardSetValue(b, snakeGetPos(s, 0, Line), snakeGetPos(s, 0, Column), 0);
	checkMovement(s, b);
	boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1, Line), snakeGetPos(s, snakeGetSize(s)-1, Column), snakeGetId(s));
}

int nextPosCell(Snake *s, Control c)
{
	int res = snakeGetPos(s, snakeGetSize(s)-1, c);
	switch (snakeGetDirection(s))
	{
		case UP:
			if (c == Column)
				res -= 1;
		break;
		case DOWN:
			if (c == Column)
				res += 1;
		break;
		case LEFT:
			if (c == Line)
				res -= 1;
		break;
		case RIGHT:
			if (c == Line)
				res += 1;
		break;
		default:
			printf("Error isNextCellBorder\n");
		break;
	}
	return res;
}

static bool isNextCellDie(Board *b, Snake *s)
{
	bool res = false;
	if (boardGetValue(b, nextPosCell(s, Line), nextPosCell(s, Column)) == 1)
		res = true;
	return res;
}

static bool isNextCellBorder(Board *b, Snake *s)
{
	bool res = false;
	if ((snakeGetDirection(s) == UP || snakeGetDirection(s)== DOWN) &&
		(nextPosCell(s, Column)<0 || nextPosCell(s, Column)>boardGetSize(b, Column)-1))
	{
			res = true;
	}
	else if ((snakeGetDirection(s) == LEFT || snakeGetDirection(s) == RIGHT) &&
		(nextPosCell(s, Line)<0 || nextPosCell(s, Line)>boardGetSize(b, Line)-1))
	{
		res = true;
	}
	return res;
}

static void checkMovement(Snake *s, Board *b) {
	
	if (isNextCellDie(b, s))
	{
		printf("Snake mort !\n");
	}

	if (!isNextCellBorder(b, s))
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
	else
	{
		switch (snakeGetDirection(s))
		{
			case UP:
				snakeTeleportation(s, snakeGetPos(s, snakeGetSize(s)-1, Line), boardGetSize(b, Column)-1);
			break;
			case DOWN:
				snakeTeleportation(s, snakeGetPos(s, snakeGetSize(s)-1, Line), 0);
			break;
			case LEFT:
				snakeTeleportation(s, boardGetSize(b, Line)-1, snakeGetPos(s, snakeGetSize(s)-1, Column));
			break;
			case RIGHT:
				snakeTeleportation(s, 0, snakeGetPos(s, snakeGetSize(s)-1, Column));
			break;
			default:
				printf("Error checkMovement\n");
			break;
		}
	}
}

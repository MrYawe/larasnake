#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"



/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#define SIZE 4
/****************************/

static void checkMovement(Snake *s);
static void setBufferedInput(bool enable);

void initGame()
{
	Board *b = boardInit(14, 14);
	Snake *s1 = snakeCreate(3, 1);
	Snake *s2 = snakeCreate(3, 2);
	initSnakes(b, s1, s2);
	boardDisplay(b);
	playGame(b, s1, s2);
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
	Way w = snakeGetWay(s);
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




static void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}

void playGame(Board *b, Snake *s1, Snake *s2)
{
	setBufferedInput(false);
	char c;
	bool touche = false;
	while (true) 
	{
		c = getchar();
		switch(c) 
		{
			case 68:	// left arrow
				snakeSetDirection(s1, LEFT); 
				touche = true; 
			break;
			case 67:	// right arrow
				snakeSetDirection(s1, RIGHT);
				touche = true;  
			break;
			case 66:	// up arrow
				snakeSetDirection(s1, UP);   
				touche = true;
			break;
			case 65:	// down arrow
				snakeSetDirection(s1, DOWN); 
				touche = true;  
			break;
			default: 
				touche = false;
			break;
		}
		if (touche)
		{			
			moveSnake(b, s1);
			boardDisplay(b);
		}
	}
	setBufferedInput(true);
}
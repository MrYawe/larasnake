#include "ia.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "coord.h"
#include "game.h"

Direction iaSurvive (Board *board, Snake *snake) {
	Direction dir = snakeGetDirection(snake);
	//boardDisplay(board);

	Coord pos = snakeGetPos(snake, snakeGetSize(snake)-1);
	if(isNextCellBorder(board, snake) || isNextCellSnake(board, snake)) {
		if(dir==UP || dir==DOWN) {
			//testing right case
			pos->x++;
			if(boardInside(board, pos) && !boardIsSnake(board, pos)) {
				printf("DROITE\n");
				dir=RIGHT;
			}
			else {
				//testing left case
				pos->x-=2;
				if(boardInside(board, pos) && !boardIsSnake(board, pos)) {
					printf("GAUCHE\n");
					dir=LEFT;
				}
			}
		}
		else if(dir==RIGHT||dir==LEFT){
			//testing upper case
			pos->y--;
			if(boardInside(board, pos) && !boardIsSnake(board, pos)) {
				printf("HAUT\n");
				dir=UP;
			} else {
				//testing down case
				pos->y+=2;
				if(boardInside(board, pos) && !boardIsSnake(board, pos)) {
					dir=DOWN;
					printf("BAS\n");
				}
			}
		}
	}
	/*
	int count = 0;
	int i, j;
	for(j=0; j<boardGetHeight(board); j++)
	{
		for (i=0; i<boardGetWidth(board); i++)
		{
		  if(!boardGetValue(board, i, j)) {
		  	count++;
		  }
		}
		printf("\n");
	}
	printf("Cases disponibles : %d\n", count);
*/

	return dir;
}

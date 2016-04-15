#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "game.h"
#include "coord.h"

static bool checkMovement(Snake *s, Board *b);

/**
 * \struct Game
 * \brief La structure représente une partie
 * \details La structure contient
 **/
struct Game
{
		Board *board; // le board
		Snake *snake1; // joueur 1
		Snake *snake2; // joueur 2
		bool isPlaying;
};

Game gameCreate(BoardSize size) // à faire : 3 mode de jeu différent (tiny, normal, big)
{
		Game g = malloc(sizeof(struct Game));

		switch (size) {
				case SMALL:
						g->board = boardInit(S_SIZE_BOARD_X, S_SIZE_BOARD_Y, S_CELL_SIZE);
						break;

				case MEDIUM:
						g->board = boardInit(M_SIZE_BOARD_X, M_SIZE_BOARD_Y, M_CELL_SIZE);
						break;

				case LARGE:
						g->board = boardInit(L_SIZE_BOARD_X, L_SIZE_BOARD_Y, L_CELL_SIZE);
						break;
		}

		g->snake1 = snakeCreate(7, 1, RIGHT);
		g->snake2 = snakeCreate(7, 2, LEFT);
		g->isPlaying = true;

    initSnakes(g->board, g->snake1, g->snake2);

		return g;
}

Board* gameGetBoard(Game g)
{
		return g->board;
}

Snake* gameGetSnake(Game g, int player)
{
		if (player == 1)
			return g->snake1;
		return g->snake2;
}

bool gameGetIsPlaying(Game g)
{
		return g->isPlaying;
}

// termine la partie
void gameEnd(Game g)
{
	boardFree(g->board);
	g->isPlaying = false;
}


void initSnakes(Board *b, Snake *s1, Snake *s2)
{
		int i;
		for (i=0; i<snakeGetSize(s1); i++)
		{
				snakeUpdateElement(s1, snakeGetSize(s1) - i -1, boardGetWidth(b)/3-i, boardGetHeight(b)/2-1);
		}
		for (i=0; i<snakeGetSize(s2); i++)
		{
				snakeUpdateElement(s2, snakeGetSize(s2) - i -1, boardGetWidth(b)/3*2+i, boardGetHeight(b)/2);
		}
		updateSnake(b, s1);
		updateSnake(b, s2);
}

void updateSnake(Board *b, Snake *s)
{
		int i;
		for (i=0; i<snakeGetSize(s); i++)
		{
				boardSetValue(b, snakeGetPos(s, i)->x, snakeGetPos(s, i)->y, snakeGetId(s));
		}
}

bool moveSnake(Board *b, Snake *s)
{
		boardSetValue(b, snakeGetPos(s, 0)->x, snakeGetPos(s, 0)->y, 0);
		bool continueGame = checkMovement(s, b);
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1)->x, snakeGetPos(s, snakeGetSize(s)-1)->y, snakeGetId(s));
		return continueGame;
}

Coord nextPosCell(Snake *s)
{
		Coord res = snakeGetPos(s, snakeGetSize(s)-1);
		switch (snakeGetDirection(s))
		{
				case UP:
						res->y -= 1;
						break;

				case DOWN:
						res->y += 1;
						break;

				case LEFT:
						res->x -= 1;
						break;

				case RIGHT:
						res->x += 1;
						break;

				default:
					printf("Error isNextCellBorder\n");
					break;
		}
		return res;
}

static bool isNextCellOutOfRange(Board *b, Snake *s)
{
		bool res = false;
		if (nextPosCell(s)->x < 0 || nextPosCell(s)->y < 0 ||
		nextPosCell(s)->y > boardGetHeight(b)-1 || nextPosCell(s)->x > boardGetWidth(b)-1)
		{
				res = true;
		}
		return res;
}

bool isNextCellSnake(Board *b, Snake *s)
{
		bool res = false;
		if (!isNextCellOutOfRange(b, s) && (boardGetValue(b, nextPosCell(s)->x, nextPosCell(s)->y) == 1 || boardGetValue(b, nextPosCell(s)->x, nextPosCell(s)->y) == 2))
		{
			res = true;
		}
		return res;
}
//DOUBLE OUT OF RANGE
bool isNextCellBorder(Board *b, Snake *s)
{
		bool res = false;
		if ((snakeGetDirection(s) == UP || snakeGetDirection(s)== DOWN) &&
		(nextPosCell(s)->y<0 || nextPosCell(s)->y>boardGetHeight(b)-1))
		{
				res = true;
		}
		else if ((snakeGetDirection(s) == LEFT || snakeGetDirection(s) == RIGHT) &&
		(nextPosCell(s)->x<0 || nextPosCell(s)->x>boardGetWidth(b)-1))
		{
				res = true;
		}
		return res;
}

static bool checkMovement(Snake *s, Board *b) {
		bool canTp = false;
		bool continueGame = true;
		if (isNextCellSnake(b, s))
		{
				printf("Snake mort !\n");
				continueGame = false;
		}

		if (isNextCellBorder(b, s))
		{
				if (canTp)
				{
						switch (snakeGetDirection(s))
						{
								case UP:
										snakeTeleportation(s, snakeGetPos(s, snakeGetSize(s)-1)->y, boardGetWidth(b)-1);
										break;

								case DOWN:
										snakeTeleportation(s, snakeGetPos(s, snakeGetSize(s)-1)->y, 0);
										break;

								case LEFT:
										snakeTeleportation(s, boardGetHeight(b)-1, snakeGetPos(s, snakeGetSize(s)-1)->x);
										break;

								case RIGHT:
										snakeTeleportation(s, 0, snakeGetPos(s, snakeGetSize(s)-1)->x);
										break;

								default:
										printf("Error checkMovement\n");
										break;
						}
				} else {
							printf("Le snake s'est pris une bordure !\n");
							continueGame = false;
				}
			}
			else
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

		return continueGame;
}

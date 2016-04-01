#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "game.h"

static bool checkMovement(Snake *s, Board *b);
static bool isNextCellBorder(Board *b, Snake *s);

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

Game gameCreate() // à faire : 3 mode de jeu différent (tiny, normal, big)
{
		Game g = malloc(sizeof(struct Game));
		g->board = boardInit(M_SIZE_BOARD_X, M_SIZE_BOARD_Y, M_CELL_SIZE);
		g->snake1 = snakeCreate(10, 1);
		g->snake2 = snakeCreate(3, 2);
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
		g->isPlaying = false;
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

bool moveSnake(Board *b, Snake *s)
{
		boardSetValue(b, snakeGetPos(s, 0, Line), snakeGetPos(s, 0, Column), 0);
		bool continueGame = checkMovement(s, b);
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1, Line), snakeGetPos(s, snakeGetSize(s)-1, Column), snakeGetId(s));
		return continueGame;
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

static bool isNextCellOutOfRange(Board *b, Snake *s)
{
		bool res = false;
		if (nextPosCell(s, Line) < 0 || nextPosCell(s, Column) < 0 ||
		nextPosCell(s, Line) > boardGetSize(b, Line)-1 || nextPosCell(s, Column) > boardGetSize(b, Column)-1)
		{
				res = true;
		}
		return res;
}

static bool isNextCellDie(Board *b, Snake *s)
{
		bool res = false;
		if (!isNextCellOutOfRange(b, s) && boardGetValue(b, nextPosCell(s, Line), nextPosCell(s, Column)) == 1)
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

static bool checkMovement(Snake *s, Board *b) {
		bool canTp = false;
		bool continueGame = true;
		if (isNextCellDie(b, s))
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

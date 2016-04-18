#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "game.h"
#include "coord.h"

// Static function
static bool gameCheckMovement(Snake *s, Board *b);

/**
 * \struct Game
 * \brief The game structure
 * \details The structure contains a board, the two snakes and a boolean to know if the game is currently playing
 **/
struct Game
{
		Board *board; // le board
		Snake *snake1; // joueur 1
		Snake *snake2; // joueur 2
		bool isPlaying;
};

/**
 * \fn gameCreate
 * \brief The function creates the game
 * \details The function store the game in the memory and initialize the snakes
 * \param size BoardSize: the type of the board to init
 * \return Returns Game pointer to the crated game
 */
Game gameCreate(BoardSize size) 
{
		// TODO: 3 mode de jeu différent (tiny, normal, big)
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

		g->snake1 = snakeCreate(15, 1, RIGHT);
		g->snake2 = snakeCreate(15, 2, LEFT);
		g->isPlaying = true;

    	gameInitSnakes(g->board, g->snake1, g->snake2);

		return g;
}

/**
 * \fn gameGetBoard
 * \brief Accessor to the board of the game structure
 * \details The function returns the board of the game
 * \param g Game: The game to access
 * \return Returns Board pointer
 */
Board* gameGetBoard(Game g)
{
		return g->board;
}

/**
 * \fn gameGetSnake
 * \brief Accessor to the snake of the game structure
 * \details The function returns the snake of the game
 * \param g Game: The game to access
 * \param player Int: The player number
 * \return Returns Snake pointer
 */
Snake* gameGetSnake(Game g, int player)
{
		if (player == 1)
			return g->snake1;
		return g->snake2;
}

/**
 * \fn gameGetIsPlaying
 * \brief Accessor to the isPlaying boolean of the game structure
 * \details The function returns the isPlaying of the game
 * \param g Game: The game to access
 * \return Bool: Returns isPlaying
 */
bool gameGetIsPlaying(Game g)
{
		return g->isPlaying;
}

/**
 * \fn gameEnd
 * \brief End the game
 * \details The function put false to the isPlaying bool and free all structures
 * \param g Game: The game to end
 */
void gameEnd(Game g)
{
		boardFree(g->board);
		g->isPlaying = false;
}

/**
 * \fn gameInitSnakes
 * \brief Initialize the snakes of the game
 * \details The function put the snakes on the board at the beggining of the game
 * \param b Board: where to put the snakes on
 * \param s1 Snake: First snake to put on the board
 * \param s2 Snake: Second snake to put on the board
 */
void gameInitSnakes(Board *b, Snake *s1, Snake *s2)
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
		gameUpdateSnake(b, s1);
		gameUpdateSnake(b, s2);
}

/**
 * \fn gameUpdateSnake
 * \brief Update the board with the position of the snake 
 * \details The function iterates on Snake's Elements and put them on the board
 * \param b Board: where to update the snake
 * \param s Snake to put on the board
 */
void gameUpdateSnake(Board *b, Snake *s)
{
		int i;
		for (i=0; i<snakeGetSize(s); i++)
		{
				boardSetValue(b, snakeGetPos(s, i)->x, snakeGetPos(s, i)->y, snakeGetId(s));
		}
}

/**
 * \fn gameMoveSnake
 * \brief Update the board with the snake movement
 * \details Update the board without iterating on elements
 * \param b Board: where to move the snake
 * \param s Snake to move on the board
 */
bool gameMoveSnake(Board *b, Snake *s)
{
		boardSetValue(b, snakeGetPos(s, 0)->x, snakeGetPos(s, 0)->y, 0);
		bool continueGame = gameCheckMovement(s, b);
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1)->x, snakeGetPos(s, snakeGetSize(s)-1)->y, snakeGetId(s));
		return continueGame;
}

/**
 * \fn gameCheckMovement
 * \brief Check collisions
 * \details Check if the next cell doesn't contains a snake or isn't a border
 * \param b Board: where to check
 * \param s Snake to move 
 */
static bool gameCheckMovement(Snake *s, Board *b) {
		bool canTp = false;
		bool continueGame = true;
		if (boardIsNextCellSnake(b, snakeGetPos(s, snakeGetSize(s)-1)->x, snakeGetPos(s, snakeGetSize(s)-1)->y, snakeGetDirection(s)))
		{
				printf("Snake mort !\n");
				continueGame = false;
		}

		if (boardIsNextCellBorder(b, snakeGetPos(s, snakeGetSize(s)-1)->x, snakeGetPos(s, snakeGetSize(s)-1)->y, snakeGetDirection(s)))
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

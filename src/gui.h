#ifndef GUI_H
#define GUI_H

#include "board.h"
#include "snake.h"
#include "game.h"

typedef struct Timer *Timer;
struct Timer
{
	Uint32 start; // départ de la boucle de jeu
	Uint32 end; // fin de la boucle de jeu
	int delay; // temps à attendre à chaque tour
	int snake1MoveTimer; // le temps en ms depuis que le snake 1 a bougé
	int snake2MoveTimer;
	Uint32 snake1LastMove; // la dernière fois que le snake 1 a bougé
	Uint32 snake2LastMove;
};

typedef struct SnakeAssets *SnakeAssets;
struct SnakeAssets
{
	SDL_Surface **head;
	SDL_Surface **body;
	SDL_Surface **tail;
};

typedef struct Assets *Assets;
struct Assets
{
	SnakeAssets snakeBlue;
	SnakeAssets snakeRed;
	SnakeAssets snakeGreen;
	SDL_Surface *board;
};

void guiPlay(BoardSize size);
void freeAll(SDL_Surface **surfaces);
void guiDisplayBoard(SDL_Surface *screen, Board *board, SDL_Surface **surfaces);
Assets guiLoadGame();
SnakeAssets guiLoadSnake(SnakeType type);
void guiDrawGame(SDL_Surface *screen, Game game, Assets assets);
void guiDrawSnake(SDL_Surface *screen, Snake *snake, SnakeAssets snakeAssets);
SDL_Surface* guiCreateScreen(BoardSize size);
void guiApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void guiSnakeEvent(SDL_Event *event, Snake *s);
void guiGeneralEvent(SDL_Event *event, Game game);
void guiClearScreen(SDL_Surface *screen);
void guiReloadScreen(SDL_Surface *screen);
Timer guiCreateTimer();

Uint32 guiGetPixel32( SDL_Surface *surface, int x, int y );
void guiSetPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
SDL_Surface *flip_surface( SDL_Surface *surface, int flags );


#endif

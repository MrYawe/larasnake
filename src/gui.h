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

void guiPlay();
void freeAll(SDL_Surface **surfaces);
void guiDisplayBoard(SDL_Surface *screen, Board *board, SDL_Surface **surfaces);
void guiSnakeEvent(SDL_Event *event, Snake *s);
void guiGeneralEvent(SDL_Event *event, Game game);
void guiClearScreen(SDL_Surface *screen);
void guiReloadScreen(SDL_Surface *screen);


#endif

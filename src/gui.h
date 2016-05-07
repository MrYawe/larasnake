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
	SDL_Surface **corner;
	SDL_Surface **tail;
};

typedef struct Assets *Assets;
struct Assets
{
	SnakeAssets *snakesAssets;
	SDL_Surface *background;
	SDL_Surface **itemsAssets;
};

/**** General ****/
void guiPlay(BoardSize size);
Timer guiCreateTimer();

/**** Screen ****/
SDL_Surface* guiCreateScreen(BoardSize size);
void guiReloadScreen(SDL_Surface *screen);
void guiClearScreen(SDL_Surface *screen);

/**** Assets ****/
Assets guiLoadAssets();
SnakeAssets guiLoadSnake(SnakeType type, char* color);
SDL_Surface** guiLoadItems();
SDL_Surface* guiLoadImage(char* path);
void guiApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void guiFreeAssets(Assets assets);

/**** Draw ****/
void guiDrawGame(SDL_Surface *screen, Game game, Assets assets);
void guiDrawSnake(SDL_Surface *screen, Snake snake, SnakeAssets snakeAssets);
void guiDrawItems(SDL_Surface *screen, Item itemList, SDL_Surface** itemsAssets);

/**** Events ****/
void guiSnakeEvent(SDL_Event *event, Snake s);
void guiGeneralEvent(SDL_Event *event, Game game);


#endif

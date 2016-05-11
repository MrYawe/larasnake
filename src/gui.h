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
	int itemPopTimer;
	Uint32 snake1LastMove; // la dernière fois que le snake 1 a bougé
	Uint32 snake2LastMove;
	Uint32 itemLastPop;
};

typedef struct GuiAssets *GuiAssets;
struct GuiAssets
{
	SDL_Surface *pauseScreen;
	SDL_Surface *timer3;
	SDL_Surface *timer2;
	SDL_Surface *timer1;
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
	GuiAssets guiAssets;
	SDL_Surface *background;
	int currentBg;
	SDL_Surface **itemsAssets;
};

typedef struct Title *Title;
struct Title
{
	int x, y;
	MenuValue value;
	char* text;
	SDL_Color color;
	TTF_Font *font;
	SDL_Surface *surface;
	bool isSelected;
};

/**** General ****/
void guiPlay(BoardSize size);
Timer guiCreateTimer();
void guiPause(Game g);

/**** Screen ****/
SDL_Surface* guiCreateScreen(BoardSize size);
void guiReloadScreen(SDL_Surface *screen);
void guiClearScreen(SDL_Surface *screen);
void guiChangeBackground(SDL_Surface* screen, Assets assets, BoardSize size);

/**** Assets ****/
Assets guiLoadAssets(BoardSize size);
SnakeAssets guiLoadSnake(SnakeType type, char* color);
GuiAssets guiLoadGui(BoardSize size);
SDL_Surface** guiLoadItems();
SDL_Surface* guiLoadImage(char* path);
void guiApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void guiFreeAssets(Assets assets);

/**** Draw ****/
void guiDrawGame(SDL_Surface *screen, Game game, Assets assets);
void guiDrawSnake(SDL_Surface *screen, Snake snake, SnakeAssets snakeAssets);
void guiDrawItems(SDL_Surface *screen, Item itemList, SDL_Surface** itemsAssets);
void guiDrawGui(SDL_Surface *screen, Game game, GuiAssets guiAssets);

/**** Events ****/
void guiEvent(SDL_Event *event, Snake s, Game g);
void guiGeneralEvent(SDL_Event *event, Game game);

/*** Menu ***/
Title guiCreateTitle(int x, int y, MenuValue value, char* text, SDL_Color color, TTF_Font* font);
void guiSetSelectedTitle(Title *titles, int nbTitles, int state);
Title guiGetSelectedItem(Title *titles, int nbTitles);
void guiDrawTitles(SDL_Surface *screen, Title *titles, int nbTitles, SDL_Color ifSelectedColor);


#endif

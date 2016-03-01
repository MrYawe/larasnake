#ifndef GUI_H
#define GUI_H

void guiDisplayBoard(SDL_Surface *screen, Board *board, SDL_Surface **surfaces);
bool guiEvent(SDL_Event *event, Snake *s1);
void guiClearScreen(SDL_Surface *screen);
void guiReloadScreen(SDL_Surface *screen);


#endif
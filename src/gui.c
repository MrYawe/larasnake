#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constants.h"
#include "game.h"

void guiDisplayBoard(SDL_Surface *screen, Board *board, SDL_Surface **surfaces) {
    int x, y;
    SDL_Rect cellPosition;
    cellPosition.x = 0;
    cellPosition.y = 0;
    //printf("Taille line: %d\n", boardGetSize(board, Line));
    //printf("Taille column: %d\n", boardGetSize(board, Column));

    for(y=0; y<boardGetSize(board, Column); y++) {
        for (x=0; x<boardGetSize(board, Line); x++) {
            if(boardGetValue(board, x, y)==0) {
                if(SDL_BlitSurface(surfaces[0], NULL, screen, &cellPosition)<0)
                    printf("%s\n", SDL_GetError());
            }
            cellPosition.x+=CELL_SIZE;
        }
        cellPosition.x=0;
        cellPosition.y+=CELL_SIZE;
    }
}

void guiClearScreen(SDL_Surface *screen) {
    if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255))<0)
        printf("%s\n", SDL_GetError());
}

void guiReloadScreen(SDL_Surface *screen) {
    SDL_Flip(screen);
}

bool guiEvent(SDL_Event *event, Snake *s1) {
    bool continuer = true;
    SDL_PollEvent(event);
    switch(event->type) {
        case SDL_QUIT:
            continuer = false;
            break;

        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
                case SDLK_UP: // Flèche haut 1
                    snakeSetDirection(s1, UP);
                    break;
                case SDLK_DOWN: // Flèche bas 2
                    snakeSetDirection(s1, DOWN);
                    break;
                case SDLK_RIGHT: // Flèche droite 3
                    snakeSetDirection(s1, RIGHT);
                    break;
                case SDLK_LEFT: // Flèche gauche 4
                    snakeSetDirection(s1, LEFT);
                    break;
                default:
                    break;
            }
            break;
    }

    return continuer;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "board.h"
#include "snake.h"
#include "gui.h"
#include "constants.h"
#include "game.h"

// Pour tester:  gcc -o prog main.c `sdl-config --cflags --libs` -lSDL_image
SDL_Surface *screen;
SDL_Surface **surfaces;
SDL_Event event;
int sizeBoardX, sizeBoardY;
int cellSize;
int blankX, blankY;
bool continuer;
//int frameRate = 60;
int frameMs = 1000 / 20; //calculate the length of each frame
Board* board;
Snake *s1;
Snake *s2;
Uint32 lastMove=0;
Uint32 startMs;
Uint32 endMs;
Uint32 delayMs;
Uint32 moveTime = 200;
Uint32 moveTimer = 0;

void init() {
    sizeBoardY=20;
    sizeBoardX=20;
    cellSize=21;
    blankX=0;
    blankY=0;
    continuer = true;
    surfaces = malloc(2*sizeof(SDL_Surface*));
    board = boardInit(sizeBoardX, sizeBoardY);
    s1 = snakeCreate(30, 1);
    s2 = snakeCreate(3, 2);
    initSnakes(board, s1, s2);

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    if(!(surfaces[0]=IMG_Load("./images/cube.bmp")))
        printf("%s\n", IMG_GetError());
}

void freeAll() {
    SDL_FreeSurface(surfaces[0]);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    init();

    while (continuer) {
        startMs = SDL_GetTicks(); //when the frame starts
        guiClearScreen(screen);
        continuer = guiEvent(&event, s1); // intercepte un evenement si il a lieu
        
        // Deplacement cube
        moveTimer += SDL_GetTicks() - lastMove;   
        if (moveTimer >= moveTime) {
            moveSnake(board, s1);
            moveTimer = 0 ;
        }
        lastMove = SDL_GetTicks();

        guiDisplayBoard(screen, board, surfaces);
        guiReloadScreen(screen);

        // Gestion FPS
        endMs = SDL_GetTicks(); //when the frame calculations end
        delayMs = frameMs - (endMs - startMs); //how long to delay
        SDL_Delay(delayMs); //delay processing
    }

    freeAll();

    return EXIT_SUCCESS;
}




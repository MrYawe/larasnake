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

SDL_Surface *screen; // La surface finale qui sera affiché à l'écran
SDL_Surface **surfaces; // Un tableu de SDL_Surface avec toutes les surfaces (images) des éléments du jeu
SDL_Event event; // Permet de capturer les évènements clavier/souris

int sizeBoardX, sizeBoardY; // Taile du board en x et y
int cellSize; // Taille d'une case (un carré)
bool continuer; // Tant que true le jeu continue
//int frameRate = 60;
int frameMs = 30; // Temps en milliseconde par frame. 30ms ~= 30 FPS
Board* board;
Snake *s1;
Snake *s2;
Uint32 lastMove=0;
Uint32 startMs;
Uint32 endMs;
int delayMs;
Uint32 moveTime = 100;
Uint32 moveTimer = 0;

void init() {
    sizeBoardX=35;
    sizeBoardY=25;
    cellSize=21;
    continuer = true;
    surfaces = malloc(2*sizeof(SDL_Surface*));
    board = boardInit(sizeBoardX, sizeBoardY);
    s1 = snakeCreate(5, 1);
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
    init(sizeBoardX, sizeBoardY);

    while (continuer) {
        printf("(1) Debut\n");
        startMs = SDL_GetTicks(); //when the frame starts
        printf("(2) Clear\n");
        guiClearScreen(screen);
        printf("(3) Event\n");

        // Deplacement cube
        moveTimer += SDL_GetTicks() - lastMove;
        printf("(4) Move snake\n");
        if (moveTimer >= moveTime) {
            continuer = guiEvent(&event, s1); // intercepte un evenement si il a lieu
            moveSnake(board, s1);
            moveTimer = 0 ;
        }
        lastMove = SDL_GetTicks();

        printf("(5) Display board\n");
        guiDisplayBoard(screen, board, surfaces);
        printf("(6) Reload screen\n");
        guiReloadScreen(screen);

        // Gestion FPS
        endMs = SDL_GetTicks(); //when the frame calculations end
        printf("Temps: %d\n", endMs - startMs);
        delayMs = frameMs - (endMs - startMs); //how long to delay
        printf("Temps d'attente: %d\n", delayMs);
        if(delayMs <= 0) {
            printf("ON A EU CHAUUUUUD !!\n");
        } else {
            SDL_Delay(delayMs); //delay processing
        }
        printf("(7) Fin\n");
    }

    freeAll();
    return EXIT_SUCCESS;
}

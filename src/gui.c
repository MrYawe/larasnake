#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gui.h"
#include "constants.h"
#include "game.h"
#include "ia.h"

void guiPlay()
{
    SDL_Event event; // Permet de capturer les évènements clavier/souris
    //SDL_Event event2;
    SDL_Surface **surfaces = malloc(2*sizeof(SDL_Surface*));
    Timer timer = malloc(sizeof(Timer*));
    timer->snake1MoveTimer = 0;
    bool continueGameMove = true;

    SDL_Init(SDL_INIT_VIDEO);
    // La surface finale qui sera affiché à l'écran
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    if(!(surfaces[0]=IMG_Load("./images/cube.bmp")))
        printf("%s\n", IMG_GetError());

    Game game = gameCreate();

    while (gameGetIsPlaying(game)) {

        //printf("(1) Debut\n");
        timer->start = SDL_GetTicks(); //when the frame starts
        //printf("(2) Clear\n");
        guiClearScreen(screen);
        //printf("(3) Event\n");

        // Deplacement snake 1
        //printf("(4) Move snake 1\n");
        timer->snake1MoveTimer += SDL_GetTicks() - timer->snake1LastMove;
        if (timer->snake1MoveTimer >= snakeGetSpeed(gameGetSnake(game, 1))) {
            iaSurvive(gameGetBoard(game), gameGetSnake(game, 1));
            guiSnakeEvent(&event, gameGetSnake(game, 1)); // intercepte un evenement si il a lieu
            continueGameMove = moveSnake(gameGetBoard(game), gameGetSnake(game, 1));
            timer->snake1MoveTimer = 0 ;
            //snakeSetSpeed(gameGetSnake(game, 1), snakeGetSpeed(gameGetSnake(game, 1))-1); // fun test
        }
        timer->snake1LastMove = SDL_GetTicks();

        //guiGeneralEvent(&event2, game);

        //printf("(5) Display board\n");
        guiDisplayBoard(screen, gameGetBoard(game), surfaces);
        //printf("(6) Reload screen\n");
        guiReloadScreen(screen);

        // Gestion FPS
        timer->end = SDL_GetTicks(); //when the frame calculations end
        //printf("Temps: %d\n", endMs - startMs);
        timer->delay = FRAME_MS - (timer->end - timer->start); //how long to delay
        //printf("Temps d'attente: %d\n", delayMs);
        if(timer->delay <= 0) {
            //printf("ON A EU CHAUUUUUD !!\n");
        } else {
            SDL_Delay(timer->delay); //delay processing
        }

        if(!continueGameMove)
            gameEnd(game);
        //printf("(7) Fin\n");
    }

    freeAll(surfaces);
}

void freeAll(SDL_Surface **surfaces) {
    SDL_FreeSurface(surfaces[0]);
    SDL_Quit();
}

void guiDisplayBoard(SDL_Surface *screen, Board *board, SDL_Surface **surfaces) {
    int x, y;
    SDL_Rect cellPosition;
    cellPosition.x = 0;
    cellPosition.y = 0;
    //printf("Taille line: %d\n", boardGetSize(board, Line));
    //printf("Taille column: %d\n", boardGetSize(board, Column));

    for(y=0; y<boardGetHeight(board); y++) {
        for (x=0; x<boardGetWidth(board); x++) {
            if(boardGetValue(board, x, y)==0) {
                if(SDL_BlitSurface(surfaces[0], NULL, screen, &cellPosition)<0)
                    printf("%s\n", SDL_GetError());
            }
            cellPosition.x+=N_CELL_SIZE;
        }
        cellPosition.x=0;
        cellPosition.y+=N_CELL_SIZE;
    }
}

void guiClearScreen(SDL_Surface *screen) {
    if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255))<0)
        printf("%s\n", SDL_GetError());
}

void guiReloadScreen(SDL_Surface *screen) {
    SDL_Flip(screen);
}

void guiSnakeEvent(SDL_Event *event, Snake *s) {
    while (SDL_PollEvent(event)) {
        switch(event->type) {

            case SDL_KEYDOWN:
                switch(event->key.keysym.sym) {
                    case SDLK_UP: // Flèche haut 1
                        snakeSetDirection(s, UP);
                        break;
                    case SDLK_DOWN: // Flèche bas 2
                        snakeSetDirection(s, DOWN);
                        break;
                    case SDLK_RIGHT: // Flèche droite 3
                        snakeSetDirection(s, RIGHT);
                        break;
                    case SDLK_LEFT: // Flèche gauche 4
                        snakeSetDirection(s, LEFT);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void guiGeneralEvent(SDL_Event *event, Game game) {
    while (SDL_PollEvent(event)) {

        switch(event->type) {

            case SDL_QUIT:
                printf("game quit\n");
                gameEnd(game);
                break;
        }
    }
}

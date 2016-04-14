#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include "gui.h"
#include "constants.h"
#include "game.h"
#include "ia.h"

//Flip flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

void guiPlay(BoardSize size)
{
    SDL_Event event; // Permet de capturer les évènements clavier/souris
    //SDL_Event event2;
    SDL_Surface **surfaces = malloc(2*sizeof(SDL_Surface*));

    SDL_Init(SDL_INIT_VIDEO);

    Timer timer = guiCreateTimer();
    /*timer->snake1LastMove = 0;
    timer->snake2LastMove = 0;*/ // bug à corriger

    bool continueGameMove1 = true;
    bool continueGameMove2 = true;

    // La surface finale qui sera affiché à l'écran
    SDL_Surface *screen = guiCreateScreen(size);
    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    if(!(surfaces[0]=IMG_Load("./images/snake/blue/snake-blue-body.png")))
        printf("%s\n", IMG_GetError());

    if(!(surfaces[1]=IMG_Load("./images/background/bg-medium.png")))
        printf("%s\n", IMG_GetError());


    SDL_Surface *background;
    if(!(background=IMG_Load("./images/background/bg-medium.png")))
        printf("%s\n", IMG_GetError());

    Game game = gameCreate(size);
    /*Snake* snake1 = gameGetSnake(game , 1);
    Snake* snake2 = gameGetSnake(game , 2);*/

    while (gameGetIsPlaying(game)) {
        printf("(1) Debut\n");

        timer->start = SDL_GetTicks(); //when the frame starts

        // Deplacement snake 1 (joueur)
        timer->snake1MoveTimer += SDL_GetTicks() - timer->snake1LastMove;
        if (timer->snake1MoveTimer >= snakeGetSpeed(gameGetSnake(game, 1))) {
            guiSnakeEvent(&event, gameGetSnake(game, 1)); // intercepte un evenement si il a lieu
            continueGameMove1 = moveSnake(gameGetBoard(game), gameGetSnake(game, 1));
            timer->snake1MoveTimer = 0 ;
            //snakeSetSpeed(gameGetSnake(game, 1), snakeGetSpeed(gameGetSnake(game, 1))-1); // fun test
        }
        timer->snake1LastMove = SDL_GetTicks();
        // Fin Deplacement snake 1

        // Deplacement snake 2 (IA)
        timer->snake2MoveTimer += SDL_GetTicks() - timer->snake2LastMove;
        if (timer->snake2MoveTimer >= snakeGetSpeed(gameGetSnake(game, 2))) {
            snakeSetDirection(gameGetSnake(game, 2), iaSurvive(gameGetBoard(game), gameGetSnake(game, 2)));
            continueGameMove2 = moveSnake(gameGetBoard(game), gameGetSnake(game, 2));
            timer->snake2MoveTimer = 0 ;
            //snakeSetSpeed(gameGetSnake(game, 2), snakeGetSpeed(gameGetSnake(game, 2))-1); // fun test
        }
        timer->snake2LastMove = SDL_GetTicks();
        // Fin Deplacement snake 2

        SDL_Rect cellPosition;
        cellPosition.x = 0;
        cellPosition.y = 0;
        if(SDL_BlitSurface(background, NULL, screen, &cellPosition)<0)
            printf("%s\n", SDL_GetError());

        guiDrawGame(screen, game, surfaces);
        //boardDisplay(gameGetBoard(game));
        //printf("(5) Display board\n");
        //guiDisplayBoard(screen, gameGetBoard(game), surfaces);



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


        if(!continueGameMove1 || !continueGameMove2)
            gameEnd(game);
        //printf("(7) Fin\n");
    }

    //freeAll(surfaces);
}

void freeAll(SDL_Surface **surfaces) {
    SDL_FreeSurface(surfaces[0]);
    SDL_Quit();
}

SDL_Surface* guiCreateScreen(BoardSize size) {
    SDL_Surface* screen;
    switch (size) {
        case SMALL:
            screen = SDL_SetVideoMode(S_SIZE_BOARD_X*S_CELL_SIZE, S_SIZE_BOARD_Y*S_CELL_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
            break;

        case MEDIUM:
            screen = SDL_SetVideoMode(M_SIZE_BOARD_X*M_CELL_SIZE, M_SIZE_BOARD_Y*M_CELL_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
            break;

        case LARGE:
            screen = SDL_SetVideoMode(L_SIZE_BOARD_X*L_CELL_SIZE, L_SIZE_BOARD_Y*L_CELL_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
            break;
    }

    return screen;
}

void guiDrawGame(SDL_Surface *screen, Game game, SDL_Surface **surfaces) {
    guiDrawSnake(screen, gameGetSnake(game, 1), surfaces);
    guiDrawSnake(screen, gameGetSnake(game, 2), surfaces);
}

void guiDrawSnake(SDL_Surface *screen, Snake *snake, SDL_Surface **surfaces) {
    int i;
    SDL_Rect cellPosition;
    SDL_Surface *rotation = rotozoomSurface(surfaces[0], 90, 1.0, 1); //On transforme la surface image.;

    for (i=0; i<snakeGetSize(snake); i++) {
        cellPosition.x = snakeGetPos(snake, i)->x * M_CELL_SIZE;
        cellPosition.y = snakeGetPos(snake, i)->y * M_CELL_SIZE;

        if(i == 0) {

        } else if (i == snakeGetSize(snake)-1) {

        } else {
            if(SDL_BlitSurface(rotation, NULL, screen, &cellPosition)<0)
                printf("%s\n", SDL_GetError());
        }
    }
}

void guiApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    if(SDL_BlitSurface(source, clip, destination, &offset) < 0)
        printf("%s\n", SDL_GetError());
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
            if(boardGetValue(board, x, y)==1) {
                if(SDL_BlitSurface(surfaces[0], NULL, screen, &cellPosition)<0)
                    printf("%s\n", SDL_GetError());
            }
            cellPosition.x+=M_CELL_SIZE;
        }
        cellPosition.x=0;
        cellPosition.y+=M_CELL_SIZE;
    }
}

Timer guiCreateTimer() {
    Timer timer = malloc(sizeof(Timer*));
    timer->snake1MoveTimer = 0;
    timer->snake2MoveTimer = 0;

    //timer->snake1LastMove = 0;
    //timer->snake2LastMove = 0;
    printf("%d\n", timer->snake1LastMove);
    printf("%d\n", timer->snake2LastMove);

    return timer;
}

void guiClearScreen(SDL_Surface *screen) {
    if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255))<0)
        printf("%s\n", SDL_GetError());
}

void guiReloadScreen(SDL_Surface *screen) {
    SDL_Flip(screen);
}

void guiSnakeEvent(SDL_Event *event, Snake *s) {
    bool moved = false;
    while (SDL_PollEvent(event)) {
        switch(event->type) {

            case SDL_KEYDOWN:
                if (!moved) {
                    switch(event->key.keysym.sym) {
                        case SDLK_UP: // Flèche haut 1
                            snakeSetDirection(s, UP);
                            moved = true;
                            break;
                        case SDLK_DOWN: // Flèche bas 2
                            snakeSetDirection(s, DOWN);
                            moved = true;
                            break;
                        case SDLK_RIGHT: // Flèche droite 3
                            snakeSetDirection(s, RIGHT);
                            moved = true;
                            break;
                        case SDLK_LEFT: // Flèche gauche 4
                            snakeSetDirection(s, LEFT);
                            moved = true;
                            break;
                        default:
                            break;
                    }
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
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

    Assets assets = guiLoadGame();

    SDL_Init(SDL_INIT_VIDEO);

    Timer timer = guiCreateTimer();

    srand(time(NULL));

    bool continueGameMove1 = true;
    bool continueGameMove2 = true;

    // La surface finale qui sera affiché à l'écran
    SDL_Surface *screen = guiCreateScreen(size);
    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    if(!(surfaces[1]=IMG_Load("./images/background/bg-medium.png")))
        printf("%s\n", IMG_GetError());


    SDL_Surface *background;
    if(!(background=IMG_Load("./images/background/bg-medium.png")))
        printf("%s\n", IMG_GetError());

    Game game = gameCreate(size);
    /*Snake* snake1 = gameGetSnake(game , 1);
    Snake* snake2 = gameGetSnake(game , 2);*/
    
    boardFeed(gameGetBoard(game));
    

    while (gameGetIsPlaying(game)) {

        timer->start = SDL_GetTicks(); //when the frame starts
        // Deplacement snake 1 (joueur)
        timer->snake1MoveTimer += SDL_GetTicks() - timer->snake1LastMove;
        if (timer->snake1MoveTimer >= snakeGetSpeed(gameGetSnake(game, 1))) {
            guiSnakeEvent(&event, gameGetSnake(game, 1)); // intercepte un evenement si il a lieu
            continueGameMove1 = moveSnake(gameGetBoard(game), gameGetSnake(game, 1));
            timer->snake1MoveTimer = 0;
            //snakeSetSpeed(gameGetSnake(game, 1), snakeGetSpeed(gameGetSnake(game, 1))-1); // fun test
        }
        timer->snake1LastMove = SDL_GetTicks();
        // Fin Deplacement snake 1

        // Deplacement snake 2 (IA)
        timer->snake2MoveTimer += SDL_GetTicks() - timer->snake2LastMove;
        if (timer->snake2MoveTimer >= snakeGetSpeed(gameGetSnake(game, 2))) {
            snakeSetDirection(gameGetSnake(game, 2), iaJambon(gameGetBoard(game), gameGetSnake(game, 2)));
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

        guiDrawGame(screen, game, assets);
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

Assets guiLoadGame() {
    Assets assets = malloc(sizeof(struct Assets));
    assets->snakeBlue = guiLoadSnake(WATER);

    return assets;
}

SnakeAssets guiLoadSnake(SnakeType type) {
    SnakeAssets snakeAssets = malloc(sizeof(struct SnakeAssets));
    snakeAssets->head = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->body = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->tail = malloc(4*sizeof(SDL_Surface*));
    //char *color = malloc(50*sizeof(char));
    SDL_Surface *head;
    SDL_Surface *body;
    SDL_Surface *tail;

    switch (type) {
        case WATER:
            if(!(head=IMG_Load("./images/snake/blue/snake-head.png")))
                printf("%s\n", IMG_GetError());
            if(!(body=IMG_Load("./images/snake/blue/snake-body.png")))
                printf("%s\n", IMG_GetError());
            if(!(tail=IMG_Load("./images/snake/blue/snake-tail.png")))
                printf("%s\n", IMG_GetError());
            break;
    }

    snakeAssets->head[RIGHT]=head;
    snakeAssets->head[UP]=rotozoomSurface(head, 90, 1.0, 1);
    snakeAssets->head[LEFT]=rotozoomSurface(head, 180, 1.0, 1);
    snakeAssets->head[DOWN]=rotozoomSurface(head, 270, 1.0, 1);

    snakeAssets->body[RIGHT]=body;
    snakeAssets->body[DOWN]=rotozoomSurface(body, 90, 1.0, 1);
    snakeAssets->body[LEFT]=rotozoomSurface(body, 180, 1.0, 1);
    snakeAssets->body[UP]=rotozoomSurface(body, 270, 1.0, 1);

    snakeAssets->tail[LEFT]=tail;
    snakeAssets->tail[DOWN]=rotozoomSurface(tail, 90, 1.0, 1);
    snakeAssets->tail[RIGHT]=rotozoomSurface(tail, 180, 1.0, 1);
    snakeAssets->tail[UP]=rotozoomSurface(tail, 270, 1.0, 1);

    return snakeAssets;
}

void guiDrawGame(SDL_Surface *screen, Game game, Assets assets) {
    guiDrawSnake(screen, gameGetSnake(game, 1), assets->snakeBlue);
    guiDrawSnake(screen, gameGetSnake(game, 2), assets->snakeBlue);
    guiApplySurface(boardGetJambon(gameGetBoard(game))->x*M_CELL_SIZE, M_CELL_SIZE*boardGetJambon(gameGetBoard(game))->y, IMG_Load("./images/cube.bmp"), screen, NULL);
}

void guiDrawSnake(SDL_Surface *screen, Snake *snake, SnakeAssets snakeAssets) {
    int i;
    int x, y;

    for (i=0; i<snakeGetSize(snake); i++) {
        x = snakeGetPos(snake, i)->x * M_CELL_SIZE;
        y = snakeGetPos(snake, i)->y * M_CELL_SIZE;

        Direction d = snakeElementGetOrientation(snake, i);

        if(i == 0) { // tail
            guiApplySurface(x, y, snakeAssets->tail[d], screen, NULL);
        } else if (i == snakeGetSize(snake)-1) { // head
            guiApplySurface(x, y, snakeAssets->head[d], screen, NULL);
        } else {
            guiApplySurface(x, y, snakeAssets->body[d], screen, NULL);
        }
    }
}

void guiApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
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
    Timer timer = malloc(sizeof(struct Timer));
    timer->snake1MoveTimer = SNAKE_DEFAULT_SPEED; // pour être certain que les deux snake bouge des le début
    timer->snake2MoveTimer = SNAKE_DEFAULT_SPEED;

    timer->snake1LastMove = 0;
    timer->snake2LastMove = 0;

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

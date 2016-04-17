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
	  /*******************/
	 /**   VARIABLES   **/
	/*******************/

	/***** SDL Variables *****/
    SDL_Event event;	//Variable to capture mouse/keyboard events
    SDL_Surface* screen;//Buffer that will contain the pixels to render on the screen

    /***** General Variables *****/
	Assets assets;	//Variable that will contain all the assets used in the game
    Timer timer;	//Variable used to control the actions based on the time

    /***** Structure Variables *****/
    bool continueGameMove1;	//Variable used to check if the snake 1 is dead
    bool continueGameMove2;	//Variable used to check if the snake 2 is dead
    
    Game game;		//Variable to access the game
    Board* board;	//Variable to access the board
    Snake* snake1;	//Variable to access the first snake
    Snake* snake2;	//Variable to access the first snake

	  /************************/
	 /**   INITIALIZATION   **/
	/************************/

	/***** SDL Initialization *****/
    SDL_Init(SDL_INIT_VIDEO);				//Initialization of the SDL Library
    SDL_WM_SetCaption("Larasnake", NULL);	//Set the title and icon name of the displayed window
    screen = guiCreateScreen(size);

	/***** General Variables *****/
	srand(time(NULL));	//Initialization of the random function
    timer = guiCreateTimer();
    assets = guiLoadAssets();

    /***** Structure Variables *****/
    continueGameMove1 = true;
    continueGameMove2 = true;

    game = gameCreate(size);            
    board = gameGetBoard(game);
    snake1 = gameGetSnake(game, 1);
    snake2 = gameGetSnake(game, 2);

    boardFeed(gameGetBoard(game));	//Function called to feed the snakes with ham

   	  /************************/
	 /**	  GAME LOOP		**/
	/************************/
    while (gameGetIsPlaying(game)) {

        timer->start = SDL_GetTicks(); // Debut de la frame courante

        /***** Deplacement du snake 1 (joueur) *****/
        timer->snake1MoveTimer += SDL_GetTicks() - timer->snake1LastMove;
        if (timer->snake1MoveTimer >= snakeGetSpeed(snake1)) {
            guiSnakeEvent(&event, snake1);                      // intercepte un evenement si il a lieu
            continueGameMove1 = gameMoveSnake(board, snake1);       //
            timer->snake1MoveTimer = 0;                         //
        }
        timer->snake1LastMove = SDL_GetTicks();
        /******************************************/

        /***** Deplacement snake 2 (IA) *****/
        timer->snake2MoveTimer += SDL_GetTicks() - timer->snake2LastMove;
        if (timer->snake2MoveTimer >= snakeGetSpeed(snake2)) {
            snakeSetDirection(snake2, iaJambon(board, snake2)); //
            continueGameMove2 = gameMoveSnake(board, snake2);       //
            timer->snake2MoveTimer = 0 ;                        //
        }
        timer->snake2LastMove = SDL_GetTicks();
        /***********************************/

        guiDrawGame(screen, game, assets);  //
        guiReloadScreen(screen);            //

        if(!continueGameMove1 || !continueGameMove2)        
            gameEnd(game);

        /***** Gestion des FPS *****/
        timer->end = SDL_GetTicks();                           //Get the time after the calculations
        timer->delay = FRAME_MS - (timer->end - timer->start); //Calculate how long to delay should be
        if(timer->delay > 0) {
            SDL_Delay(timer->delay);                           //Delay processing
        }
    }

    //freeAll(game);
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

SDL_Surface* guiLoadImage(char* path) {
    SDL_Surface *s;
    if(!(s = IMG_Load(path)))
        printf("%s\n", IMG_GetError());

    return s;
}

Assets guiLoadAssets() {
    Assets assets = malloc(sizeof(struct Assets));
    assets->background = guiLoadImage("./images/background/bg-medium.png");
    assets->snakeBlue = guiLoadSnake(WATER);
    return assets;
}

void guiFreeAssets(Assets assets) {
    free(assets->background);
    free(assets->snakeBlue);
    free(assets);
}

SnakeAssets guiLoadSnake(SnakeType type) {
    SnakeAssets snakeAssets = malloc(sizeof(struct SnakeAssets));
    snakeAssets->head = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->body = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->corner = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->tail = malloc(4*sizeof(SDL_Surface*));
    //char *color = malloc(50*sizeof(char));
    SDL_Surface *head;
    SDL_Surface *body;
    SDL_Surface *corner;
    SDL_Surface *tail;

    switch (type) {
        case WATER:
            head=guiLoadImage("./images/snake/blue/snake-head.png");
            body=guiLoadImage("./images/snake/blue/snake-body.png");
            corner=guiLoadImage("./images/snake/blue/snake-corner.png");
            tail=guiLoadImage("./images/snake/blue/snake-tail.png");
            break;
    }

    snakeAssets->head[RIGHT]=head;
    snakeAssets->head[UP]=rotozoomSurface(head, 90, 1.0, 1);
    snakeAssets->head[LEFT]=rotozoomSurface(head, 180, 1.0, 1);
    snakeAssets->head[DOWN]=rotozoomSurface(head, 270, 1.0, 1);

    snakeAssets->body[RIGHT]=body;
    snakeAssets->body[LEFT]=body;
    snakeAssets->body[DOWN]=rotozoomSurface(body, 90, 1.0, 1);
    snakeAssets->body[UP]=rotozoomSurface(body, 90, 1.0, 1);

    snakeAssets->corner[RIGHT]=corner;
    snakeAssets->corner[UP]=rotozoomSurface(corner, 90, 1.0, 1);
    snakeAssets->corner[LEFT]=rotozoomSurface(corner, 180, 1.0, 1);
    snakeAssets->corner[DOWN]=rotozoomSurface(corner, 270, 1.0, 1);

    snakeAssets->tail[LEFT]=tail;
    snakeAssets->tail[DOWN]=rotozoomSurface(tail, 90, 1.0, 1);
    snakeAssets->tail[RIGHT]=rotozoomSurface(tail, 180, 1.0, 1);
    snakeAssets->tail[UP]=rotozoomSurface(tail, 270, 1.0, 1);

    return snakeAssets;
}

void guiDrawGame(SDL_Surface *screen, Game game, Assets assets) {
    guiApplySurface(0, 0, assets->background, screen, NULL); // dessine le background
    guiDrawSnake(screen, gameGetSnake(game, 1), assets->snakeBlue);
    guiDrawSnake(screen, gameGetSnake(game, 2), assets->snakeBlue);
    guiApplySurface(boardGetJambon(gameGetBoard(game))->x*M_CELL_SIZE, M_CELL_SIZE*boardGetJambon(gameGetBoard(game))->y, IMG_Load("./images/cube.bmp"), screen, NULL);
}

void guiDrawSnake(SDL_Surface *screen, Snake *snake, SnakeAssets snakeAssets) {
    int i;
    int x, y;
    Direction currentDirection;
    Direction nextDirection;

    for (i=0; i<snakeGetSize(snake); i++) {
        x = snakeGetPos(snake, i)->x * M_CELL_SIZE;
        y = snakeGetPos(snake, i)->y * M_CELL_SIZE;

        currentDirection = snakeElementGetOrientation(snake, i);

        if(i == 0) { // tail
            guiApplySurface(x, y, snakeAssets->tail[currentDirection], screen, NULL);
        } else if (i == snakeGetSize(snake)-1) { // head
            guiApplySurface(x, y, snakeAssets->head[currentDirection], screen, NULL);
        } else {
            nextDirection = snakeElementGetOrientation(snake, i+1);
            if(currentDirection==RIGHT && nextDirection==UP) {
                guiApplySurface(x, y, snakeAssets->corner[LEFT], screen, NULL);
            } else if(currentDirection==RIGHT && nextDirection==DOWN) {
                guiApplySurface(x, y, snakeAssets->corner[DOWN], screen, NULL);
            } else if(currentDirection==UP && nextDirection==RIGHT) {
                guiApplySurface(x, y, snakeAssets->corner[RIGHT], screen, NULL);
            } else if(currentDirection==UP && nextDirection==LEFT) {
                guiApplySurface(x, y, snakeAssets->corner[DOWN], screen, NULL);
            } else if(currentDirection==DOWN && nextDirection==RIGHT) {
                guiApplySurface(x, y, snakeAssets->corner[UP], screen, NULL);
            } else if(currentDirection==DOWN && nextDirection==LEFT) {
                guiApplySurface(x, y, snakeAssets->corner[LEFT], screen, NULL);
            } else if(currentDirection==LEFT && nextDirection==UP) {
                guiApplySurface(x, y, snakeAssets->corner[UP], screen, NULL);
            } else if(currentDirection==LEFT && nextDirection==DOWN) {
                guiApplySurface(x, y, snakeAssets->corner[RIGHT], screen, NULL);
            } else {
                guiApplySurface(x, y, snakeAssets->body[currentDirection], screen, NULL);
            }
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

Timer guiCreateTimer() {
    Timer timer = malloc(sizeof(struct Timer));
    timer->snake1MoveTimer = SNAKE_DEFAULT_SPEED; // pour être certain que les deux snake bouge des le début
    timer->snake2MoveTimer = SNAKE_DEFAULT_SPEED;

    timer->snake1LastMove = 0;
    timer->snake2LastMove = 0;

    return timer;
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

/**
 * \file gui.c
 * \author groupe Larakis
 * \version 1
 * \date 19/04/2016
 * \brief Everything about the gui class
 * \details Contains all functions to manage the gui and interract with the user
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gui.h"
#include "constants.h"
#include "game.h"
#include "ia.h"

/**
 * \fn guiPlay(BoardSize size)
 * \brief This function is the main game loop
 * \details Function that create a new game, perform the game loop and display the game with SDL
 * \param size Variable representing the size of the Board (Small, Medium or Large)
 */
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
    Board board;	//Variable to access the board
    Snake snake1;	//Variable to access the first snake
    Snake snake2;	//Variable to access the first snake

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

    gameFeed(game); //Function called to put some food on the board

   	  /************************/
	 /**	  GAME LOOP		**/
	/************************/
    while (gameGetIsPlaying(game)) {

        timer->start = SDL_GetTicks(); // Start of the current frame

        /***** Move of snake 1 (player) *****/
        timer->snake1MoveTimer += SDL_GetTicks() - timer->snake1LastMove;
        if (timer->snake1MoveTimer >= snakeGetSpeed(snake1)) {  // test if we wait enough time to move the snake 1
            guiSnakeEvent(&event, snake1);                      // catch player event and set the direction of snake1
            continueGameMove1 = gameMoveSnake(game, snake1);   // move th snake1. if snake1 is dead continueGameMove1=false
            timer->snake1MoveTimer = 0;                         // set the move timer to 0 when the snake move
        }
        timer->snake1LastMove = SDL_GetTicks();
        /******************************************/

        /***** Move of snake 2 (AI) *****/
        timer->snake2MoveTimer += SDL_GetTicks() - timer->snake2LastMove;
        if (timer->snake2MoveTimer >= snakeGetSpeed(snake2)) {  // test if we wait enough time to move the snake 2
            snakeSetDirection(snake2, iaRandom(board, snake2));  // let ia choose the best direction of snake2
            continueGameMove2 = gameMoveSnake(game, snake2);   // move th snake2. if snake2 is dead continueGameMove2=false
            timer->snake2MoveTimer = 0 ;                        // set the move timer to 0 when the snake move
        }
        timer->snake2LastMove = SDL_GetTicks();
        /***********************************/

        /***** Draw *****/
        guiDrawGame(screen, game, assets);  // draw the board on srceen with surfaces stored in the Assets struct
        guiReloadScreen(screen);            // reload all the screen
        /***************/

        if(!continueGameMove1 || !continueGameMove2) // if one snake die the game is over
            gameEnd(game);

        /***** Framerate management *****/
        timer->end = SDL_GetTicks();                           // Get the time after the calculations
        timer->delay = FRAME_MS - (timer->end - timer->start); // Calculate how long to delay should be
        if(timer->delay > 0) {
            SDL_Delay(timer->delay);                           // Delay processing
        }
    }

    /***** Free *****/
    gameFree(game);
    guiFreeAssets(assets);
    SDL_Quit();
}


/**
 * \fn SDL_Surface* guiCreateScreen(BoardSize size)
 * \brief The function creates the screen
 * \details The function creates the screen depending on the size in parameter
 * \param size BoardSize: the type of the board (Small, Medium, Large)
 * \return The SDL_Surface* of the screen
 */
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

/**
 * \fn SDL_Surface* guiLoadImage(char* path)
 * \brief The function load the image given in parameter
 * \details The function load the image given in parameter
 * \param path the path of the image relative to the root folder
 * \return The SDL_Surface* of the image
 */
SDL_Surface* guiLoadImage(char* path) {
    SDL_Surface *s;
    if(!(s = IMG_Load(path)))
        printf("%s\n", IMG_GetError());

    return s;
}

/**
 * \fn Assets guiLoadAssets()
 * \brief The function load all assets of the game
 * \details The function load all assets of the game
 * \return The Assets struct with all assets loaded
 */
Assets guiLoadAssets() {
    Assets assets = malloc(sizeof(struct Assets));
    assets->background = guiLoadImage("./images/background/bg-medium.png");
    assets->food = guiLoadImage("./images/item/food.png");

    char *colors[3] = {"blue", "red", "green"};

    assets->snakesAssets = malloc(3*sizeof(SnakeAssets));
    int i;
    for (i = 0; i < 3; i++) { // mettre à i < 3 si 3 couleurs chargé
        assets->snakesAssets[i] = guiLoadSnake(i, colors[i]); // WATER=0, FIRE=1, GRASS=2
    }

    return assets;
}

/**
 * \fn void guiFreeAssets(Assets assets)
 * \brief The function free the struct Assets
 * \details The function free the struct Assets
 * \param assets The Assets struct to free
 */
void guiFreeAssets(Assets assets) {
    free(assets->background);
    free(assets->food);
    int i;
    for (i = 0; i < 3; i++) { // mettre à i < 3 si 3 couleurs chargé
        free(assets->snakesAssets[i]); // WATER=0, FIRE=1, GRASS=2
    }

    free(assets);
}

/**
 * \fn SnakeAssets guiLoadSnake(SnakeType type, char* color)
 * \brief The function load a SnakeAssets
 * \details The function load all assets needed to draw a snake (head, body, corner, tail)
 * \param type The snake type (WATER, FIRE, GRASS)
 * \param color The color of the snake
 * \return The SnakeAssets struct of the loaded snake
 */
SnakeAssets guiLoadSnake(SnakeType type, char* color) {
    char *path = malloc(100*sizeof(char));
    SnakeAssets snakeAssets = malloc(sizeof(struct SnakeAssets));
    snakeAssets->head = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->body = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->corner = malloc(4*sizeof(SDL_Surface*));
    snakeAssets->tail = malloc(4*sizeof(SDL_Surface*));

    char sDirection[4];
    sDirection[0] = 'U';
    sDirection[1] = 'R';
    sDirection[2] = 'D';
    sDirection[3] = 'L';

    int direction; // UP=0, RIGHT=1, DOWN=2, LEFT=3
    for (direction = 0; direction < 4; direction++) {
        sprintf(path, "./images/snake/%s/head/%c.png", color, sDirection[direction]);
        snakeAssets->head[direction] = guiLoadImage(path);
        sprintf(path, "./images/snake/%s/corner/%c.png", color, sDirection[direction]);
        snakeAssets->corner[direction] = guiLoadImage(path);
        sprintf(path, "./images/snake/%s/tail/%c.png", color, sDirection[direction]);
        snakeAssets->tail[direction] = guiLoadImage(path);
        sprintf(path, "./images/snake/%s/body/%c.png", color, sDirection[direction]);
        snakeAssets->body[direction] = guiLoadImage(path);
    }

    return snakeAssets;
}

/**
 * \fn void guiDrawGame(SDL_Surface *screen, Game game, Assets assets)
 * \brief Draw the entire game on the screen
 * \details Draw each element of the game on the screen with SDL
 * \param screen The screen to draw on
 * \param game The game struct containing all elements of the game
 * \param assets The Assets struct containing all assets of the game
 * \return The SnakeAssets struct of the loaded snake
 */
void guiDrawGame(SDL_Surface *screen, Game game, Assets assets) {
    Snake snake1 = gameGetSnake(game, 1);
    Snake snake2 = gameGetSnake(game, 2);
    Item itemList = gameGetItemList(game);

    guiApplySurface(0, 0, assets->background, screen, NULL); // dessine le background
    guiDrawSnake(screen, snake1, assets->snakesAssets[snakeGetType(snake1)]);
    guiDrawSnake(screen, snake2, assets->snakesAssets[snakeGetType(snake2)]);
    guiDrawItems(screen, itemList, assets->food);
    //guiApplySurface(gameGetFood(game)->posX*M_CELL_SIZE, M_CELL_SIZE*gameGetFood(game)->posY, assets->food, screen, NULL);
}


void guiDrawItems(SDL_Surface *screen, Item itemList, SDL_Surface* surface) {

    Item item = itemList;
    int x, y;

    while(item != NULL) {
        x = item->posX * M_CELL_SIZE;
        y = item->posY * M_CELL_SIZE;
        switch(item->value) {
            case SENTRY:
                break;

            case FOOD:
                guiApplySurface(x, y, surface, screen, NULL);
                break;

            default:
                break;
        }
        item = item->next;
    }
}


/**
 * \fn void guiDrawSnake(SDL_Surface *screen, Snake snake, SnakeAssets snakeAssets)
 * \brief Draw one snake on the screen
 * \details Draw one snake on the screen
 * \param screen The screen to draw on
 * \param snake The snake to draw
 * \param snakeAssets The skin to associate to the snake
 */
void guiDrawSnake(SDL_Surface *screen, Snake snake, SnakeAssets snakeAssets) {
    int i;
    int x, y;
    Direction currentDirection;
    Direction nextDirection;

    for (i=0; i<snakeGetSize(snake); i++) {
        x = snakeGetPos(snake, i)->x * M_CELL_SIZE;
        y = snakeGetPos(snake, i)->y * M_CELL_SIZE;

        currentDirection = snakeElementGetOrientation(snake, i);


        if(i == 0) // tail
        {
            nextDirection = snakeElementGetOrientation(snake, i+1);
            if(currentDirection != nextDirection)
                guiApplySurface(x, y, snakeAssets->tail[nextDirection], screen, NULL);
            else
                guiApplySurface(x, y, snakeAssets->tail[currentDirection], screen, NULL);
        }
        else if (i == snakeGetSize(snake)-1) // head
            guiApplySurface(x, y, snakeAssets->head[currentDirection], screen, NULL);
        else // body
        {
            nextDirection = snakeElementGetOrientation(snake, i+1);
            if(currentDirection != nextDirection)
            {
                if(currentDirection == RIGHT)
                {
                    if(nextDirection == UP)
                        guiApplySurface(x, y, snakeAssets->corner[LEFT], screen, NULL);
                    else // DOWN
                        guiApplySurface(x, y, snakeAssets->corner[DOWN], screen, NULL);
                }
                else if(currentDirection == UP)
                {
                    if(nextDirection == RIGHT)
                        guiApplySurface(x, y, snakeAssets->corner[RIGHT], screen, NULL);
                    else // LEFT
                        guiApplySurface(x, y, snakeAssets->corner[DOWN], screen, NULL);
                }
                else if(currentDirection == DOWN)
                {
                    if(nextDirection == RIGHT)
                        guiApplySurface(x, y, snakeAssets->corner[UP], screen, NULL);
                    else // LEFT
                        guiApplySurface(x, y, snakeAssets->corner[LEFT], screen, NULL);
                }
                else if(currentDirection == LEFT)
                {
                    if(nextDirection == UP)
                        guiApplySurface(x, y, snakeAssets->corner[UP], screen, NULL);
                    else // DOWN
                        guiApplySurface(x, y, snakeAssets->corner[RIGHT], screen, NULL);
                }
            }
            else
                guiApplySurface(x, y, snakeAssets->body[currentDirection], screen, NULL);
        }
    }
}

/**
 * \fn void guiApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
 * \brief Draw one surface on the screen
 * \details Draw one surface on the screen at the position x, y with a SDL_BlitSurface call
 * \param x The x position
 * \param y The y position
 * \param source The surface to draw
 * \param destination The surface to draw on
 * \param clip The rectangle representing the area of source to draw (NULL = all the source surface)
 */
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

/**
 * \fn guiCreateTimer()
 * \brief Create the Timer struct
 * \details Create the Timer struct
 * \return The Timer struct created
 */
Timer guiCreateTimer() {
    Timer timer = malloc(sizeof(struct Timer));
    timer->snake1MoveTimer = SNAKE_DEFAULT_SPEED; // pour être certain que les deux snake bouge des le début
    timer->snake2MoveTimer = SNAKE_DEFAULT_SPEED;

    timer->snake1LastMove = 0;
    timer->snake2LastMove = 0;

    return timer;
}

/**
 * \fn void guiReloadScreen(SDL_Surface *screen)
 * \brief Reload the entire screen
 * \details Reload the entire screen with a SDL_Flip call
 * \param screen The screen surface to reload
 */
void guiReloadScreen(SDL_Surface *screen) {
    SDL_Flip(screen);
}

/**
 * \fn void guiSnakeEvent(SDL_Event *event, Snake s)
 * \brief Catch all player input
 * \details Catch all player input and set the snake direction
 * \param event The event struct to listen
 * \param s The snake to be oriented
 */
void guiSnakeEvent(SDL_Event *event, Snake s) {
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

/**
 * \fn void guiGeneralEvent(SDL_Event *event, Game game)
 * \brief Catch all player input
 * \details Catch all player input and quit the game on SDL_QUIT
 * \param event The event struct to listen
 * \param game The game to end on quit
 */
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

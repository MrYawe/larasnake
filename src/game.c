/**
 * \file game.c
 * \author groupe Larakis
 * \version 1
 * \date 19/04/2016
 * \brief Everything about the game class
 * \details Contains all functions to manage the game
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "constants.h"
#include "game.h"
#include <SDL/SDL_mixer.h>

// Static function
static bool gameCheckMovement(Game g, Snake s);

//////////////////////////////////////////
//				STRUCTURE				//
//////////////////////////////////////////

/**
 * \struct Game
 * \brief The game structure
 * \details The structure contains a board, the two snakes and a boolean to know if the game is currently playing
 **/
struct Game
{
	Board board; // le board
	Snake snake1; // joueur 1
	Snake snake2; // joueur 2
	//Item itemList;
	bool isPlaying;
	bool isPaused;
	int pauseFinished;

	Mix_Chunk **sound;
	int numberSound;
};

/**
 * \fn Game gameCreate(BoardSize size)
 * \brief The function creates the game
 * \details The function store the game in the memory and initialize the snakes
 * \param size BoardSize: the type of the board to init
 * \return Returns Game pointer to the crated game
 */
Game gameCreate(BoardSize size)
{

	Game g = malloc(sizeof(struct Game));

	switch (size) {
		case SMALL:
			g->board = boardInit(S_SIZE_BOARD_X, S_SIZE_BOARD_Y, S_CELL_SIZE);
			g->snake1 = snakeCreate(SNAKE_DEFAULT_SIZE_SMALL, SNAKE1, RIGHT, WATER);
			g->snake2 = snakeCreate(SNAKE_DEFAULT_SIZE_SMALL, SNAKE2, LEFT, FIRE);
			break;
		case MEDIUM:
			g->board = boardInit(M_SIZE_BOARD_X, M_SIZE_BOARD_Y, M_CELL_SIZE);
			g->snake1 = snakeCreate(SNAKE_DEFAULT_SIZE_MEDIUM, SNAKE1, RIGHT, WATER);
			g->snake2 = snakeCreate(SNAKE_DEFAULT_SIZE_MEDIUM, SNAKE2, LEFT, FIRE);
			break;
		case LARGE:
			g->board = boardInit(L_SIZE_BOARD_X, L_SIZE_BOARD_Y, L_CELL_SIZE);
			g->snake1 = snakeCreate(SNAKE_DEFAULT_SIZE_LARGE, SNAKE1, RIGHT, WATER);
			g->snake2 = snakeCreate(SNAKE_DEFAULT_SIZE_LARGE, SNAKE2, LEFT, FIRE);
			break;
	}

	g->isPlaying = true;
	g->pauseFinished=4;
	g->isPaused = true;


	//init sound
	g->numberSound=8; //CHANGE HERE THE NUMBER OF SOUND
	g->sound=malloc(g->numberSound*sizeof(Mix_Chunk *));
	Mix_AllocateChannels(g->numberSound+1);

	//load sounds
	g->sound[0] = Mix_LoadWAV("./sound/pickItem.wav");
	g->sound[1] = Mix_LoadWAV("./sound/eatHam.wav");
	g->sound[2] = Mix_LoadWAV("./sound/changeBody.wav");
	g->sound[3] = Mix_LoadWAV("./sound/reverseSnake.wav");
	g->sound[4] = Mix_LoadWAV("./sound/changeBg.wav");
	g->sound[5] = Mix_LoadWAV("./sound/mp.wav");
	g->sound[6] = Mix_LoadWAV("./sound/speedUp.wav");
	g->sound[7] = Mix_LoadWAV("./sound/ghostBuster.wav");


	gameInitSnakes(g->board, g->snake1, g->snake2);

	return g;
}

/**
 * \fn void gameFree(Game game)
 * \brief Free the struct game
 * \details  Free the struct game
 * \param game The game struct to free
 */
void gameFree(Game game)
{
	boardFree(game->board);
	snakeFree(game->snake1);
	snakeFree(game->snake2);
	int i;
	for(i=0;i<game->numberSound;i++)
	{
	 	Mix_FreeChunk(game->sound[i]); //free all the sounds of the array
	}
	free(game->sound);
	free(game);
}

/**
 * \fn Board gameGetBoard(Game g)
 * \brief Accessor to the board of the game structure
 * \details The function returns the board of the game
 * \param g Game: The game to access
 * \return Returns Board pointer
 */
Board gameGetBoard(Game g)
{
	return g->board;
}

/**
 * \fn Snake game(Game g, int player)
 * \brief Accessor to the snake of the game structure
 * \details The function returns the snake of the game
 * \param g Game: The game to access
 * \param player Int: The player number
 * \return Returns Snake pointer
 */
Snake gameGetSnake(Game g, int id)
{
	if (snakeGetId(g->snake1) == id)
		return g->snake1;
	else
		return g->snake2;
}
/*
Item gameGetItemList(Game g) {
	return g->itemList;
}*/

/**
 * \fn bool gameGetIsPlaying(Game g)
 * \brief Accessor to the isPlaying boolean of the game structure
 * \details The function returns the isPlaying of the game
 * \param g Game: The game to access
 * \return Bool: Returns isPlaying
 */
bool gameGetIsPlaying(Game g)
{
	return g->isPlaying;
}

bool gameGetIsPaused(Game g)
{
	return g->isPaused;
}

void gameSetIsPaused(Game g, bool isPaused)
{
	g->isPaused = isPaused;
}
int gameGetPauseTimer(Game g)
{
	return g->pauseFinished;
}
void gameSetPauseTimer(Game g, int t)
{
	g->pauseFinished=t;
}

/**
 * \fn void gameEnd(Game g)
 * \brief End the game
 * \details The function put false to the isPlaying bool
 * \param g Game: The game to end
 */
void gameEnd(Game g)
{
	g->isPlaying = false;
}

/**
 * \fn void gameInitSnakes(Board b, Snake s1, Snake s2)
 * \brief Initialize the snakes of the game
 * \details The function put the snakes on the board at the beggining of the game
 * \param b Board: where to put the snakes on
 * \param s1 Snake: First snake to put on the board
 * \param s2 Snake: Second snake to put on the board
 */
void gameInitSnakes(Board b, Snake s1, Snake s2)
{
	int i;
	for (i=0; i<snakeGetSize(s1); i++)
	{
			snakeUpdateElement(s1, snakeGetSize(s1) - i -1, boardGetWidth(b)/3-i, boardGetHeight(b)/2-1);
	}
	for (i=0; i<snakeGetSize(s2); i++)
	{
			snakeUpdateElement(s2, snakeGetSize(s2) - i -1, boardGetWidth(b)/3*2+i, boardGetHeight(b)/2);
	}
	gameUpdateSnake(b, s1);
	gameUpdateSnake(b, s2);
}

/**
 * \fn void gameUpdateSnake(Board b, Snake s)
 * \brief Update the board with the position of the snake
 * \details The function iterates on Snake's Elements and put them on the board
 * \param b Board: where to update the snake
 * \param s Snake to put on the board
 */
void gameUpdateSnake(Board b, Snake s)
{
	Coord snakePos;
	int i;
	for (i=0; i<snakeGetSize(s); i++)
	{
		snakePos=snakeGetPos(s, i);
		boardSetValue(b, snakePos->x, snakePos->y, snakeGetId(s));
	}
}

/**
 * \fn bool gameMoveSnake(Board b, Snake s)
 * \brief Update the board with the snake movement
 * \details Update the board without iterating on elements
 * \param g Game: the game
 * \param s Snake to move on the board
 */
bool gameMoveSnake(Game g, Snake s)
{
	//bool continueGame = gameCheckMovement(s, b);

	//Coord posSnakeTail = snakeGetPos(s, 0);
	//Coord posSnakeHead = snakeGetPos(s, snakeGetSize(s)-1);

	//if(continueGame){
	Board b = gameGetBoard(g);


		boardSetValue(b, snakeGetPos(s, 0)->x, snakeGetPos(s, 0)->y, 0);
        //printf("posTailBOARD x:%d y:%d\n",posSnakeTail->x, posSnakeTail->y);
		bool continueGame = gameCheckMovement(g, s);
		boardSetValue(b, snakeGetPos(s, snakeGetSize(s)-1)->x, snakeGetPos(s, snakeGetSize(s)-1)->y, snakeGetId(s));
	//}
		//printf("posHeadBOARD x:%d y:%d\n",posSnakeHead->x, posSnakeHead->y);
	//free(posSnakeTail);
	//free(posSnakeHead);
/*
	Board b = gameGetBoard(g);
	bool continueGame = gameCheckMovement(g, s);

	Coord posSnakeTail = snakeGetPos(s, 0);
	Coord posSnakeHead = snakeGetPos(s, snakeGetSize(s)-1);

	if(continueGame){
		boardSetValue(b, posSnakeTail->x, posSnakeTail->y, 0);
		boardSetValue(b, posSnakeHead->x, posSnakeHead->y, snakeGetId(s));
	}
	free(posSnakeTail);
	free(posSnakeHead);
*/
	return continueGame;
}


/**
 * \fn static bool gameCheckMovement(Snake s, Board b)
 * \brief Check collisions
 * \details Check if the next cell doesn't contains a snake or isn't a border
 * \param g Game: the game
 * \param s Snake to move
 */
static bool gameCheckMovement(Game g, Snake s)
{
	Board b = gameGetBoard(g);
	bool continueGame = true;
	Coord coordSnake = snakeGetPos(s, snakeGetSize(s)-1);
	Direction dirSnake = snakeGetDirection(s);
	//BUG Next pos cell quand fantôme

	if (boardIsNextCellType(b, coordSnake->x, coordSnake->y, dirSnake, 1, OUTSIDE))
	{
		if (snakeGetCanCrossBorder(s)) // if he can cross border
		{
			switch (snakeGetDirection(s))
			{
				case UP:
					snakeTeleportation(s, coordSnake->x, boardGetHeight(b)-1);
					break;
				case DOWN:
					snakeTeleportation(s, coordSnake->x, 0);
					break;
				case LEFT:
					snakeTeleportation(s, boardGetWidth(b)-1, coordSnake->y);
					break;
				case RIGHT:
					snakeTeleportation(s, 0, coordSnake->y);
					break;
				default:
					printf("Error checkMovement\n");
					break;
			}
		}
		else
		{
			printf("Le snake s'est pris une bordure !\n");
			continueGame = false;
		}
	}
	else if (!snakeIsGhost(s) && !snakeGetCanCrossBorder(s) && boardIsNextCellType(b, coordSnake->x, coordSnake->y, dirSnake, 1, WALL_P))
	{
		printf("Le snake s'est pris un mur !\n");
		continueGame = false;
	}
	else if (boardIsNextCellType(b, coordSnake->x, coordSnake->y, dirSnake, 2, SNAKE1, SNAKE2))
	{
		printf("Snake %d mort !\n", snakeGetId(s));
		continueGame = false;
	}
	else if (boardIsNextCellType(b, coordSnake->x, coordSnake->y, dirSnake, 12, FOOD, SPEED_UP, GROW_UP, GROW_DOWN, REVERSE_CONTROL, REVERSE_SNAKE, NO_BORDER, GHOST, SWAP_SNAKE, NEW_COLOR, NEW_MAP, WALL)) //items
	{
		Snake otherSnake;
		Coord coordItem = boardNextPosCell(coordSnake->x, coordSnake->y, dirSnake);

		Item itemList = boardGetItemList(b);
		Item item = itemSearch(itemList, coordItem->x, coordItem->y);

		if(snakeGetId(s) == 1) {
			otherSnake = gameGetSnake(g, 2);
		} else {
			otherSnake = gameGetSnake(g, 1);
		}
		if(item->value==14)
		{
			boardSetType(b,true); //changeMap
		}
		switch (dirSnake)
		{
			case UP:
				snakeGoUp(s);
				break;
			case DOWN:
				snakeGoDown(s);
				break;
			case LEFT:
				snakeTurnLeft(s);
				break;
			case RIGHT:
				snakeTurnRight(s);
				break;
			default:
				printf("Error checkMovement\n");
				break;
		}
		if(item->value==4)
			gameFeed(g, true);

		gameItemCollision(item, s, otherSnake,g);
		playItemSound(g, item);
		boardItemDelete(b, item);


	}
	else
	{
		switch (dirSnake)
		{
			case UP:
				snakeGoUp(s);
				break;
			case DOWN:
				snakeGoDown(s);
				break;
			case LEFT:
				snakeTurnLeft(s);
				break;
			case RIGHT:
				snakeTurnRight(s);
				break;
			default:
				printf("Error checkMovement\n");
				break;
		}
	}
	//detection of the field part -fire-water-grass 0-1-2
	char currentFieldValue=boardGetFieldValue(b,coordSnake->x, coordSnake->y);
	if(currentFieldValue!='-')
	{
		int type=currentFieldValue-'0'; //conversion en int
		s->isAffectedByField=true;
		int typeSnake=snakeGetType(s);
		if( typeSnake==type)
			snakeSetSpeed(s,SNAKE_DEFAULT_SPEED-3*SPEED_UP_VALUE);
		else
		{
			if(( typeSnake==FIRE && type==WATER) || ( typeSnake==WATER && type==GRASS) || ( typeSnake==GRASS && type==FIRE))
				snakeSetSpeed(s,SNAKE_DEFAULT_SPEED+5*SPEED_UP_VALUE);
		}

		//printf("%d/%d\n",snakeGetType(s),type);
		//printf("%d/%d/%d\n",FIRE,WATER,GRASS);
	}
	else if(s->isAffectedByField) //we leave the affected field
	{
		s->isAffectedByField=false;
		snakeSetSpeed(s,SNAKE_DEFAULT_SPEED);
	}
	//-----
	return continueGame;
}

/**
 * \fn void playItemSound(Game g, Item i)
 * \brief The function play a sound depending the item
 * \details The function just check the item id and play a sound when the player pick it
 * \param g Game : The current game
 * \param i Item : The item picked
 */
void playItemSound(Game g, Item i)
{
	int id=i->value;

	if(id==4) //eat ham
	{
		Mix_VolumeChunk(g->sound[1], MIX_MAX_VOLUME); //set sound volume
		Mix_PlayChannel(1, g->sound[1], 0);
	}
	else if(id==12) //change body
	{
		Mix_VolumeChunk(g->sound[2], MIX_MAX_VOLUME/2); //set sound volume
		Mix_PlayChannel(2, g->sound[2], 0);
	}
	else if(id==9)//reverse Snake
	{
		Mix_VolumeChunk(g->sound[3], MIX_MAX_VOLUME-40); //set sound volume
		Mix_PlayChannel(3, g->sound[3], 0);
	}
	else if(id==14) //change bg
	{
		Mix_VolumeChunk(g->sound[4], MIX_MAX_VOLUME); //set sound volume
		Mix_PlayChannel(4, g->sound[4], 0);
	}
	else if(id==15) //wall
	{
		Mix_VolumeChunk(g->sound[5], MIX_MAX_VOLUME/2); //set sound volume
		Mix_PlayChannel(5, g->sound[5], 0);
	}
	else if(id==5)//speed_up
	{
		Mix_VolumeChunk(g->sound[6], MIX_MAX_VOLUME/2); //set sound volume
		Mix_PlayChannel(6, g->sound[6], 0);
	}
	else if(id==11)//ghost
	{
		Mix_VolumeChunk(g->sound[7], MIX_MAX_VOLUME); //set sound volume
		Mix_PlayChannel(7, g->sound[7], 0);
	}
	else
	{
		Mix_VolumeChunk(g->sound[0], MIX_MAX_VOLUME); //set sound volume
		Mix_PlayChannel(0, g->sound[0], 0);
	}
}

void gameItemCollision(Item i, Snake sOnCollision, Snake sBis, Game g) {
	switch (i->value) {

		case SENTRY:
            printf("Sentry collision\n");
            break;
        case FOOD:
            itemOnCollisionFood(i, sOnCollision, sBis, g->board);
            break;
        case SPEED_UP:
            itemOnCollisionSpeedUp(i, sOnCollision, sBis);
            break;
        case GROW_UP:
            itemOnCollisionGrowUp(i, sOnCollision, sBis, g->board);
            break;
        case GROW_DOWN:
            itemOnCollisionGrowDown(i, sOnCollision, sBis, g->board);
            break;
        case REVERSE_CONTROL:
            itemOnCollisionReverseControl(i, sOnCollision, sBis);
            break;
        case REVERSE_SNAKE:
            itemOnCollisionReverseSnake(i, sOnCollision, sBis);
            break;
        case NO_BORDER:
            itemOnCollisionNoBorder(i, sOnCollision, sBis);
            break;
        case GHOST:
            itemOnCollisionGhost(i, sOnCollision, sBis);
            break;
        case SWAP_SNAKE:
            itemOnCollisionSwapSnake(i, sOnCollision, sBis);
            break;
        case NEW_COLOR:
            itemOnCollisionNewColor(i, sOnCollision, sBis);
            break;
        case NEW_MAP:
            itemOnCollisionNewMap(i, sOnCollision, sBis);
            break;
        case WALL:
            itemOnCollisionWall(i, sOnCollision, sBis, g);
            break;
        default:
            printf("Item non implemented\n");
    }
}


void gameItemDebuff(Item i, Snake snake) {
	switch (i->value) {

		case SENTRY:
            printf("Sentry debuff\n");
            break;
        case SPEED_UP:
            itemOnDebuffSpeedUp(i, snake);
            break;
        case REVERSE_CONTROL:
            itemOnDebuffReverseControl(i, snake);
            break;
        case NO_BORDER:
            itemOnDebuffNoBorder(i, snake);
            break;
        case GHOST:
            itemOnDebuffGhost(i, snake);
            break;
        default:
            printf("Item non implemented\n");
    }
}

/**
 * \fn bool boardIsSnake(Board b, Coord coord)
 * \brief The function allow to know if a cell is a part of a snake
 * \details The function returns a boolean to know if the cell of the coordinates passed in arguments is a part of a snake
 * \param b Board : The board to access
 * \param coord Coord : Coordinates of the cell to test
 * \return Returns boolean which say if the cell is a snake
 */
/*bool boardIsSnake(Board b, Coord coord)
{
	bool res=false;
	if(boardInside(b, coord->x, coord->y) && (boardGetValue(b, coord->x, coord->y)==1 || boardGetValue(b, coord->x, coord->y)==2)){
		res = true;
	}
	return res;
}*/

/**
 * \fn void gameFeed(Game game)
 * \brief The function puts a food in the board
 * \details The function set a food coodinates in the board structure
 * \param b Board : The board to edit
 */
void gameFeed(Game game, bool ham)
{
	Board b = gameGetBoard(game);
	int x = rand()%boardGetWidth(b);
	int y = rand()%boardGetHeight(b);
	while(boardGetValue(b, x, y)!=0){
		x = rand()%boardGetWidth(b);
		y = rand()%boardGetHeight(b);
	}
	BoardValue itemValue;
	if(ham)
		itemValue = FOOD;
	else
	{
		itemValue=itemGetRandomItemValue();
		if(itemValue==FOOD)
			itemValue=5;
	}

	boardItemAdd(b, x, y, itemValue);
	printf("Ajout de l'item %d: (%d, %d)\n", itemValue, x, y);
}

/**
 * \fn Coord boardNextPosCell(int x, int y, Direction dir)
 * \brief The function allow to get the next cell
 * \details The function allow to get the next cell from a position and a direction
 * \param x Int: the x coordinate of the current position
 * \param y Int: the y coordinate of the current position
 * \param dir Direction: the direction to go
 * \return Returns Coord which correspond to the next cell
 */
Coord boardNextPosCell(int x, int y, Direction dir)
{
  	Coord res = coordNew(x, y);
    switch (dir)
    {
        case UP:
            res->y -= 1;
            break;

        case DOWN:
            res->y += 1;
            break;

        case LEFT:
            res->x -= 1;
            break;

        case RIGHT:
            res->x += 1;
            break;

        default:
          printf("Error isNextCellBorder\n");
          break;
    }
    return res;
}

/**
 * \fn bool boardIsNextCellSnake(Board b, int x, int y, Direction dir)
 * \brief The function allow to know if the next cell is a part of a snake
 * \details The function returns a boolean to know if the next cell of the coordinates passed in arguments is a part of a snake
 * \param b Board : The board to access
 * \param x Board : The actual X position
 * \param y Board : The actual Y position
 * \param dir Direction : Direction to go
 * \return Returns boolean which say if the next cell is a snake
 */
/*bool boardIsNextCellSnake(Board b, int x, int y, Direction dir)
{
    Coord nextPos = boardNextPosCell(x, y, dir);
    return boardIsSnake(b, nextPos);
}*/

/**
 * \fn bool boardIsNextCellBorder(Board b, int x, int y, Direction dir)
 * \brief The function allow to know if the next cell is a part of a border
 * \details The function returns a boolean to know if the next cell of the coordinates passed in arguments is a part of a border
 * \param b Board : The board to access
 * \param x Board : The actual X position
 * \param y Board : The actual Y position
 * \param dir Direction : Direction to go
 * \return Returns boolean which say if the next cell is a border
 */
/*bool boardIsNextCellBorder(Board b, int x, int y, Direction dir)
{
    bool res = false;
    Coord nextPos = boardNextPosCell(x, y, dir);

    if ((dir == UP || dir== DOWN) &&
    (nextPos->y<0 || nextPos->y>boardGetHeight(b)-1))
    {
        res = true;
    }
    else if ((dir == LEFT || dir == RIGHT) &&
    (nextPos->x<0 || nextPos->x>boardGetWidth(b)-1))
    {
        res = true;
    }
    return res;
}*/

/*
 * \fn bool boardIsNextCellType(Board b, int x, int y, Direction dir, int n, ...)
 * \brief Check if the next cell of the board is the type of the given parameter(s)
 * \details Check if the next cell of the board is the type of the given parameter(s)
 * \param b Board : board to access
 * \param x Board : The actual X position
 * \param y Board : The actual Y position
 * \param dir Direction : The direction to test
 * \param n int : Number of arguments after this one (dynamic number of arguments)
 * \param n*BoardValue : We can pass as much of arguments of we want to test different types at one time
 * \return bool: If the type is in the list of arguments, = 1
 */
bool boardIsNextCellType(Board b, int x, int y, Direction dir, int n, ...)
{
	Coord coord = boardNextPosCell(x, y, dir);
	bool res = false;
	int i;
	BoardValue value;
	va_list va;
	va_start(va,n);	//indicating va to point on the first variable argument
	for(i=0;i<n;i++){
		value = va_arg (va, BoardValue);
		if(!res && value==-1 && !boardInside(b, coord->x, coord->y))
		{
			res = true;
		}
		else if(!res && boardGetValue(b, coord->x, coord->y)==value){
			res = true;
		}
	}
	va_end(va); //clean memory assigned to varlist
	free(coord);
	return res;
}

/*
 * \fn void gameSetFieldValue(Game g, int type, int taille)
 * \brief Open and read the field values
 * \details Open the file associated to the current board, read the values, and complete the board fieldAssets
 * \param g Game : the current game
 * \param type int : the field type (lava, water, ...)
 * \param taille int: the field size (big, medium, small)
 */
void gameSetFieldValue(Game g, int type, int taille)
{
	Board b = g->board;
	int x= boardGetWidth(b);
	int y= boardGetHeight(b);
	char path[31];
	sprintf(path,"./boardData/bg-%d-%d.txt",type, taille); //open de right file text
	printf("%s\n", path);
	FILE *field = fopen(path, "r");
	int i,j;
	char v;
//x=50
//y=35
	for(j=0;j<y;j++){
      for(i=0;i<x;i++){
          v=fgetc(field);
					while(v==13 || v==10) //remove \n
						  v=fgetc(field);
					boardSetFieldValue(b, i, j, v);
					//printf("%d-%d\n",i,j);
      }
		//	printf("\n");
  }
}
/************************/
/**   ITEM FONCTIONS   **/
/************************/

void itemOnCollisionFood(Item i, Snake sOnCollision, Snake sBis, Board b) {
    printf("COLLISION JAMBON\n");
    int k;
    for (k = 0; k < FOOD_VALUE; k++) {
        snakeGrowTail(sOnCollision);
    }
	gameUpdateSnake(b, sOnCollision);
}

//---------
void itemOnCollisionSpeedUp(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION SPEED_UP\n");
    snakeSetSpeed(sOnCollision, snakeGetSpeed(sOnCollision)-SPEED_UP_VALUE);
	itemAddNew(snakeGetItemList(sOnCollision), -1, -1, i->value);
}

void itemOnDebuffSpeedUp(Item i, Snake snake) {
    printf("DEBUFF SPEED_UP\n");
    snakeSetSpeed(snake, snakeGetSpeed(snake)+SPEED_UP_VALUE);
	itemDelete(i);
}
//---------


void itemOnCollisionGrowUp(Item i, Snake sOnCollision, Snake sBis, Board b) {
    printf("COLLISION GROW_UP\n");
    int k;
    for (k = 0; k < GROW_UP_VALUE; k++) {
        snakeGrowHead(sOnCollision);
    }
	gameUpdateSnake(b, sOnCollision);
}

void itemOnCollisionGrowDown(Item i, Snake sOnCollision, Snake sBis, Board b) {
    printf("COLLISION GROW_DOWN\n");
    if(snakeGetSize(sOnCollision)>5){
    	boardSetValue(b, sOnCollision->tail->pos->x, sOnCollision->tail->pos->y, EMPTY);
    	snakeDeleteFirstElement(sOnCollision);
    	boardSetValue(b, sOnCollision->tail->pos->x, sOnCollision->tail->pos->y, EMPTY);
		snakeDeleteFirstElement(sOnCollision);
    	boardSetValue(b, sOnCollision->tail->pos->x, sOnCollision->tail->pos->y, EMPTY);
		snakeDeleteFirstElement(sOnCollision);
    	boardSetValue(b, sOnCollision->tail->pos->x, sOnCollision->tail->pos->y, EMPTY);
		snakeDeleteFirstElement(sOnCollision);
    }
    
}

//---------
void itemOnCollisionReverseControl(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_CONTROL\n");
    snakeSetIsControlReversed(sOnCollision, true);
    snakeSetIsControlReversed(sBis, true);
	itemAddNew(snakeGetItemList(sOnCollision), -1, -1, i->value);
	itemAddNew(snakeGetItemList(sBis), -1, -1, i->value);
}

void itemOnDebuffReverseControl(Item i, Snake snake) {
    printf("DEBUFF REVERSE_CONTROL\n");
    snakeSetIsControlReversed(snake, false);
	itemDelete(i);
}
//---------


void itemOnCollisionReverseSnake(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_SNAKE\n");
    // TODO franck: la tete devient la queue
}

//---------
void itemOnCollisionNoBorder(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NO_BORDER\n");
    snakeSetCanCrossBorder(sOnCollision, true);
	itemAddNew(snakeGetItemList(sOnCollision), -1, -1, i->value);
}

void itemOnDebuffNoBorder(Item i, Snake snake) {
    printf("DEBUFF NO_BORDER\n");
	if(itemSearchByValue(i->next, NO_BORDER) == NULL && itemSearchByValue(i->next, GHOST) == NULL) {
		snakeSetCanCrossBorder(snake, false);
	}

	itemDelete(i);
}
//---------

//---------
void itemOnCollisionGhost(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GHOST\n");
    snakeSetCanCrossBorder(sOnCollision, true);
    snakeSetCanCrossSnake(sOnCollision, true);
	itemAddNew(snakeGetItemList(sOnCollision), -1, -1, i->value);
}

void itemOnDebuffGhost(Item i, Snake snake) {
    printf("DEBUFF GHOST\n");
	if(itemSearchByValue(i->next, GHOST) == NULL) {
		if(itemSearchByValue(i->next, NO_BORDER) == NULL) {
			snakeSetCanCrossBorder(snake, false);
		}
		snakeSetCanCrossSnake(snake, false);
	}
	itemDelete(i);
}
//---------

void itemOnCollisionSwapSnake(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION SWAP_SNAKE\n");
    struct Snake temp = *sBis;
    *sBis = *sOnCollision;
    *sOnCollision = temp;
}

void itemOnCollisionNewColor(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NEW_COLOR\n");
    SnakeType t1 = snakeGetType(sOnCollision);
    SnakeType t2 = snakeGetType(sBis);
    if( (t1==WATER || t2==WATER) && (t1==FIRE || t2==FIRE) ) {
        snakeSetType(sOnCollision, GRASS);
    } else if ( (t1==WATER || t2==WATER) && (t1==GRASS || t2==GRASS) ) {
        snakeSetType(sOnCollision, FIRE);
    } else {
        snakeSetType(sOnCollision, WATER);
    }
}

void itemOnCollisionNewMap(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NEW_MAP\n");
    //change map: done in gui.c
}

void itemOnCollisionWall(Item it, Snake sOnCollision, Snake sBis, Game game) {
    printf("COLLISION WALL\n");

		Board b = gameGetBoard(game);
		int xMax=boardGetWidth(b)-1;
		int yMax=boardGetHeight(b)-1;
		int x = rand()%xMax+1;
		int y = rand()%yMax+1;

		BoardValue itemValue=16;
		int j=rand()%80+30;
		int i;

		for(i=0;i<j;i++)
		{
			if(boardGetValue(b,x,y)==EMPTY) {
				boardItemAdd(b, x, y,itemValue);
				int nx = rand()%3-1;
				int ny = rand()%3-1;
				while((x==nx && y == ny) || !boardInside(b,x+nx,y+ny))
				{
					nx = rand()%3-1;
					ny = rand()%3-1;
				}
				x=x+nx;
				y=y+ny;
			}
			
		}
		printf("Ajout d'un mur !\n");
}

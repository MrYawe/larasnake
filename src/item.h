#ifndef ITEM_H
#define ITEM_H

#include "snake.h"
#include "game.h"


typedef struct Item *Item;
/**
 * \struct Item
 * \brief The item structure
 * \details
 **/
struct Item
{
    int posX;
    int posY;
    BoardValue value;
    void (*onCollision)(int idSnake, Game game); // idSnake:id du snake qui a touché l'object
};

/*** Object ***/
Item itemCreate(int x, int y, BoardValue value);


/*** Collisions ***/
void itemOnCollisionFood(int idSnake, Game game);

#endif

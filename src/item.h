#ifndef ITEM_H
#define ITEM_H

#include "enum.h"

typedef struct Item* Item;
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
    void (*onCollision)(int idSnake); // idSnake:id du snake qui a touché l'object
};

/*** Object ***/
Item itemCreate(int x, int y, BoardValue value);


/*** Collisions ***/
void itemOnCollisionFood(int idSnake);

#endif

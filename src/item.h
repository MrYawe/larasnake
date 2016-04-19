#ifndef ITEM_H
#define ITEM_H

/**
 * \file item.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Headers of item file
 * \details All header of the item file functions
 */

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
void itemFree(Item item);


/*** Collisions ***/
void itemOnCollisionFood(int idSnake);

#endif

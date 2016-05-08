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
#include "board.h"
#include "snake.h"


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
    void (*onCollision)(Item i, Board b, Snake sOnCollision, Snake sBis); // idSnake:id du snake qui a touché l'object
    Item prev;
    Item next;
};

/*** Object ***/
Item itemCreate(int x, int y, BoardValue value);
Item itemAdd(Item list, Board board, int x, int y, BoardValue value);
BoardValue itemGetRandomItemValue();
Item itemSearch(Item list, int x, int y);
void itemDelete(Item item, Board board);
void itemFree(Item item);

/*** Collisions ***/
void itemOnCollisionFood(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionSpeedUp(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionGrowUp(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionGrowDown(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionReverseControl(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionReverseSnake(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionNoBorder(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionGhost(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionSwapSnake(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionNewColor(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionNewMap(Item i, Board b, Snake sOnCollision, Snake sBis);
void itemOnCollisionWall(Item i, Board b, Snake sOnCollision, Snake sBis);

#endif

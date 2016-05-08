/**
 * \file item.c
 * \author groupe Larakis
 * \version 1
 * \date 19/04/2016
 * \brief Everything about the item class
 * \details Contains all functions to create, edit, delete and acess the items of the game
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "item.h"
#include "constants.h"



/************************/
/**   ITEM FONCTIONS   **/
/************************/

void itemOnCollisionFood(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION JAMBON\n");
    int k;
    for (k = 0; k < FOOD_VALUE; k++) {
        snakeGrow(sOnCollision);
    }
    itemDelete(i, b);
}

void itemOnCollisionSpeedUp(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION SPEED_UP\n");
    snakeSetSpeed(sOnCollision, snakeGetSpeed(sOnCollision)-SPEED_UP_VALUE);
    itemDelete(i, b);
}

void itemOnCollisionGrowUp(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GROW_UP\n");
    int k;
    for (k = 0; k < GROW_UP_VALUE; k++) {
        snakeGrow(sOnCollision);
    }
    itemDelete(i, b);
}

void itemOnCollisionGrowDown(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GROW_DOWN\n");
}

void itemOnCollisionReverseControl(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_CONTROL\n");
}

void itemOnCollisionReverseSnake(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_SNAKE\n");
}

void itemOnCollisionNoBorder(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NO_BORDER\n");
}

void itemOnCollisionGhost(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GHOST\n");
}

void itemOnCollisionSwapSnake(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION SWAP_SNAKE\n");
}

void itemOnCollisionNewColor(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NEW_COLOR\n");
}

void itemOnCollisionNewMap(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NEW_MAP\n");
}

void itemOnCollisionWall(Item i, Board b, Snake sOnCollision, Snake sBis) {
    printf("COLLISION WALL\n");
}
















/**
 * \fn Item itemCreate(int x, int y, BoardValue value)
 * \brief The function create the item struct
 * \details The function create the item struct
 * \param x The x postion
 * \param y The y postion
 * \param value The value of the item in the board
 */

Item itemCreate(int x, int y, BoardValue value) {
    Item item = malloc(sizeof(struct Item));
    item->posX = x;
    item->posY = y;
    item->value = value;
    item->prev = NULL;
    item->next = NULL;

    switch (item->value) {
        case SENTRY:
            item->onCollision = NULL;
            break;
        case FOOD:
            item->onCollision = itemOnCollisionFood;
            break;
        case SPEED_UP:
            item->onCollision = itemOnCollisionSpeedUp;
            break;
        case GROW_UP:
            item->onCollision = itemOnCollisionGrowUp;
            break;
        case GROW_DOWN:
            item->onCollision = itemOnCollisionGrowDown;
            break;
        case REVERSE_CONTROL:
            item->onCollision = itemOnCollisionReverseControl;
            break;
        case REVERSE_SNAKE:
            item->onCollision = itemOnCollisionReverseSnake;
            break;
        case NO_BORDER:
            item->onCollision = itemOnCollisionNoBorder;
            break;
        case GHOST:
            item->onCollision = itemOnCollisionGhost;
            break;
        case SWAP_SNAKE:
            item->onCollision = itemOnCollisionSwapSnake;
            break;
        case NEW_COLOR:
            item->onCollision = itemOnCollisionNewColor;
            break;
        case NEW_MAP:
            item->onCollision = itemOnCollisionNewMap;
            break;
        case WALL:
            item->onCollision = itemOnCollisionWall;
            break;
        default:
            printf("Item non implemented\n");
    }

    return item;
}

// ajout en fin
Item itemAdd(Item list, Board board, int x, int y, BoardValue value) {
    Item newItem = itemCreate(x, y, value);

    Item temp = list;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newItem;
    newItem->prev = temp;
    boardSetValue(board, x, y, value);

    return list;
}

Item itemSearch(Item list, int x, int y) {
    Item temp = list;
    while(temp != NULL) {
        if(temp->posX == x && temp->posY == y) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void itemDelete(Item item, Board board) {
    if(item->value == SENTRY) // we can't delete the sentry
        return;

    boardSetValue(board, item->posX, item->posY, EMPTY);
    item->prev->next = item->next;
    itemFree(item);
}



/**
 * \fn void itemFree(Item item)
 * \brief The function free the memory of the item
 * \details The function free the memory of the item
 * \param item Item to free from memory
 */
void itemFree(Item item) {
    free(item);
}

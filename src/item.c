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

void itemOnCollisionFood(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION JAMBON\n");
    int k;
    for (k = 0; k < FOOD_VALUE; k++) {
        snakeGrow(sOnCollision);
    }
    //itemDelete(i, b);
}

void itemOnCollisionSpeedUp(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION SPEED_UP\n");
    snakeSetSpeed(sOnCollision, snakeGetSpeed(sOnCollision)-SPEED_UP_VALUE);
}

void itemOnCollisionGrowUp(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GROW_UP\n");
    int k;
    for (k = 0; k < GROW_UP_VALUE; k++) {
        snakeGrow(sOnCollision);
    }
}

void itemOnCollisionGrowDown(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GROW_DOWN\n");
    printf("PAS ENCORE IMPLEMENTE\n");
    // TODO franck: le retrecir
}

void itemOnCollisionReverseControl(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_CONTROL\n");
    snakeSetIsControlReversed(sOnCollision, true);
    snakeSetIsControlReversed(sBis, true);
}

void itemOnCollisionReverseSnake(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION REVERSE_SNAKE\n");
    snakeInverseWay(sOnCollision);
}

void itemOnCollisionNoBorder(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION NO_BORDER\n");
    snakeSetCanCrossBorder(sOnCollision, true);
}

void itemOnCollisionGhost(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION GHOST\n");
    snakeSetCanCrossBorder(sOnCollision, true);
    snakeSetCanCrossSnake(sOnCollision, true);
}

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
    printf("PAS ENCORE IMPLEMENTE\n");
    // TODO: change la map
}

void itemOnCollisionWall(Item i, Snake sOnCollision, Snake sBis) {
    printf("COLLISION WALL\n");
    printf("PAS ENCORE IMPLEMENTE\n");
    // TODO: fait pop un item mur
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

BoardValue itemGetRandomItemValue() {
    int x = rand()%12;
    return x+4;
}

// ajout en fin
Item itemAdd(Item list, int x, int y, BoardValue value) {
    Item newItem = itemCreate(x, y, value);

    Item temp = list;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newItem;
    newItem->prev = temp;
    //boardSetValue(board, x, y, value);

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

int itemDelete(Item item) {
    if(item->value == SENTRY) // we can't delete the sentry
        return 0;

    //boardSetValue(board, item->posX, item->posY, EMPTY);

    if(item->next != NULL) {
        item->next->prev = item->prev;
    }
    item->prev->next = item->next;

    return 1;
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

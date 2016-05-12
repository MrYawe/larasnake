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

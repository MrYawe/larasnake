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
 * \return Item Return the created item
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

/**
 * \fn BoardValue itemGetRandomItemValue()
 * \brief Get a random item value
 * \return BoardValue Return the random board value
 */
BoardValue itemGetRandomItemValue() {
    int x = rand()%12;
    return x+4;
}

/**
 * \fn Item itemAddNew(Item list, int x, int y, BoardValue value)
 * \brief Add a new item in a item list
 * \param list The item list
 * \param x The x postion
 * \param y The y postion
 * \param value The value of the item in the board
 * \return Item Return the first item (sentry) of the list
 */
Item itemAddNew(Item list, int x, int y, BoardValue value) {
    Item newItem = itemCreate(x, y, value);
    itemAdd(list, newItem);

    return list;
}

/**
 * \fn Item itemAdd(Item list, Item toAdd)
 * \brief Add a existing item in the item list
 * \param list The item list
 * \param toAdd The item to add
 * \return Item Return the first item (sentry) of the list
 */
Item itemAdd(Item list, Item toAdd) {

    Item temp = list;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = toAdd;
    toAdd->prev = temp;

    return list;
}

/**
 * \fn Item itemSearch(Item list, int x, int y)
 * \brief Search a item in the list by position x, y
 * \param list The item list
 * \param x The x position
 * \param y The y position
 * \return Item The item searched. NULL if not found
 */
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

/**
 * \fn Item itemSearchByValue(Item list, BoardValue value)
 * \brief Search a item in the list by value
 * \param list The item list
 * \param value The value of the item
 * \return Item The item searched. NULL if not found
 */
Item itemSearchByValue(Item list, BoardValue value) {
    Item temp = list;
    while(temp != NULL) {
        if(temp->value == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/**
 * \fn int itemDelete(Item item)
 * \brief Delete an item in his list
 * \param item The item to delete
 * \return Return 1 if the item is deleted
 */
int itemDelete(Item item) {
    if(item->value == SENTRY) // we can't delete the sentry
        return 0;

    //boardSetValue(board, item->posX, item->posY, EMPTY);
    printf("1\n");
    if(item->next != NULL) {
        item->next->prev = item->prev;
    }
    printf("2\n");
    item->prev->next = item->next;
    printf("3\n");

    return 1;
}

/**
 * \fn bool itemListIsEmpty(Item list)
 * \brief Test if the item list is empty
 * \param list The item list
 */
bool itemListIsEmpty(Item list) {
    if(list->next != NULL) {
        return false;
    }
    return true;
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

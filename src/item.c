#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "item.h"
#include "constants.h"

void itemOnCollisionFood(int idSnake) {
    printf("COLLISION JAMBON\n");
}

Item itemCreate(int x, int y, BoardValue value) {
    Item item = malloc(sizeof(struct Item));
    /*item->posX = x;
    item->posY = y;
    item->value = value;

    switch (item->value) {
        case FOOD:
            item->onCollision = itemOnCollisionFood;
            break;
    }
*/
    return item;
}
void itemFree(Item item) {
    free(item);
}

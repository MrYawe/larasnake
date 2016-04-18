#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "item.h"
#include "constants.h"
#include "board.h"




void itemOnCollisionFood(int idSnake, Game game) {
    /*printf("COLLISION JAMBON\n");
    Item food = boardGetFood(gameGetBoard(game));
    free(food);

    boardFeed(gameGetBoard(game));*/
}


Item itemCreate(int x, int y, BoardValue value) {
    Item item = malloc(sizeof(struct Item));
    item->posX = x;
    item->posY = y;
    item->value = value;

    switch (item->value) {
        case FOOD:
            item->onCollision = itemOnCollisionFood;
            break;
    }

    return item;
}
void itemFree(Item item) {
    free(item);
}

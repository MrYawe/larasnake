#ifndef ENUM_H
#define ENUM_H

/**
 * \file enum.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief All the enums of the program
 * \details Contains all defines of enums of the program
 */

typedef enum BoardValue {
    OUTSIDE=-1, EMPTY,
    SNAKE1, SNAKE2,
    SENTRY,
    FOOD, SPEED_UP, GROW_UP, GROW_DOWN, REVERSE_CONTROL, REVERSE_SNAKE, NO_BORDER, GHOST, SWAP_SNAKE, NEW_COLOR, NEW_MAP, WALL,
    NB_ITEM
} BoardValue;

typedef enum MenuValue {
    PLAY, INSTRUCTION, OPTION, QUIT
} MenuValue;

#endif

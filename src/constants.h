#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * \file contant.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief The constants for the program
 * \details All constants defined, used in the program
 */

// General
#define FRAME_MS 30 // Temps en milliseconde par frame. 30ms ~= 30 FPS



/*** Menus ***/
#define MENU_SIZE_X 600
#define MENU_SIZE_Y 600
#define MENU_POLICE_SIZE 30
#define MENU_POLICE_INTERVAL 80

/*** Snake ***/
#define SNAKE_DEFAULT_SPEED 100 // en ms
#define SNAKE_DEFAULT_SIZE_SMALL 8
#define SNAKE_DEFAULT_SIZE_MEDIUM 15
#define SNAKE_DEFAULT_SIZE_LARGE 20

#define NB_TYPES 3

/*** Bonus parameters ***/
#define ITEM_POP_INTERVAL 5000
#define ITEM_DEBUFF_INTERVAL 6000
#define FOOD_VALUE 1
#define SPEED_UP_VALUE 20 // de combien de ms la vitesse est augmenté
#define GROW_UP_VALUE 3
#define GROW_DOWN_VALUE 3


/*** Board dimensions ***/
// Small
#define S_SIZE_BOARD_X 35
#define S_SIZE_BOARD_Y 25
#define S_CELL_SIZE 20

// Medium
#define M_SIZE_BOARD_X 50
#define M_SIZE_BOARD_Y 35
#define M_CELL_SIZE 20

// Large
#define L_SIZE_BOARD_X 65
#define L_SIZE_BOARD_Y 35
#define L_CELL_SIZE 20

/***  ***/

#endif

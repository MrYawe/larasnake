/**
 * \file testBoard.c
 * \author groupe Larakis
 * \version 1
 * \date 21/03/2016
 * \brief Tests unitaires de Board
 * \details Toutes les fonctions necessaires pour tester board.c
 */

#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/snake.h"


/**
 * \fn testBoardInit
 * \brief Test the bord initilization
 * \details This function test if cells' values are equal to 0 after board's initilization
 * \param state Parameter generated by Cmocka
 */
// void testBoardInit(void **state) {
//     int x, y;
//     Board *b = boardInit(SIZE_X, SIZE_Y, 20);
//     for(y=0; y<boardGetHeight(b); y++) {
//         for (x=0; x<boardGetWidth(b); x++) {
//             assert_int_equal(boardGetValue(b, x, y), 0);
//         }
//     }
//     boardFree(b);
// }


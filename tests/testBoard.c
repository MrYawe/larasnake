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

#include "../src/board.h"
#include "testBoard.h"

#define SIZE_X 32
#define SIZE_Y 16

/**
 * \fn testBoardInit
 * \brief Test the bord initilization
 * \details This function test if cells' values are equal to 0 after board's initilization
 * \param state Parameter generated by Cmocka
 */
void testBoardInit(void **state) {
    int x, y;
    Board *b = boardInit(SIZE_X, SIZE_Y, 20);
    for(y=0; y<boardGetHeight(b); y++) {
        for (x=0; x<boardGetWidth(b); x++) {
            assert_int_equal(boardGetValue(b, x, y), 0);
        }
    }
    boardFree(b);
}

/**
 * \fn testBoardValue
 * \brief Test the cell's values' affectation
 * \details The function test if the affectation of the cell (5,8) with the value 3 is correct
 * \param state Parameter generated by Cmocka
 */
void testBoardValue(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y,20);
    boardSetValue(b, 5, 8, 3); // val (5, 8) = 3
    assert_int_equal(boardGetValue(b, 5, 8), 3);
    boardFree(b);
}

/**
 * \fn testBoardSize
 * \brief Test the board size
 * \details The function test if the size generated is correct
 * \param state Parameter generated by Cmocka
 */
void testBoardSize(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y,20);
    assert_int_equal(boardGetWidth(b), SIZE_X);
    assert_int_equal(boardGetHeight(b), SIZE_Y);
    boardFree(b);
}

/**
 * \fn testBoardCopy
 * \brief Test if the board you've just copied is the same
 * \details The function create a new board (by copy), then test different assets, such as size, values, initialization
 * \param state Parameter generated by Cmocka
 */
void testBoardCopy(void **state) {
    Board *b1 = boardInit(SIZE_X, SIZE_Y,20);
    Board *b2 = boardCopy(b1);
    int x,y;
    assert_int_equal(boardGetWidth(b1), boardGetWidth(b2));
    assert_int_equal(boardGetHeight(b1), boardGetHeight(b2));

    for(y=0; y<boardGetHeight(b1); y++) {
        for (x=0; x<boardGetWidth(b1); x++) {
            assert_int_equal(boardGetValue(b1, x, y), boardGetValue(b2, x, y));
        }
    }
    boardFree(b1);
    boardFree(b2);
}

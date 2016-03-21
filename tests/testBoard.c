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

#define SIZE_X 32
#define SIZE_Y 16

/**
 * \fn testBoardInit
 * \brief Test l'initilisation du plateau
 * \details La fonction teste si toutes les cases du board sont égal à 0 après initilisation
 * \param state Parametre géré par cmocka
 */
void testBoardInit(void **state) {
    int x, y;
    Board *b = boardInit(SIZE_X, SIZE_Y);
    for(y=0; y<boardGetSize(b, Column); y++) {
        for (x=0; x<boardGetSize(b, Line); x++) {
            assert_int_equal(boardGetValue(b, x, y), 0);
        }
    }
}

/**
 * \fn testBoardValue
 * \brief Test l'affectation d'une valeur à une case du board
 * \details La fonction teste si l'affectation de la valeur 3 à la case (5, 8) est correct
 * \param state Parametre géré par cmocka
 */
void testBoardValue(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y);
    boardSetValue(b, 5, 8, 3); // val (5, 8) = 3
    assert_int_equal(boardGetValue(b, 5, 8), 3);
}

/**
 * \fn testBoardSize
 * \brief Test la taille du board
 * \details La fonction teste si la taille du board renvoyé est correct
 * \param state Parametre géré par cmocka
 */
void testBoardSize(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y);
    assert_int_equal(boardGetSize(b, Line), SIZE_X);
    assert_int_equal(boardGetSize(b, Column), SIZE_Y);
}

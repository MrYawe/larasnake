#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/board.h"

#define SIZE_X 32
#define SIZE_Y 16

void testBoardInit(void **state) {
    int x, y;
    Board *b = boardInit(SIZE_X, SIZE_Y);
    for(y=0; y<boardGetSize(b, Column); y++) {
        for (x=0; x<boardGetSize(b, Line); x++) {
            assert_int_equal(boardGetValue(b, x, y), 0);
        }
    }
}

void testBoardValue(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y);
    boardSetValue(b, 5, 8, 3); // val (5, 8) = 3
    assert_int_equal(boardGetValue(b, 5, 8), 3);
}

void testBoardSize(void **state) {
    Board *b = boardInit(SIZE_X, SIZE_Y);
    assert_int_equal(boardGetSize(b, Line), SIZE_X);
    assert_int_equal(boardGetSize(b, Column), SIZE_Y);
}

#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "testBoard.h"

int main () {
	const struct CMUnitTest tests[] = {
        /** Start Test Board **/
        cmocka_unit_test(testBoardInit),
        cmocka_unit_test(testBoardValue),
        cmocka_unit_test(testBoardSize),
        /** End Test Board **/
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

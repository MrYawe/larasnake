#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "testBoard.h"
#include "testSnake.h"
#include "testIa.h"

int main () 
{
	const struct CMUnitTest board[] = {
        cmocka_unit_test(testBoardInit),
        cmocka_unit_test(testBoardValue),
        cmocka_unit_test(testBoardSize),
		cmocka_unit_test(testBoardCopy),
    };
    

    const struct CMUnitTest snake[] = {
        cmocka_unit_test(testSnakeInit),
    };
    

    const struct CMUnitTest ia[] = {
        cmocka_unit_test(testIaJambon),
    };


    cmocka_run_group_tests(board, NULL, NULL);
    printf("\n\n");
    cmocka_run_group_tests(snake, NULL, NULL);
    printf("\n\n");
    cmocka_run_group_tests(ia, NULL, NULL);

    return 0;
}
 
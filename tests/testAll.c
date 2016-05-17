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
        cmocka_unit_test(testBoardValueAccessor),
        cmocka_unit_test(testBoardInside),
        cmocka_unit_test(testManageItem),
        cmocka_unit_test(testManageBoardType),
        cmocka_unit_test(testManageAssets)
    };
    

    const struct CMUnitTest snake[] = {
        cmocka_unit_test(testSnakeInitPos),
        cmocka_unit_test(testSnakeMovementUp),
        cmocka_unit_test(testSnakeMovementDown),
        cmocka_unit_test(testSnakeMovementLeft),
        cmocka_unit_test(testSnakeMovementRight),
        cmocka_unit_test(testSnakeMovementTp),
        cmocka_unit_test(testSnakeGrowHead),
        cmocka_unit_test(testSnakeGrowTail),
        cmocka_unit_test(testSnakeGetPos),
        cmocka_unit_test(testSnakeManageDirection),
        cmocka_unit_test(testSnakeManageTypes),
        cmocka_unit_test(testSnakeManageSpeed),
        cmocka_unit_test(testSnakeManageOrientation),
        cmocka_unit_test(testSnakeManageControls),
        cmocka_unit_test(testSnakeManageCrossBorders),
        cmocka_unit_test(testSnakeManageCrossSnakes)
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
 
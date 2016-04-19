#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "testBoard.h"
#include "testSnake.h"
#include "testIa.h"

int main () {
	const struct CMUnitTest tests[] = {
        /** Start Test Board **/
        cmocka_unit_test(testBoardInit),
        cmocka_unit_test(testBoardValue),
        cmocka_unit_test(testBoardSize),
		cmocka_unit_test(testBoardCopy),
        /** End Test Board **/

        /** Start Test Snake **/
        
        /** End Test Snake **/

        /** Start Test IA **/
        
        /** End Test IA **/
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
 
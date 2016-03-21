# CMake generated Testfile for 
# Source directory: /home/asn/workspace/projects/cmocka/tests
# Build directory: /home/asn/workspace/projects/cmocka/obj32/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_alloc "/home/asn/workspace/projects/cmocka/obj32/tests/test_alloc")
add_test(test_group_setup_fail "/home/asn/workspace/projects/cmocka/obj32/tests/test_group_setup_fail")
set_tests_properties(test_group_setup_fail PROPERTIES  WILL_FAIL "1")
add_test(test_fixtures "/home/asn/workspace/projects/cmocka/obj32/tests/test_fixtures")
add_test(test_group_fixtures "/home/asn/workspace/projects/cmocka/obj32/tests/test_group_fixtures")
add_test(test_assert_macros "/home/asn/workspace/projects/cmocka/obj32/tests/test_assert_macros")
add_test(test_assert_macros_fail "/home/asn/workspace/projects/cmocka/obj32/tests/test_assert_macros_fail")
set_tests_properties(test_assert_macros_fail PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  FAILED  \\] 1 test")
add_test(test_exception_handler "/home/asn/workspace/projects/cmocka/obj32/tests/test_exception_handler")
set_tests_properties(test_exception_handler PROPERTIES  PASS_REGULAR_EXPRESSION "Test failed with exception: (Segmentation fault|Segmentation Fault|11)")
add_test(test_basics "/home/asn/workspace/projects/cmocka/obj32/tests/test_basics")
add_test(test_skip "/home/asn/workspace/projects/cmocka/obj32/tests/test_skip")
set_tests_properties(test_skip PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  SKIPPED \\] test_check_skip")
add_test(test_setup_fail "/home/asn/workspace/projects/cmocka/obj32/tests/test_setup_fail")
set_tests_properties(test_setup_fail PROPERTIES  WILL_FAIL "1")
add_test(test_cmockery "/home/asn/workspace/projects/cmocka/obj32/tests/test_cmockery")
add_test(test_setup_fail_1_failed "test_setup_fail")
set_tests_properties(test_setup_fail_1_failed PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  ERROR   \\] int_test_ignored")
add_test(test_setup_fail_1_passed "test_setup_fail")
set_tests_properties(test_setup_fail_1_passed PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  PASSED  \\] 1 test\\(s\\).")
add_test(test_setup_fail_match_failed "test_setup_fail")
set_tests_properties(test_setup_fail_match_failed PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  ERROR   \\] int_test_ignored")
add_test(test_setup_fail_match_passed "test_setup_fail")
set_tests_properties(test_setup_fail_match_passed PROPERTIES  PASS_REGULAR_EXPRESSION "\\[       OK \\] int_test_success")
add_test(test_basics_tap "test_basics")
set_tests_properties(test_basics_tap PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=tap" PASS_REGULAR_EXPRESSION "^1\\.\\.2[ 
]+ok 1 - null_test_success")
add_test(test_assert_macros_fail_tap "test_assert_macros_fail")
set_tests_properties(test_assert_macros_fail_tap PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=tap" PASS_REGULAR_EXPRESSION "^1\\.\\.1[ 
]+not ok 1 - test_assert_return_code_fail")
add_test(test_skip_tap "test_skip")
set_tests_properties(test_skip_tap PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=tap" PASS_REGULAR_EXPRESSION "not ok 1 # SKIP")
add_test(test_setup_fail_tap "test_setup_fail")
set_tests_properties(test_setup_fail_tap PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=tap" PASS_REGULAR_EXPRESSION "not ok 1 - int_test_ignored Could not run the test - check test fixtures")
add_test(test_basics_subunit "test_basics")
set_tests_properties(test_basics_subunit PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=subunit" PASS_REGULAR_EXPRESSION "^test: null_test_success[ 
]+success: null_test_success")
add_test(test_assert_macros_fail_subunit "test_assert_macros_fail")
set_tests_properties(test_assert_macros_fail_subunit PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=subunit" PASS_REGULAR_EXPRESSION "failure: test_assert_return_code_fail \\[")
add_test(test_skip_subunit "test_skip")
set_tests_properties(test_skip_subunit PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=subunit" PASS_REGULAR_EXPRESSION "^test: test_check_skip[ 
]+skip: test_check_skip")
add_test(test_setup_fail_subunit "test_setup_fail")
set_tests_properties(test_setup_fail_subunit PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=subunit" PASS_REGULAR_EXPRESSION "error: int_test_ignored \\[ Could not run the test - check test fixtures \\]")
add_test(test_basics_xml "test_basics")
set_tests_properties(test_basics_xml PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=xml" PASS_REGULAR_EXPRESSION "<testsuite name=\"tests\" time=\"[0-9.]+\" tests=\"2\" failures=\"0\" errors=\"0\" skipped=\"0\" >[ 
]+<testcase name=\"null_test_success\" time=\"[0-9.]+\" >.*</testcase>")
add_test(test_assert_macros_fail_xml "test_assert_macros_fail")
set_tests_properties(test_assert_macros_fail_xml PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=xml" PASS_REGULAR_EXPRESSION "<testcase name=\"test_assert_return_code_fail\" time=\"[0-9.]+\" >[ 
]+<failure>")
add_test(test_skip_xml "test_skip")
set_tests_properties(test_skip_xml PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=xml" PASS_REGULAR_EXPRESSION "<testcase name=\"test_check_skip\" time=\"[0-9.]+\" >[ 
]+<skipped/>")
add_test(test_setup_fail_xml "test_setup_fail")
set_tests_properties(test_setup_fail_xml PROPERTIES  ENVIRONMENT "CMOCKA_MESSAGE_OUTPUT=xml" PASS_REGULAR_EXPRESSION "<testcase name=\"int_test_ignored\" time=\"[0-9.]+\" >[ 
]+<failure><!\\[CDATA\\[Test setup failed\\]\\]></failure>")

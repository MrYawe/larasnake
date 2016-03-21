# CMake generated Testfile for 
# Source directory: /home/asn/workspace/projects/cmocka/example
# Build directory: /home/asn/workspace/projects/cmocka/obj32/example
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simple_test "/home/asn/workspace/projects/cmocka/obj32/example/simple_test")
add_test(calculator_test "/home/asn/workspace/projects/cmocka/obj32/example/calculator_test")
add_test(allocate_module_test "/home/asn/workspace/projects/cmocka/obj32/example/allocate_module_test")
set_tests_properties(allocate_module_test PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  FAILED  \\] 3 test")
add_test(assert_macro_test "/home/asn/workspace/projects/cmocka/obj32/example/assert_macro_test")
set_tests_properties(assert_macro_test PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  FAILED  \\] 2 test")
add_test(assert_module_test "/home/asn/workspace/projects/cmocka/obj32/example/assert_module_test")
set_tests_properties(assert_module_test PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  FAILED  \\] 2 test")
add_test(customer_database_test "/home/asn/workspace/projects/cmocka/obj32/example/customer_database_test")
add_test(key_value_test "/home/asn/workspace/projects/cmocka/obj32/example/key_value_test")
add_test(product_database_test "/home/asn/workspace/projects/cmocka/obj32/example/product_database_test")
set_tests_properties(product_database_test PROPERTIES  PASS_REGULAR_EXPRESSION "\\[  FAILED  \\] 2 test")
subdirs(chef_wrap)

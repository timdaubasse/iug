# CMake generated Testfile for 
# Source directory: /net/cremi/chapellegrini/ProjetTech/iug/tests
# Build directory: /net/cremi/chapellegrini/ProjetTech/iug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("fill_copy_window" "/net/cremi/chapellegrini/ProjetTech/iug/tests/unit_tests" "fill_copy_window" "--durations" "yes" "--warn" "NoAssertions" "--name" "unit_tests ( build)")
set_tests_properties("fill_copy_window" PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran" LABELS ";unit;" TIMEOUT "10")

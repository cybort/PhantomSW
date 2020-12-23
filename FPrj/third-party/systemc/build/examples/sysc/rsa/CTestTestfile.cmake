# CMake generated Testfile for 
# Source directory: /home/f21538/systemc-2.3.3/examples/sysc/rsa
# Build directory: /home/f21538/systemc-2.3.3/objdir/examples/sysc/rsa
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/rsa/rsa "/home/f21538/svn/cmake-3.19.0-rc3-Linux-x86_64/bin/cmake" "-DTEST_EXE=/home/f21538/systemc-2.3.3/objdir/examples/sysc/rsa/rsa" "-DTEST_DIR=/home/f21538/systemc-2.3.3/objdir/examples/sysc/rsa" "-DTEST_INPUT=" "-DTEST_GOLDEN=" "-DTEST_FILTER=" "-DDIFF_COMMAND=/usr/bin/diff" "-DDIFF_OPTIONS=-u" "-P" "/home/f21538/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/rsa/rsa PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR" _BACKTRACE_TRIPLES "/home/f21538/systemc-2.3.3/examples/CMakeLists.txt;137;add_test;/home/f21538/systemc-2.3.3/examples/sysc/rsa/CMakeLists.txt;44;configure_and_add_test;/home/f21538/systemc-2.3.3/examples/sysc/rsa/CMakeLists.txt;0;")

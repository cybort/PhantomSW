# CMake generated Testfile for 
# Source directory: /home/f21538/systemc-2.3.3/examples/sysc/pipe
# Build directory: /home/f21538/systemc-2.3.3/objdir/examples/sysc/pipe
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/pipe/pipe "/home/f21538/svn/cmake-3.19.0-rc3-Linux-x86_64/bin/cmake" "-DTEST_EXE=/home/f21538/systemc-2.3.3/objdir/examples/sysc/pipe/pipe" "-DTEST_DIR=/home/f21538/systemc-2.3.3/objdir/examples/sysc/pipe" "-DTEST_INPUT=" "-DTEST_GOLDEN=" "-DTEST_FILTER=" "-DDIFF_COMMAND=/usr/bin/diff" "-DDIFF_OPTIONS=-u" "-P" "/home/f21538/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/pipe/pipe PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR" _BACKTRACE_TRIPLES "/home/f21538/systemc-2.3.3/examples/CMakeLists.txt;137;add_test;/home/f21538/systemc-2.3.3/examples/sysc/pipe/CMakeLists.txt;54;configure_and_add_test;/home/f21538/systemc-2.3.3/examples/sysc/pipe/CMakeLists.txt;0;")

# CMake generated Testfile for 
# Source directory: /home/f21538/systemc-2.3.3/examples/sysc/simple_fifo
# Build directory: /home/f21538/systemc-2.3.3/objdir/examples/sysc/simple_fifo
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/simple_fifo/simple_fifo "/home/f21538/svn/cmake-3.19.0-rc3-Linux-x86_64/bin/cmake" "-DTEST_EXE=/home/f21538/systemc-2.3.3/objdir/examples/sysc/simple_fifo/simple_fifo" "-DTEST_DIR=/home/f21538/systemc-2.3.3/objdir/examples/sysc/simple_fifo" "-DTEST_INPUT=" "-DTEST_GOLDEN=/home/f21538/systemc-2.3.3/examples/sysc/simple_fifo/golden.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=/usr/bin/diff" "-DDIFF_OPTIONS=-u" "-P" "/home/f21538/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/simple_fifo/simple_fifo PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR" _BACKTRACE_TRIPLES "/home/f21538/systemc-2.3.3/examples/CMakeLists.txt;137;add_test;/home/f21538/systemc-2.3.3/examples/sysc/simple_fifo/CMakeLists.txt;44;configure_and_add_test;/home/f21538/systemc-2.3.3/examples/sysc/simple_fifo/CMakeLists.txt;0;")

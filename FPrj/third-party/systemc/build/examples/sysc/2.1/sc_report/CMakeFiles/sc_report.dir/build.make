# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/f21538/svn/cmake-3.19.0-rc3-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/f21538/svn/cmake-3.19.0-rc3-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/f21538/systemc-2.3.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/f21538/systemc-2.3.3/objdir

# Include any dependencies generated for this target.
include examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/depend.make

# Include the progress variables for this target.
include examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/flags.make

examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.o: examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/flags.make
examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.o: ../examples/sysc/2.1/sc_report/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.o"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sc_report.dir/main.cpp.o -c /home/f21538/systemc-2.3.3/examples/sysc/2.1/sc_report/main.cpp

examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sc_report.dir/main.cpp.i"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f21538/systemc-2.3.3/examples/sysc/2.1/sc_report/main.cpp > CMakeFiles/sc_report.dir/main.cpp.i

examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sc_report.dir/main.cpp.s"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f21538/systemc-2.3.3/examples/sysc/2.1/sc_report/main.cpp -o CMakeFiles/sc_report.dir/main.cpp.s

# Object files for target sc_report
sc_report_OBJECTS = \
"CMakeFiles/sc_report.dir/main.cpp.o"

# External object files for target sc_report
sc_report_EXTERNAL_OBJECTS =

examples/sysc/2.1/sc_report/sc_report: examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/main.cpp.o
examples/sysc/2.1/sc_report/sc_report: examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/build.make
examples/sysc/2.1/sc_report/sc_report: src/libsystemc.a
examples/sysc/2.1/sc_report/sc_report: examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sc_report"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sc_report.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/build: examples/sysc/2.1/sc_report/sc_report

.PHONY : examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/build

examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/clean:
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report && $(CMAKE_COMMAND) -P CMakeFiles/sc_report.dir/cmake_clean.cmake
.PHONY : examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/clean

examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/depend:
	cd /home/f21538/systemc-2.3.3/objdir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/f21538/systemc-2.3.3 /home/f21538/systemc-2.3.3/examples/sysc/2.1/sc_report /home/f21538/systemc-2.3.3/objdir /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report /home/f21538/systemc-2.3.3/objdir/examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sysc/2.1/sc_report/CMakeFiles/sc_report.dir/depend


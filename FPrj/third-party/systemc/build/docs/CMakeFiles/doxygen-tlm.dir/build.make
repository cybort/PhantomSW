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

# Utility rule file for doxygen-tlm.

# Include the progress variables for this target.
include docs/CMakeFiles/doxygen-tlm.dir/progress.make

docs/CMakeFiles/doxygen-tlm: docs/tlm/doxygen/html/index.html


docs/tlm/doxygen/html/index.html:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building the TLM source code documentation using Doxygen."
	cd /home/f21538/systemc-2.3.3/objdir/docs/tlm/doxygen && /usr/bin/doxygen /home/f21538/systemc-2.3.3/objdir/docs/tlm/doxygen/Doxyfile

doxygen-tlm: docs/CMakeFiles/doxygen-tlm
doxygen-tlm: docs/tlm/doxygen/html/index.html
doxygen-tlm: docs/CMakeFiles/doxygen-tlm.dir/build.make

.PHONY : doxygen-tlm

# Rule to build all files generated by this target.
docs/CMakeFiles/doxygen-tlm.dir/build: doxygen-tlm

.PHONY : docs/CMakeFiles/doxygen-tlm.dir/build

docs/CMakeFiles/doxygen-tlm.dir/clean:
	cd /home/f21538/systemc-2.3.3/objdir/docs && $(CMAKE_COMMAND) -P CMakeFiles/doxygen-tlm.dir/cmake_clean.cmake
.PHONY : docs/CMakeFiles/doxygen-tlm.dir/clean

docs/CMakeFiles/doxygen-tlm.dir/depend:
	cd /home/f21538/systemc-2.3.3/objdir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/f21538/systemc-2.3.3 /home/f21538/systemc-2.3.3/docs /home/f21538/systemc-2.3.3/objdir /home/f21538/systemc-2.3.3/objdir/docs /home/f21538/systemc-2.3.3/objdir/docs/CMakeFiles/doxygen-tlm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/CMakeFiles/doxygen-tlm.dir/depend


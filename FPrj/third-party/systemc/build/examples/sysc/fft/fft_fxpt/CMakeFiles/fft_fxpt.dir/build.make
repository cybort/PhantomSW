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
include examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/depend.make

# Include the progress variables for this target.
include examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/flags.make

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.o: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/flags.make
examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.o: ../examples/sysc/fft/fft_fxpt/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.o"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fft_fxpt.dir/main.cpp.o -c /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/main.cpp

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_fxpt.dir/main.cpp.i"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/main.cpp > CMakeFiles/fft_fxpt.dir/main.cpp.i

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_fxpt.dir/main.cpp.s"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/main.cpp -o CMakeFiles/fft_fxpt.dir/main.cpp.s

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.o: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/flags.make
examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.o: ../examples/sysc/fft/fft_fxpt/source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.o"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fft_fxpt.dir/source.cpp.o -c /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/source.cpp

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_fxpt.dir/source.cpp.i"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/source.cpp > CMakeFiles/fft_fxpt.dir/source.cpp.i

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_fxpt.dir/source.cpp.s"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/source.cpp -o CMakeFiles/fft_fxpt.dir/source.cpp.s

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.o: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/flags.make
examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.o: ../examples/sysc/fft/fft_fxpt/fft.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.o"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fft_fxpt.dir/fft.cpp.o -c /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/fft.cpp

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_fxpt.dir/fft.cpp.i"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/fft.cpp > CMakeFiles/fft_fxpt.dir/fft.cpp.i

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_fxpt.dir/fft.cpp.s"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/fft.cpp -o CMakeFiles/fft_fxpt.dir/fft.cpp.s

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.o: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/flags.make
examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.o: ../examples/sysc/fft/fft_fxpt/sink.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.o"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fft_fxpt.dir/sink.cpp.o -c /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/sink.cpp

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_fxpt.dir/sink.cpp.i"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/sink.cpp > CMakeFiles/fft_fxpt.dir/sink.cpp.i

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_fxpt.dir/sink.cpp.s"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt/sink.cpp -o CMakeFiles/fft_fxpt.dir/sink.cpp.s

# Object files for target fft_fxpt
fft_fxpt_OBJECTS = \
"CMakeFiles/fft_fxpt.dir/main.cpp.o" \
"CMakeFiles/fft_fxpt.dir/source.cpp.o" \
"CMakeFiles/fft_fxpt.dir/fft.cpp.o" \
"CMakeFiles/fft_fxpt.dir/sink.cpp.o"

# External object files for target fft_fxpt
fft_fxpt_EXTERNAL_OBJECTS =

examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/main.cpp.o
examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/source.cpp.o
examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/fft.cpp.o
examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/sink.cpp.o
examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/build.make
examples/sysc/fft/fft_fxpt/fft_fxpt: src/libsystemc.a
examples/sysc/fft/fft_fxpt/fft_fxpt: examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/f21538/systemc-2.3.3/objdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable fft_fxpt"
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fft_fxpt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/build: examples/sysc/fft/fft_fxpt/fft_fxpt

.PHONY : examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/build

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/clean:
	cd /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt && $(CMAKE_COMMAND) -P CMakeFiles/fft_fxpt.dir/cmake_clean.cmake
.PHONY : examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/clean

examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/depend:
	cd /home/f21538/systemc-2.3.3/objdir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/f21538/systemc-2.3.3 /home/f21538/systemc-2.3.3/examples/sysc/fft/fft_fxpt /home/f21538/systemc-2.3.3/objdir /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt /home/f21538/systemc-2.3.3/objdir/examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sysc/fft/fft_fxpt/CMakeFiles/fft_fxpt.dir/depend


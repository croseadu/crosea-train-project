# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /local/.train/train/codeDepot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /local/.train/train/codeDepot/build

# Include any dependencies generated for this target.
include basic/basic/CMakeFiles/maze.dir/depend.make

# Include the progress variables for this target.
include basic/basic/CMakeFiles/maze.dir/progress.make

# Include the compile flags for this target's objects.
include basic/basic/CMakeFiles/maze.dir/flags.make

basic/basic/CMakeFiles/maze.dir/maze.c.o: basic/basic/CMakeFiles/maze.dir/flags.make
basic/basic/CMakeFiles/maze.dir/maze.c.o: ../basic/basic/maze.c
	$(CMAKE_COMMAND) -E cmake_progress_report /local/.train/train/codeDepot/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/basic/CMakeFiles/maze.dir/maze.c.o"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/maze.dir/maze.c.o   -c /local/.train/train/codeDepot/basic/basic/maze.c

basic/basic/CMakeFiles/maze.dir/maze.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/maze.dir/maze.c.i"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /local/.train/train/codeDepot/basic/basic/maze.c > CMakeFiles/maze.dir/maze.c.i

basic/basic/CMakeFiles/maze.dir/maze.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/maze.dir/maze.c.s"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /local/.train/train/codeDepot/basic/basic/maze.c -o CMakeFiles/maze.dir/maze.c.s

basic/basic/CMakeFiles/maze.dir/maze.c.o.requires:
.PHONY : basic/basic/CMakeFiles/maze.dir/maze.c.o.requires

basic/basic/CMakeFiles/maze.dir/maze.c.o.provides: basic/basic/CMakeFiles/maze.dir/maze.c.o.requires
	$(MAKE) -f basic/basic/CMakeFiles/maze.dir/build.make basic/basic/CMakeFiles/maze.dir/maze.c.o.provides.build
.PHONY : basic/basic/CMakeFiles/maze.dir/maze.c.o.provides

basic/basic/CMakeFiles/maze.dir/maze.c.o.provides.build: basic/basic/CMakeFiles/maze.dir/maze.c.o
.PHONY : basic/basic/CMakeFiles/maze.dir/maze.c.o.provides.build

# Object files for target maze
maze_OBJECTS = \
"CMakeFiles/maze.dir/maze.c.o"

# External object files for target maze
maze_EXTERNAL_OBJECTS =

bin/maze: basic/basic/CMakeFiles/maze.dir/maze.c.o
bin/maze: lib/libutils.a
bin/maze: basic/basic/CMakeFiles/maze.dir/build.make
bin/maze: basic/basic/CMakeFiles/maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../bin/maze"
	cd /local/.train/train/codeDepot/build/basic/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/basic/CMakeFiles/maze.dir/build: bin/maze
.PHONY : basic/basic/CMakeFiles/maze.dir/build

basic/basic/CMakeFiles/maze.dir/requires: basic/basic/CMakeFiles/maze.dir/maze.c.o.requires
.PHONY : basic/basic/CMakeFiles/maze.dir/requires

basic/basic/CMakeFiles/maze.dir/clean:
	cd /local/.train/train/codeDepot/build/basic/basic && $(CMAKE_COMMAND) -P CMakeFiles/maze.dir/cmake_clean.cmake
.PHONY : basic/basic/CMakeFiles/maze.dir/clean

basic/basic/CMakeFiles/maze.dir/depend:
	cd /local/.train/train/codeDepot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /local/.train/train/codeDepot /local/.train/train/codeDepot/basic/basic /local/.train/train/codeDepot/build /local/.train/train/codeDepot/build/basic/basic /local/.train/train/codeDepot/build/basic/basic/CMakeFiles/maze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/basic/CMakeFiles/maze.dir/depend

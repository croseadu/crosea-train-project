# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr2/yuehaid/code/train/Apollo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr2/yuehaid/code/train/Apollo/build

# Include any dependencies generated for this target.
include basic/CMakeFiles/sorting.dir/depend.make

# Include the progress variables for this target.
include basic/CMakeFiles/sorting.dir/progress.make

# Include the compile flags for this target's objects.
include basic/CMakeFiles/sorting.dir/flags.make

basic/CMakeFiles/sorting.dir/sorting.c.o: basic/CMakeFiles/sorting.dir/flags.make
basic/CMakeFiles/sorting.dir/sorting.c.o: ../basic/sorting.c
	$(CMAKE_COMMAND) -E cmake_progress_report /usr2/yuehaid/code/train/Apollo/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/CMakeFiles/sorting.dir/sorting.c.o"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/sorting.dir/sorting.c.o   -c /usr2/yuehaid/code/train/Apollo/basic/sorting.c

basic/CMakeFiles/sorting.dir/sorting.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sorting.dir/sorting.c.i"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /usr2/yuehaid/code/train/Apollo/basic/sorting.c > CMakeFiles/sorting.dir/sorting.c.i

basic/CMakeFiles/sorting.dir/sorting.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sorting.dir/sorting.c.s"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /usr2/yuehaid/code/train/Apollo/basic/sorting.c -o CMakeFiles/sorting.dir/sorting.c.s

basic/CMakeFiles/sorting.dir/sorting.c.o.requires:
.PHONY : basic/CMakeFiles/sorting.dir/sorting.c.o.requires

basic/CMakeFiles/sorting.dir/sorting.c.o.provides: basic/CMakeFiles/sorting.dir/sorting.c.o.requires
	$(MAKE) -f basic/CMakeFiles/sorting.dir/build.make basic/CMakeFiles/sorting.dir/sorting.c.o.provides.build
.PHONY : basic/CMakeFiles/sorting.dir/sorting.c.o.provides

basic/CMakeFiles/sorting.dir/sorting.c.o.provides.build: basic/CMakeFiles/sorting.dir/sorting.c.o

# Object files for target sorting
sorting_OBJECTS = \
"CMakeFiles/sorting.dir/sorting.c.o"

# External object files for target sorting
sorting_EXTERNAL_OBJECTS =

bin/sorting: basic/CMakeFiles/sorting.dir/sorting.c.o
bin/sorting: basic/CMakeFiles/sorting.dir/build.make
bin/sorting: utils/libutils.a
bin/sorting: basic/CMakeFiles/sorting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/sorting"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sorting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/CMakeFiles/sorting.dir/build: bin/sorting
.PHONY : basic/CMakeFiles/sorting.dir/build

basic/CMakeFiles/sorting.dir/requires: basic/CMakeFiles/sorting.dir/sorting.c.o.requires
.PHONY : basic/CMakeFiles/sorting.dir/requires

basic/CMakeFiles/sorting.dir/clean:
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -P CMakeFiles/sorting.dir/cmake_clean.cmake
.PHONY : basic/CMakeFiles/sorting.dir/clean

basic/CMakeFiles/sorting.dir/depend:
	cd /usr2/yuehaid/code/train/Apollo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr2/yuehaid/code/train/Apollo /usr2/yuehaid/code/train/Apollo/basic /usr2/yuehaid/code/train/Apollo/build /usr2/yuehaid/code/train/Apollo/build/basic /usr2/yuehaid/code/train/Apollo/build/basic/CMakeFiles/sorting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/CMakeFiles/sorting.dir/depend


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
include basic/CMakeFiles/queen,.dir/depend.make

# Include the progress variables for this target.
include basic/CMakeFiles/queen,.dir/progress.make

# Include the compile flags for this target's objects.
include basic/CMakeFiles/queen,.dir/flags.make

basic/CMakeFiles/queen,.dir/queen.c.o: basic/CMakeFiles/queen,.dir/flags.make
basic/CMakeFiles/queen,.dir/queen.c.o: ../basic/queen.c
	$(CMAKE_COMMAND) -E cmake_progress_report /usr2/yuehaid/code/train/Apollo/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/CMakeFiles/queen,.dir/queen.c.o"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/queen,.dir/queen.c.o   -c /usr2/yuehaid/code/train/Apollo/basic/queen.c

basic/CMakeFiles/queen,.dir/queen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/queen,.dir/queen.c.i"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /usr2/yuehaid/code/train/Apollo/basic/queen.c > CMakeFiles/queen,.dir/queen.c.i

basic/CMakeFiles/queen,.dir/queen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/queen,.dir/queen.c.s"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /usr2/yuehaid/code/train/Apollo/basic/queen.c -o CMakeFiles/queen,.dir/queen.c.s

basic/CMakeFiles/queen,.dir/queen.c.o.requires:
.PHONY : basic/CMakeFiles/queen,.dir/queen.c.o.requires

basic/CMakeFiles/queen,.dir/queen.c.o.provides: basic/CMakeFiles/queen,.dir/queen.c.o.requires
	$(MAKE) -f basic/CMakeFiles/queen,.dir/build.make basic/CMakeFiles/queen,.dir/queen.c.o.provides.build
.PHONY : basic/CMakeFiles/queen,.dir/queen.c.o.provides

basic/CMakeFiles/queen,.dir/queen.c.o.provides.build: basic/CMakeFiles/queen,.dir/queen.c.o

# Object files for target queen,
queen,_OBJECTS = \
"CMakeFiles/queen,.dir/queen.c.o"

# External object files for target queen,
queen,_EXTERNAL_OBJECTS =

bin/queen,: basic/CMakeFiles/queen,.dir/queen.c.o
bin/queen,: basic/CMakeFiles/queen,.dir/build.make
bin/queen,: utils/libutils.a
bin/queen,: basic/CMakeFiles/queen,.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/queen,"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/queen,.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/CMakeFiles/queen,.dir/build: bin/queen,
.PHONY : basic/CMakeFiles/queen,.dir/build

basic/CMakeFiles/queen,.dir/requires: basic/CMakeFiles/queen,.dir/queen.c.o.requires
.PHONY : basic/CMakeFiles/queen,.dir/requires

basic/CMakeFiles/queen,.dir/clean:
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -P CMakeFiles/queen,.dir/cmake_clean.cmake
.PHONY : basic/CMakeFiles/queen,.dir/clean

basic/CMakeFiles/queen,.dir/depend:
	cd /usr2/yuehaid/code/train/Apollo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr2/yuehaid/code/train/Apollo /usr2/yuehaid/code/train/Apollo/basic /usr2/yuehaid/code/train/Apollo/build /usr2/yuehaid/code/train/Apollo/build/basic /usr2/yuehaid/code/train/Apollo/build/basic/CMakeFiles/queen,.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/CMakeFiles/queen,.dir/depend


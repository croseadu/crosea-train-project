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
include basic/CMakeFiles/binaryTree.dir/depend.make

# Include the progress variables for this target.
include basic/CMakeFiles/binaryTree.dir/progress.make

# Include the compile flags for this target's objects.
include basic/CMakeFiles/binaryTree.dir/flags.make

basic/CMakeFiles/binaryTree.dir/binaryTree.c.o: basic/CMakeFiles/binaryTree.dir/flags.make
basic/CMakeFiles/binaryTree.dir/binaryTree.c.o: ../basic/binaryTree.c
	$(CMAKE_COMMAND) -E cmake_progress_report /usr2/yuehaid/code/train/Apollo/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/CMakeFiles/binaryTree.dir/binaryTree.c.o"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/binaryTree.dir/binaryTree.c.o   -c /usr2/yuehaid/code/train/Apollo/basic/binaryTree.c

basic/CMakeFiles/binaryTree.dir/binaryTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/binaryTree.dir/binaryTree.c.i"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /usr2/yuehaid/code/train/Apollo/basic/binaryTree.c > CMakeFiles/binaryTree.dir/binaryTree.c.i

basic/CMakeFiles/binaryTree.dir/binaryTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/binaryTree.dir/binaryTree.c.s"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /usr2/yuehaid/code/train/Apollo/basic/binaryTree.c -o CMakeFiles/binaryTree.dir/binaryTree.c.s

basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.requires:
.PHONY : basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.requires

basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.provides: basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.requires
	$(MAKE) -f basic/CMakeFiles/binaryTree.dir/build.make basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.provides.build
.PHONY : basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.provides

basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.provides.build: basic/CMakeFiles/binaryTree.dir/binaryTree.c.o

# Object files for target binaryTree
binaryTree_OBJECTS = \
"CMakeFiles/binaryTree.dir/binaryTree.c.o"

# External object files for target binaryTree
binaryTree_EXTERNAL_OBJECTS =

bin/binaryTree: basic/CMakeFiles/binaryTree.dir/binaryTree.c.o
bin/binaryTree: basic/CMakeFiles/binaryTree.dir/build.make
bin/binaryTree: utils/libutils.a
bin/binaryTree: basic/CMakeFiles/binaryTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/binaryTree"
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binaryTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/CMakeFiles/binaryTree.dir/build: bin/binaryTree
.PHONY : basic/CMakeFiles/binaryTree.dir/build

basic/CMakeFiles/binaryTree.dir/requires: basic/CMakeFiles/binaryTree.dir/binaryTree.c.o.requires
.PHONY : basic/CMakeFiles/binaryTree.dir/requires

basic/CMakeFiles/binaryTree.dir/clean:
	cd /usr2/yuehaid/code/train/Apollo/build/basic && $(CMAKE_COMMAND) -P CMakeFiles/binaryTree.dir/cmake_clean.cmake
.PHONY : basic/CMakeFiles/binaryTree.dir/clean

basic/CMakeFiles/binaryTree.dir/depend:
	cd /usr2/yuehaid/code/train/Apollo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr2/yuehaid/code/train/Apollo /usr2/yuehaid/code/train/Apollo/basic /usr2/yuehaid/code/train/Apollo/build /usr2/yuehaid/code/train/Apollo/build/basic /usr2/yuehaid/code/train/Apollo/build/basic/CMakeFiles/binaryTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/CMakeFiles/binaryTree.dir/depend

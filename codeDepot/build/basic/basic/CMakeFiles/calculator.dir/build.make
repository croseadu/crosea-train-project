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
include basic/basic/CMakeFiles/calculator.dir/depend.make

# Include the progress variables for this target.
include basic/basic/CMakeFiles/calculator.dir/progress.make

# Include the compile flags for this target's objects.
include basic/basic/CMakeFiles/calculator.dir/flags.make

basic/basic/CMakeFiles/calculator.dir/calculator.c.o: basic/basic/CMakeFiles/calculator.dir/flags.make
basic/basic/CMakeFiles/calculator.dir/calculator.c.o: ../basic/basic/calculator.c
	$(CMAKE_COMMAND) -E cmake_progress_report /local/.train/train/codeDepot/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/basic/CMakeFiles/calculator.dir/calculator.c.o"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/calculator.dir/calculator.c.o   -c /local/.train/train/codeDepot/basic/basic/calculator.c

basic/basic/CMakeFiles/calculator.dir/calculator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/calculator.dir/calculator.c.i"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /local/.train/train/codeDepot/basic/basic/calculator.c > CMakeFiles/calculator.dir/calculator.c.i

basic/basic/CMakeFiles/calculator.dir/calculator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/calculator.dir/calculator.c.s"
	cd /local/.train/train/codeDepot/build/basic/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /local/.train/train/codeDepot/basic/basic/calculator.c -o CMakeFiles/calculator.dir/calculator.c.s

basic/basic/CMakeFiles/calculator.dir/calculator.c.o.requires:
.PHONY : basic/basic/CMakeFiles/calculator.dir/calculator.c.o.requires

basic/basic/CMakeFiles/calculator.dir/calculator.c.o.provides: basic/basic/CMakeFiles/calculator.dir/calculator.c.o.requires
	$(MAKE) -f basic/basic/CMakeFiles/calculator.dir/build.make basic/basic/CMakeFiles/calculator.dir/calculator.c.o.provides.build
.PHONY : basic/basic/CMakeFiles/calculator.dir/calculator.c.o.provides

basic/basic/CMakeFiles/calculator.dir/calculator.c.o.provides.build: basic/basic/CMakeFiles/calculator.dir/calculator.c.o
.PHONY : basic/basic/CMakeFiles/calculator.dir/calculator.c.o.provides.build

# Object files for target calculator
calculator_OBJECTS = \
"CMakeFiles/calculator.dir/calculator.c.o"

# External object files for target calculator
calculator_EXTERNAL_OBJECTS =

bin/calculator: basic/basic/CMakeFiles/calculator.dir/calculator.c.o
bin/calculator: lib/libutils.a
bin/calculator: basic/basic/CMakeFiles/calculator.dir/build.make
bin/calculator: basic/basic/CMakeFiles/calculator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../bin/calculator"
	cd /local/.train/train/codeDepot/build/basic/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calculator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/basic/CMakeFiles/calculator.dir/build: bin/calculator
.PHONY : basic/basic/CMakeFiles/calculator.dir/build

basic/basic/CMakeFiles/calculator.dir/requires: basic/basic/CMakeFiles/calculator.dir/calculator.c.o.requires
.PHONY : basic/basic/CMakeFiles/calculator.dir/requires

basic/basic/CMakeFiles/calculator.dir/clean:
	cd /local/.train/train/codeDepot/build/basic/basic && $(CMAKE_COMMAND) -P CMakeFiles/calculator.dir/cmake_clean.cmake
.PHONY : basic/basic/CMakeFiles/calculator.dir/clean

basic/basic/CMakeFiles/calculator.dir/depend:
	cd /local/.train/train/codeDepot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /local/.train/train/codeDepot /local/.train/train/codeDepot/basic/basic /local/.train/train/codeDepot/build /local/.train/train/codeDepot/build/basic/basic /local/.train/train/codeDepot/build/basic/basic/CMakeFiles/calculator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/basic/CMakeFiles/calculator.dir/depend


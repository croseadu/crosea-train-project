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
CMAKE_SOURCE_DIR = /local/.train/train/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /local/.train/train/final/build

# Include any dependencies generated for this target.
include sorting/CMakeFiles/selectionSort.dir/depend.make

# Include the progress variables for this target.
include sorting/CMakeFiles/selectionSort.dir/progress.make

# Include the compile flags for this target's objects.
include sorting/CMakeFiles/selectionSort.dir/flags.make

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o: sorting/CMakeFiles/selectionSort.dir/flags.make
sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o: ../sorting/selectionSort.c
	$(CMAKE_COMMAND) -E cmake_progress_report /local/.train/train/final/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o"
	cd /local/.train/train/final/build/sorting && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/selectionSort.dir/selectionSort.c.o   -c /local/.train/train/final/sorting/selectionSort.c

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/selectionSort.dir/selectionSort.c.i"
	cd /local/.train/train/final/build/sorting && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /local/.train/train/final/sorting/selectionSort.c > CMakeFiles/selectionSort.dir/selectionSort.c.i

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/selectionSort.dir/selectionSort.c.s"
	cd /local/.train/train/final/build/sorting && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /local/.train/train/final/sorting/selectionSort.c -o CMakeFiles/selectionSort.dir/selectionSort.c.s

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.requires:
.PHONY : sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.requires

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.provides: sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.requires
	$(MAKE) -f sorting/CMakeFiles/selectionSort.dir/build.make sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.provides.build
.PHONY : sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.provides

sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.provides.build: sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o
.PHONY : sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.provides.build

# Object files for target selectionSort
selectionSort_OBJECTS = \
"CMakeFiles/selectionSort.dir/selectionSort.c.o"

# External object files for target selectionSort
selectionSort_EXTERNAL_OBJECTS =

bin/selectionSort: sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o
bin/selectionSort: lib/libutils.a
bin/selectionSort: sorting/CMakeFiles/selectionSort.dir/build.make
bin/selectionSort: sorting/CMakeFiles/selectionSort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/selectionSort"
	cd /local/.train/train/final/build/sorting && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/selectionSort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sorting/CMakeFiles/selectionSort.dir/build: bin/selectionSort
.PHONY : sorting/CMakeFiles/selectionSort.dir/build

sorting/CMakeFiles/selectionSort.dir/requires: sorting/CMakeFiles/selectionSort.dir/selectionSort.c.o.requires
.PHONY : sorting/CMakeFiles/selectionSort.dir/requires

sorting/CMakeFiles/selectionSort.dir/clean:
	cd /local/.train/train/final/build/sorting && $(CMAKE_COMMAND) -P CMakeFiles/selectionSort.dir/cmake_clean.cmake
.PHONY : sorting/CMakeFiles/selectionSort.dir/clean

sorting/CMakeFiles/selectionSort.dir/depend:
	cd /local/.train/train/final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /local/.train/train/final /local/.train/train/final/sorting /local/.train/train/final/build /local/.train/train/final/build/sorting /local/.train/train/final/build/sorting/CMakeFiles/selectionSort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sorting/CMakeFiles/selectionSort.dir/depend


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
CMAKE_SOURCE_DIR = /local/.train/train/2016

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /local/.train/train/2016/build

# Include any dependencies generated for this target.
include basic/CMakeFiles/conversion.dir/depend.make

# Include the progress variables for this target.
include basic/CMakeFiles/conversion.dir/progress.make

# Include the compile flags for this target's objects.
include basic/CMakeFiles/conversion.dir/flags.make

basic/CMakeFiles/conversion.dir/conversion.o: basic/CMakeFiles/conversion.dir/flags.make
basic/CMakeFiles/conversion.dir/conversion.o: ../basic/conversion.c
	$(CMAKE_COMMAND) -E cmake_progress_report /local/.train/train/2016/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object basic/CMakeFiles/conversion.dir/conversion.o"
	cd /local/.train/train/2016/build/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/conversion.dir/conversion.o   -c /local/.train/train/2016/basic/conversion.c

basic/CMakeFiles/conversion.dir/conversion.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conversion.dir/conversion.i"
	cd /local/.train/train/2016/build/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /local/.train/train/2016/basic/conversion.c > CMakeFiles/conversion.dir/conversion.i

basic/CMakeFiles/conversion.dir/conversion.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conversion.dir/conversion.s"
	cd /local/.train/train/2016/build/basic && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /local/.train/train/2016/basic/conversion.c -o CMakeFiles/conversion.dir/conversion.s

basic/CMakeFiles/conversion.dir/conversion.o.requires:
.PHONY : basic/CMakeFiles/conversion.dir/conversion.o.requires

basic/CMakeFiles/conversion.dir/conversion.o.provides: basic/CMakeFiles/conversion.dir/conversion.o.requires
	$(MAKE) -f basic/CMakeFiles/conversion.dir/build.make basic/CMakeFiles/conversion.dir/conversion.o.provides.build
.PHONY : basic/CMakeFiles/conversion.dir/conversion.o.provides

basic/CMakeFiles/conversion.dir/conversion.o.provides.build: basic/CMakeFiles/conversion.dir/conversion.o
.PHONY : basic/CMakeFiles/conversion.dir/conversion.o.provides.build

# Object files for target conversion
conversion_OBJECTS = \
"CMakeFiles/conversion.dir/conversion.o"

# External object files for target conversion
conversion_EXTERNAL_OBJECTS =

bin/conversion: basic/CMakeFiles/conversion.dir/conversion.o
bin/conversion: lib/libutils.a
bin/conversion: basic/CMakeFiles/conversion.dir/build.make
bin/conversion: basic/CMakeFiles/conversion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/conversion"
	cd /local/.train/train/2016/build/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conversion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
basic/CMakeFiles/conversion.dir/build: bin/conversion
.PHONY : basic/CMakeFiles/conversion.dir/build

basic/CMakeFiles/conversion.dir/requires: basic/CMakeFiles/conversion.dir/conversion.o.requires
.PHONY : basic/CMakeFiles/conversion.dir/requires

basic/CMakeFiles/conversion.dir/clean:
	cd /local/.train/train/2016/build/basic && $(CMAKE_COMMAND) -P CMakeFiles/conversion.dir/cmake_clean.cmake
.PHONY : basic/CMakeFiles/conversion.dir/clean

basic/CMakeFiles/conversion.dir/depend:
	cd /local/.train/train/2016/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /local/.train/train/2016 /local/.train/train/2016/basic /local/.train/train/2016/build /local/.train/train/2016/build/basic /local/.train/train/2016/build/basic/CMakeFiles/conversion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : basic/CMakeFiles/conversion.dir/depend

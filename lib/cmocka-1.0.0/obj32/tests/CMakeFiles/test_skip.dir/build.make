# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_SOURCE_DIR = /home/asn/workspace/projects/cmocka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/asn/workspace/projects/cmocka/obj32

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_skip.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_skip.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_skip.dir/flags.make

tests/CMakeFiles/test_skip.dir/test_skip.c.o: tests/CMakeFiles/test_skip.dir/flags.make
tests/CMakeFiles/test_skip.dir/test_skip.c.o: ../tests/test_skip.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/asn/workspace/projects/cmocka/obj32/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/test_skip.dir/test_skip.c.o"
	cd /home/asn/workspace/projects/cmocka/obj32/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_skip.dir/test_skip.c.o   -c /home/asn/workspace/projects/cmocka/tests/test_skip.c

tests/CMakeFiles/test_skip.dir/test_skip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_skip.dir/test_skip.c.i"
	cd /home/asn/workspace/projects/cmocka/obj32/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/asn/workspace/projects/cmocka/tests/test_skip.c > CMakeFiles/test_skip.dir/test_skip.c.i

tests/CMakeFiles/test_skip.dir/test_skip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_skip.dir/test_skip.c.s"
	cd /home/asn/workspace/projects/cmocka/obj32/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/asn/workspace/projects/cmocka/tests/test_skip.c -o CMakeFiles/test_skip.dir/test_skip.c.s

tests/CMakeFiles/test_skip.dir/test_skip.c.o.requires:
.PHONY : tests/CMakeFiles/test_skip.dir/test_skip.c.o.requires

tests/CMakeFiles/test_skip.dir/test_skip.c.o.provides: tests/CMakeFiles/test_skip.dir/test_skip.c.o.requires
	$(MAKE) -f tests/CMakeFiles/test_skip.dir/build.make tests/CMakeFiles/test_skip.dir/test_skip.c.o.provides.build
.PHONY : tests/CMakeFiles/test_skip.dir/test_skip.c.o.provides

tests/CMakeFiles/test_skip.dir/test_skip.c.o.provides.build: tests/CMakeFiles/test_skip.dir/test_skip.c.o

# Object files for target test_skip
test_skip_OBJECTS = \
"CMakeFiles/test_skip.dir/test_skip.c.o"

# External object files for target test_skip
test_skip_EXTERNAL_OBJECTS =

tests/test_skip: tests/CMakeFiles/test_skip.dir/test_skip.c.o
tests/test_skip: tests/CMakeFiles/test_skip.dir/build.make
tests/test_skip: src/libcmocka.so.0.3.0
tests/test_skip: /usr/lib/librt.so
tests/test_skip: tests/CMakeFiles/test_skip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test_skip"
	cd /home/asn/workspace/projects/cmocka/obj32/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_skip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_skip.dir/build: tests/test_skip
.PHONY : tests/CMakeFiles/test_skip.dir/build

tests/CMakeFiles/test_skip.dir/requires: tests/CMakeFiles/test_skip.dir/test_skip.c.o.requires
.PHONY : tests/CMakeFiles/test_skip.dir/requires

tests/CMakeFiles/test_skip.dir/clean:
	cd /home/asn/workspace/projects/cmocka/obj32/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_skip.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_skip.dir/clean

tests/CMakeFiles/test_skip.dir/depend:
	cd /home/asn/workspace/projects/cmocka/obj32 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/asn/workspace/projects/cmocka /home/asn/workspace/projects/cmocka/tests /home/asn/workspace/projects/cmocka/obj32 /home/asn/workspace/projects/cmocka/obj32/tests /home/asn/workspace/projects/cmocka/obj32/tests/CMakeFiles/test_skip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_skip.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = "/home/autumn/CS 5721/OpenGL_Lab2-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/autumn/CS 5721/OpenGL_Lab2-master/build"

# Include any dependencies generated for this target.
include glfw-3.2.1/tests/CMakeFiles/msaa.dir/depend.make

# Include the progress variables for this target.
include glfw-3.2.1/tests/CMakeFiles/msaa.dir/progress.make

# Include the compile flags for this target's objects.
include glfw-3.2.1/tests/CMakeFiles/msaa.dir/flags.make

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o: glfw-3.2.1/tests/CMakeFiles/msaa.dir/flags.make
glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o: ../glfw-3.2.1/tests/msaa.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/OpenGL_Lab2-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msaa.dir/msaa.c.o   -c "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/tests/msaa.c"

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msaa.dir/msaa.c.i"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/tests/msaa.c" > CMakeFiles/msaa.dir/msaa.c.i

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msaa.dir/msaa.c.s"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/tests/msaa.c" -o CMakeFiles/msaa.dir/msaa.c.s

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.requires:

.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.requires

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.provides: glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.requires
	$(MAKE) -f glfw-3.2.1/tests/CMakeFiles/msaa.dir/build.make glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.provides.build
.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.provides

glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.provides.build: glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o


glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o: glfw-3.2.1/tests/CMakeFiles/msaa.dir/flags.make
glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o: ../glfw-3.2.1/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/OpenGL_Lab2-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msaa.dir/__/deps/getopt.c.o   -c "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/getopt.c"

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msaa.dir/__/deps/getopt.c.i"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/getopt.c" > CMakeFiles/msaa.dir/__/deps/getopt.c.i

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msaa.dir/__/deps/getopt.c.s"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/getopt.c" -o CMakeFiles/msaa.dir/__/deps/getopt.c.s

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.requires:

.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.requires

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.provides: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f glfw-3.2.1/tests/CMakeFiles/msaa.dir/build.make glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.provides.build
.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.provides

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.provides.build: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o


glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o: glfw-3.2.1/tests/CMakeFiles/msaa.dir/flags.make
glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o: ../glfw-3.2.1/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/OpenGL_Lab2-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/msaa.dir/__/deps/glad.c.o   -c "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/glad.c"

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/msaa.dir/__/deps/glad.c.i"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/glad.c" > CMakeFiles/msaa.dir/__/deps/glad.c.i

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/msaa.dir/__/deps/glad.c.s"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/deps/glad.c" -o CMakeFiles/msaa.dir/__/deps/glad.c.s

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.requires:

.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.requires

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.provides: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.requires
	$(MAKE) -f glfw-3.2.1/tests/CMakeFiles/msaa.dir/build.make glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.provides.build
.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.provides

glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.provides.build: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o


# Object files for target msaa
msaa_OBJECTS = \
"CMakeFiles/msaa.dir/msaa.c.o" \
"CMakeFiles/msaa.dir/__/deps/getopt.c.o" \
"CMakeFiles/msaa.dir/__/deps/glad.c.o"

# External object files for target msaa
msaa_EXTERNAL_OBJECTS =

glfw-3.2.1/tests/msaa: glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o
glfw-3.2.1/tests/msaa: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o
glfw-3.2.1/tests/msaa: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o
glfw-3.2.1/tests/msaa: glfw-3.2.1/tests/CMakeFiles/msaa.dir/build.make
glfw-3.2.1/tests/msaa: glfw-3.2.1/src/libglfw3.a
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/librt.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libm.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libX11.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libXrandr.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libXinerama.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
glfw-3.2.1/tests/msaa: /usr/lib/x86_64-linux-gnu/libXcursor.so
glfw-3.2.1/tests/msaa: glfw-3.2.1/tests/CMakeFiles/msaa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/autumn/CS 5721/OpenGL_Lab2-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable msaa"
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msaa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw-3.2.1/tests/CMakeFiles/msaa.dir/build: glfw-3.2.1/tests/msaa

.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/build

glfw-3.2.1/tests/CMakeFiles/msaa.dir/requires: glfw-3.2.1/tests/CMakeFiles/msaa.dir/msaa.c.o.requires
glfw-3.2.1/tests/CMakeFiles/msaa.dir/requires: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/getopt.c.o.requires
glfw-3.2.1/tests/CMakeFiles/msaa.dir/requires: glfw-3.2.1/tests/CMakeFiles/msaa.dir/__/deps/glad.c.o.requires

.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/requires

glfw-3.2.1/tests/CMakeFiles/msaa.dir/clean:
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" && $(CMAKE_COMMAND) -P CMakeFiles/msaa.dir/cmake_clean.cmake
.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/clean

glfw-3.2.1/tests/CMakeFiles/msaa.dir/depend:
	cd "/home/autumn/CS 5721/OpenGL_Lab2-master/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/autumn/CS 5721/OpenGL_Lab2-master" "/home/autumn/CS 5721/OpenGL_Lab2-master/glfw-3.2.1/tests" "/home/autumn/CS 5721/OpenGL_Lab2-master/build" "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests" "/home/autumn/CS 5721/OpenGL_Lab2-master/build/glfw-3.2.1/tests/CMakeFiles/msaa.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : glfw-3.2.1/tests/CMakeFiles/msaa.dir/depend


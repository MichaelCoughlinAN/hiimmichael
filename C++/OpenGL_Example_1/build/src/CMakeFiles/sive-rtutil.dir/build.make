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
CMAKE_SOURCE_DIR = "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build"

# Include any dependencies generated for this target.
include src/CMakeFiles/sive-rtutil.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/sive-rtutil.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/sive-rtutil.dir/flags.make

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o: ../src/ArgumentParsing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/ArgumentParsing.cpp"

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/ArgumentParsing.cpp" > CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.i

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/ArgumentParsing.cpp" -o CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.s

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o


src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o: ../src/handleGraphicsArgs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/handleGraphicsArgs.cpp"

src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/handleGraphicsArgs.cpp" > CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.i

src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/handleGraphicsArgs.cpp" -o CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.s

src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o


src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o: ../src/model_obj.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/model_obj.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/model_obj.cpp"

src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/model_obj.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/model_obj.cpp" > CMakeFiles/sive-rtutil.dir/model_obj.cpp.i

src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/model_obj.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/model_obj.cpp" -o CMakeFiles/sive-rtutil.dir/model_obj.cpp.s

src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o


src/CMakeFiles/sive-rtutil.dir/Random.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/Random.cpp.o: ../src/Random.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/sive-rtutil.dir/Random.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/Random.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Random.cpp"

src/CMakeFiles/sive-rtutil.dir/Random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/Random.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Random.cpp" > CMakeFiles/sive-rtutil.dir/Random.cpp.i

src/CMakeFiles/sive-rtutil.dir/Random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/Random.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Random.cpp" -o CMakeFiles/sive-rtutil.dir/Random.cpp.s

src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/Random.cpp.o


src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o: ../src/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/Timer.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Timer.cpp"

src/CMakeFiles/sive-rtutil.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/Timer.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Timer.cpp" > CMakeFiles/sive-rtutil.dir/Timer.cpp.i

src/CMakeFiles/sive-rtutil.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/Timer.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Timer.cpp" -o CMakeFiles/sive-rtutil.dir/Timer.cpp.s

src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o


src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o: ../src/Vector3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Vector3D.cpp"

src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/Vector3D.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Vector3D.cpp" > CMakeFiles/sive-rtutil.dir/Vector3D.cpp.i

src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/Vector3D.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/Vector3D.cpp" -o CMakeFiles/sive-rtutil.dir/Vector3D.cpp.s

src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o


src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o: src/CMakeFiles/sive-rtutil.dir/flags.make
src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o: ../src/XMLSceneParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o -c "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/XMLSceneParser.cpp"

src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.i"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/XMLSceneParser.cpp" > CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.i

src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.s"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src/XMLSceneParser.cpp" -o CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.s

src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.requires:

.PHONY : src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.requires

src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.provides: src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/sive-rtutil.dir/build.make src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.provides.build
.PHONY : src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.provides

src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.provides.build: src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o


# Object files for target sive-rtutil
sive__rtutil_OBJECTS = \
"CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o" \
"CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o" \
"CMakeFiles/sive-rtutil.dir/model_obj.cpp.o" \
"CMakeFiles/sive-rtutil.dir/Random.cpp.o" \
"CMakeFiles/sive-rtutil.dir/Timer.cpp.o" \
"CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o" \
"CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o"

# External object files for target sive-rtutil
sive__rtutil_EXTERNAL_OBJECTS =

src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/Random.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/build.make
src/libsive-rtutil.a: src/CMakeFiles/sive-rtutil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libsive-rtutil.a"
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/sive-rtutil.dir/cmake_clean_target.cmake
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sive-rtutil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/sive-rtutil.dir/build: src/libsive-rtutil.a

.PHONY : src/CMakeFiles/sive-rtutil.dir/build

src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/ArgumentParsing.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/handleGraphicsArgs.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/model_obj.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/Random.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/Timer.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/Vector3D.cpp.o.requires
src/CMakeFiles/sive-rtutil.dir/requires: src/CMakeFiles/sive-rtutil.dir/XMLSceneParser.cpp.o.requires

.PHONY : src/CMakeFiles/sive-rtutil.dir/requires

src/CMakeFiles/sive-rtutil.dir/clean:
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/sive-rtutil.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/sive-rtutil.dir/clean

src/CMakeFiles/sive-rtutil.dir/depend:
	cd "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master" "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/src" "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build" "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src" "/home/autumn/CS 5721/Lab 1/OpenGL_Lab1-master/build/src/CMakeFiles/sive-rtutil.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/sive-rtutil.dir/depend


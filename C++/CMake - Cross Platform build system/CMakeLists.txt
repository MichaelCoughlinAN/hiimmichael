
# The name of our project is "HELLO". CMakeLists files in this project
# can refer to the root source directory of the project as
#${HELLO_SOURCE_DIR} 
# and to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8)
project (HELLO)
# You can change the build type below. To have the Release
# build created, change Debug to Release set(CMAKE_BUILD_TYPE Debug)
# Add executable called "helloDemo" that is built from the source files
# "myClass.cpp" and "helloDemo.cpp".
add_executable (test1 class1.cpp class1.h test1_main.cpp) 

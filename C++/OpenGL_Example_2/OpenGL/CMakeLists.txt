include_directories(${CMAKE_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries (${OPENGL_LIBRARY})

include_directories(${CMAKE_SOURCE_DIR}/libcs5721/cs5721GraphicsLib/src)
link_directories(${CMAKE_BINARY_DIR}/libcs5721/cs5721GraphicsLib/src)

add_executable (glfwExample
  glfwExample.cpp
  SingleTriangle_ClipCoordinate_Scene.cpp
  GLSL.cpp GLSL.h
)
target_link_libraries (glfwExample ${GLEW_LIBRARIES})
target_link_libraries (glfwExample glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries (glfwExample ${PNG_LIBRARIES})
target_link_libraries (glfwExample z)


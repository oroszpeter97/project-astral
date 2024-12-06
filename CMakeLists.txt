cmake_minimum_required(VERSION "3.31.1")
project(ProjectAstral)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
include_directories(external/glfw)
include_directories(external/glfw/deps)
add_subdirectory(external/glm)
include_directories(external/stb)
link_directories(external/stb)

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")

set(SOURCE_FILES src/main.cpp src/Shader.cpp)

add_executable(ProjectAstral ${SOURCE_FILES} ${GLAD})

target_link_libraries(ProjectAstral glfw glm)
target_include_directories(ProjectAstral PUBLIC ${CMAKE_SOURCE_DIR}/include)
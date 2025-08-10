cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(house VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DRESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/res/")
add_definitions(-DGLEW_STATIC)

include_directories(${CMAKE_SOURCE_DIR}/core/include)

include_directories("$ENV{GLM}/include")
include_directories("$ENV{GLFW}/include")
include_directories("$ENV{GLEW}/include")

link_directories("$ENV{GLFW}/lib")
link_directories("$ENV{GLEW}/lib")
link_directories("${CMAKE_BINARY_DIR}/core")

link_libraries(glfw3)
link_libraries(devCored)
link_libraries(glew32.a)
link_libraries(opengl32)
link_libraries(glu32)

add_executable(${PROJECT_NAME} src/house.cpp)
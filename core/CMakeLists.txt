cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devCore VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DGLEW_STATIC)

include_directories("include/core")
include_directories("$ENV{GLEW}/include")

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

        PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
        DEBUG_POSTFIX "d"
)

target_sources(${PROJECT_NAME} PRIVATE src/vao.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/initialization.cpp)

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES
        include/core/vao.h
        include/core/type.h
        include/core/error.h
        include/core/initialization.h
)

set(INSTALL_TARGET_FILES
        ${PROJECT_NAME}
)

include("${CMAKE_SOURCE_DIR}/config/install.cmake")
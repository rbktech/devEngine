cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devGraph VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DGLEW_STATIC)

include_directories("include/graph")
include_directories("${CMAKE_SOURCE_DIR}/core/include")

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

        PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
        DEBUG_POSTFIX "d"
)

target_sources(${PROJECT_NAME} PRIVATE src/graph.cpp)

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES
        include/graph/graph.h
)

set(INSTALL_TARGET_FILES
        ${PROJECT_NAME}
)

include("${CMAKE_SOURCE_DIR}/config/install.cmake")
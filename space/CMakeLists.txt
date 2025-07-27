cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devSpace VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")

include_directories("include")

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

        PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
        DEBUG_POSTFIX "d"
)

target_sources(${PROJECT_NAME} PRIVATE src/library.cpp)

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES
        include/space/library.h
)

set(INSTALL_TARGET_FILES
        ${PROJECT_NAME}
)

get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY )

if(${CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    include("${CMAKE_SOURCE_DIR}/config/install.cmake")
endif()
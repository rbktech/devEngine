cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devGraph VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DRESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/res/")
add_definitions(-DGLEW_STATIC)

include_directories("include")
include_directories("$ENV{GLM}/include")
include_directories("${CMAKE_SOURCE_DIR}/core/include")

# ------------------------------------------------------------------------

list(APPEND LIST_IN_RESOURCES "shaders/pos3col3.vert")
list(APPEND LIST_IN_RESOURCES "shaders/pos3col3.frag")
list(APPEND LIST_IN_RESOURCES "vertex/cursor.xyz")
list(APPEND LIST_IN_RESOURCES "vertex/cursor.rgb")
list(APPEND LIST_IN_RESOURCES "vertex/coordinate.xyz")
list(APPEND LIST_IN_RESOURCES "vertex/coordinate.rgb")

foreach(resource ${LIST_IN_RESOURCES})
    string(REGEX REPLACE "[:/\\]" "." name ${resource})

    set(IN ${CMAKE_CURRENT_SOURCE_DIR}/res/${resource})
    set(OUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.obj)

    string(REGEX REPLACE "[:/\\.]" "_" IN_BINARY_NAME ${IN})
    string(REGEX REPLACE "[:/\\.]" "_" OUT_BINARY_NAME ${name})

    # message("IN: ${IN}")
    # message("OUT: ${OUT}")

    # message("IN_BINARY_NAME ${IN_BINARY_NAME}")
    # message("OUT_BINARY_NAME: ${OUT_BINARY_NAME}")

    add_custom_command (
            OUTPUT  ${OUT}
            COMMAND objcopy --input-target binary --output-target elf64-x86-64 --binary-architecture i386:x86-64 ${IN} ${OUT}
            COMMAND objcopy --redefine-sym _binary_${IN_BINARY_NAME}_start=binary_${OUT_BINARY_NAME}_start ${OUT} ${OUT}
            COMMAND objcopy --redefine-sym _binary_${IN_BINARY_NAME}_end=binary_${OUT_BINARY_NAME}_end ${OUT} ${OUT}
            COMMAND objcopy --redefine-sym _binary_${IN_BINARY_NAME}_size=binary_${OUT_BINARY_NAME}_size ${OUT} ${OUT}
    )

    list(APPEND LIST_OUT_RESOURCES ${OUT})
endforeach()

# ------------------------------------------------------------------------

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

        PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
        DEBUG_POSTFIX "d"
)

target_sources(${PROJECT_NAME} PRIVATE src/graph.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${LIST_OUT_RESOURCES})

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES
        include/graph/graph.h
)

set(INSTALL_TARGET_FILES
        ${PROJECT_NAME}
)

get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

if(${CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    include("${CMAKE_SOURCE_DIR}/config/install.cmake")
endif()

# ------------------------------------------------------------------------
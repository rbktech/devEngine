cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devCore VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CORE devCore)
set(LEGACY devLegacy)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DGLEW_STATIC)

include_directories("include")
include_directories("$ENV{GLM}/include")
include_directories("$ENV{GLEW}/include")

add_library(${CORE})

set_target_properties(${CORE}

        PROPERTIES OUTPUT_NAME "devCore"
        DEBUG_POSTFIX "d"
)

target_sources(${CORE} PRIVATE src/resources.cpp)
target_sources(${CORE} PRIVATE src/variable.cpp)
target_sources(${CORE} PRIVATE src/core.cpp)
target_sources(${CORE} PRIVATE src/initialization.cpp)
target_sources(${CORE} PRIVATE src/mash.cpp)
target_sources(${CORE} PRIVATE src/error.cpp)
target_sources(${CORE} PRIVATE src/matrixglm.cpp)

target_sources(${CORE} PRIVATE src/object/bbo.cpp)
target_sources(${CORE} PRIVATE src/object/buffer.cpp)
target_sources(${CORE} PRIVATE src/object/camera.cpp)
target_sources(${CORE} PRIVATE src/object/cbo.cpp)
target_sources(${CORE} PRIVATE src/object/draw.cpp)
target_sources(${CORE} PRIVATE src/object/ebo.cpp)
target_sources(${CORE} PRIVATE src/object/fbo.cpp)
target_sources(${CORE} PRIVATE src/object/matrix.cpp)
target_sources(${CORE} PRIVATE src/object/orthographic.cpp)
target_sources(${CORE} PRIVATE src/object/perspective.cpp)
target_sources(${CORE} PRIVATE src/object/rbo.cpp)
target_sources(${CORE} PRIVATE src/object/rotate.cpp)
target_sources(${CORE} PRIVATE src/object/scale.cpp)
target_sources(${CORE} PRIVATE src/object/shader.cpp)
target_sources(${CORE} PRIVATE src/object/tbo.cpp)
target_sources(${CORE} PRIVATE src/object/texture.cpp)
target_sources(${CORE} PRIVATE src/object/translate.cpp)
target_sources(${CORE} PRIVATE src/object/vao.cpp)
target_sources(${CORE} PRIVATE src/object/vbo.cpp)

add_library(${LEGACY})

set_target_properties(${LEGACY}

        PROPERTIES OUTPUT_NAME "devLegacy"
        DEBUG_POSTFIX "d"
)

target_sources(${LEGACY} PRIVATE src/object/legacy/cbo.cpp)
target_sources(${LEGACY} PRIVATE src/object/legacy/matrix.cpp)
target_sources(${LEGACY} PRIVATE src/object/legacy/tbo.cpp)
target_sources(${LEGACY} PRIVATE src/object/legacy/translate.cpp)
target_sources(${LEGACY} PRIVATE src/object/legacy/vao.cpp)
target_sources(${LEGACY} PRIVATE src/object/legacy/vbo.cpp)

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES

        include/core/core.h
        include/core/error.h
        include/core/initialization.h
        include/core/mash.h
        include/core/matrixglm.h
        include/core/object/bbo.h
        include/core/object/bitmap.h
        include/core/object/buffer.h
        include/core/object/camera.h
        include/core/object/cbo.h
        include/core/object/draw.h
        include/core/object/ebo.h
        include/core/object/fbo.h
        include/core/object/matrix.h
        include/core/object/orthographic.h
        include/core/object/perspective.h
        include/core/object/rbo.h
        include/core/object/rotate.h
        include/core/object/scale.h
        include/core/object/shader.h
        include/core/object/tbo.h
        include/core/object/texture.h
        include/core/object/translate.h
        include/core/object/vao.h
        include/core/object/vbo.h
        include/core/resources.h
        include/core/type.h
        include/core/variable.h
)

set(INSTALL_TARGET_FILES
        ${CORE}
        ${LEGACY}
)

get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

if (${CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    include("${CMAKE_SOURCE_DIR}/config/install.cmake")
endif ()
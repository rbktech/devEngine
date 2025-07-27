cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devCore VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# ------------------------------------------------------------------------

add_definitions(-DVERSION="${PROJECT_VERSION}")
add_definitions(-DGLEW_STATIC)

include_directories("include")
include_directories("$ENV{GLM}/include")
include_directories("$ENV{GLEW}/include")

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}

        PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
        DEBUG_POSTFIX "d"
)

target_sources(${PROJECT_NAME} PRIVATE src/initialization.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/resources.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/matrixglm.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/variable.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/mash.cpp)

target_sources(${PROJECT_NAME} PRIVATE src/object/shader.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/bbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/texture.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/buffer.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/draw.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/rotate.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/perspective.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/orthographic.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/vao.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/ebo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/fbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/rbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/vbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/tbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/vbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/cbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/tbo.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/translate.cpp)
target_sources(${PROJECT_NAME} PRIVATE src/object/matrix.cpp)

# ------------------------------------------------------------------------

set(INSTALL_HEADER_FILES

        include/core/context.h
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
        ${PROJECT_NAME}
)

get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

if (${CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    include("${CMAKE_SOURCE_DIR}/config/install.cmake")
endif ()

# ------------------------------------------------------------------------

#[[string(REGEX REPLACE "[:/\\]" "_" D_NAME ${CMAKE_SOURCE_DIR})

foreach(shader ${LIST_SHADERS})
    string(REPLACE "." "_" name ${shader})

    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/${name}.obj
            COMMAND objcopy --input-target binary --output-target elf64-x86-64 --binary-architecture i386:x86-64 ${CMAKE_SOURCE_DIR}/res/${shader} ${CMAKE_BINARY_DIR}/${name}.obj

            COMMAND objcopy --redefine-sym _binary_${D_NAME}_res_${name}_start=binary_res_${name}_start  ${CMAKE_BINARY_DIR}/${name}.obj ${CMAKE_BINARY_DIR}/${name}.obj
            COMMAND objcopy --redefine-sym _binary_${D_NAME}_res_${name}_end=binary_res_${name}_end  ${CMAKE_BINARY_DIR}/${name}.obj ${CMAKE_BINARY_DIR}/${name}.obj
            COMMAND objcopy --redefine-sym _binary_${D_NAME}_res_${name}_size=binary_res_${name}_size  ${CMAKE_BINARY_DIR}/${name}.obj ${CMAKE_BINARY_DIR}/${name}.obj
    )

    list(APPEND OBJS ${CMAKE_BINARY_DIR}/${name}.obj)
endforeach()]]

# ------------------------------------------------------------------------
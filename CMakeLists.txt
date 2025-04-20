cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(devEngine VERSION ${VERSION})

add_subdirectory(core)
add_subdirectory(graph)
add_subdirectory(plot)
add_subdirectory(space)
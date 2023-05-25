cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "Resources")

file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
        ${inc}
        ${src})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Resources")


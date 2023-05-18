cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "Components")

#find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
        ${inc}
        ${src})


target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")


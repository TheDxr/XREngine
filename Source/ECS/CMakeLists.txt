cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "ECS")


file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
        ${inc}
        ${src})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR}/ECS)
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR}/Resources)

target_link_libraries(${PROJECT_NAME} PRIVATE Resources)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "ECS")


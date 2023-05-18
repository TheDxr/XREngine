cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "Core")

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)


file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
            ${inc}
            ${src})


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")

target_link_libraries(${PROJECT_NAME} PUBLIC
                      glfw
                      glad::glad
                      spdlog::spdlog
                      )
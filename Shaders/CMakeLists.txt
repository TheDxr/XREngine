cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "Shaders")

file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.frag)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.vert)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_custom_target(${PROJECT_NAME} ALL SOURCES ${inc} ${src} DEPENDS ${inc} ${src})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "App")

add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND}
            -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
        COMMENT "Copying shaders to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders")

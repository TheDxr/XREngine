cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "OpenGLEngine")

#add_definitions(-DGLFW_INCLUDE_NONE)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)


file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
            ${inc}
            ${src})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")

target_include_directories(${PROJECT_NAME} PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR}/Engine/OpenGL)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR}/Resources)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR}/ECS)


target_link_libraries(${PROJECT_NAME} PUBLIC ECS)
target_link_libraries(${PROJECT_NAME} PUBLIC Resources)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)

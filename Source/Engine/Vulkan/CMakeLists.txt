cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "VulkanEngine")

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)


file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})

add_library(${PROJECT_NAME} STATIC
        ${inc}
        ${src})


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")

target_include_directories(${PROJECT_NAME} PUBLIC ${VULKAN_SDK_DIR}/Include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SPDLOG_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR}/Resources)
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR}/Engine/Vulkan)

target_link_directories(${PROJECT_NAME} PUBLIC "${VULKAN_SDK_DIR}/Lib")
target_link_libraries(${PROJECT_NAME} PUBLIC vulkan-1)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE Resources)
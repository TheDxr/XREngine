cmake_minimum_required(VERSION 3.22)
project(OpenGL LANGUAGES C CXX)
# Group CMakePredefinedTargets into a folder filter
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Lib") # Output directory for static lib (.lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Bin") # Output directory for shared lib (.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Bin") # Output directory for executables (.exe)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 编译器不满足C++17标准就报错
set(CMAKE_CXX_EXTENSIONS OFF) # 关闭gun的特性防止msvc出错
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(DEP_DIR "${PROJECT_SOURCE_DIR}/Dependencies")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Source")
set(SHADER_DIR "${PROJECT_SOURCE_DIR}/Shaders")
set(COMMON_DIR "${PROJECT_SOURCE_DIR}/Source/App/Common")
set(CORE_DIR "${PROJECT_SOURCE_DIR}/Source/Engine/Core")
set(COMPONENT_DIR "${PROJECT_SOURCE_DIR}/Source/Engine/Components")

#set(GLFW_INCLUDE_DIR "D:/Program Files/vcpkg/packages/glfw3_x64-windows/include")
#set(GLAD_INCLUDE_DIR "D:/Program Files/vcpkg/packages/glad_x64-windows/include"
#        "D:/Program Files/vcpkg/packages/egl-registry_x64-windows/include")
set(GLM_INCLUDE_DIR "D:/Program Files/vcpkg/packages/glm_x64-windows/include")
#set(SPDLOG_INCLUDE_DIR "D:/Program Files/vcpkg/packages/spdlog_x64-windows/include")
#set(ASSIMP_INCLUDE_DIR "D:/Program Files/vcpkg/packages/assimp_x64-windows/include")
#set(FMT_INCLUDE_DIR "D:/Program Files/vcpkg/packages/fmt_x64-windows/include")

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-D_DEBUG)

add_subdirectory(Source)
add_subdirectory(Shaders)




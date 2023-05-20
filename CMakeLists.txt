cmake_minimum_required(VERSION 3.22)
project(Dxr3DEngine LANGUAGES C CXX)
# Group CMakePredefinedTargets into a folder filter
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Lib") # Output directory for static lib (.lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Bin") # Output directory for shared lib (.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Bin") # Output directory for executables (.exe)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 编译器不满足C++17标准就报错
set(CMAKE_CXX_EXTENSIONS OFF) # 关闭gun的特性防止msvc出错
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
#if(MSVC)
#set(CMAKE_CXX_FLAGS_DEBUG "/Zc:nrvo") # 优化返回值优化
#endif(MSVC)
set(DEP_DIR "${PROJECT_SOURCE_DIR}/Dependencies")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Source")
set(SHADER_DIR "${PROJECT_SOURCE_DIR}/Shaders")
set(ENGINE_DIR "${PROJECT_SOURCE_DIR}/Source/Engine")

#set(CMAKE_CXX_FLAGS_DEBUG "/O2")
set(GLM_INCLUDE_DIR "D:/Program Files/vcpkg/packages/glm_x64-windows/include")
set(SPDLOG_INCLUDE_DIR ${DEP_DIR}/spdlog/include)
set(IMGUI_INCLUDE_DIR  "D:/ProgramData/imgui-1.89.5"
        "D:/ProgramData/imgui-1.89.5/backends")
set(VULKAN_SDK_DIR D:/VulkanSDK/1.3.216.0)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-D_DEBUG)


add_subdirectory(Source)
add_subdirectory(Shaders)




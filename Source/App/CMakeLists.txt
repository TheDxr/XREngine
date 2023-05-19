cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME Application)


find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(rapidjson CONFIG REQUIRED)

set(Main "main.cpp")

set(deps
    ${DEP_DIR}/glad.c
    ${DEP_DIR}/imgui.cpp
    ${DEP_DIR}/imgui_demo.cpp
    ${DEP_DIR}/imgui_draw.cpp
    ${DEP_DIR}/imgui_impl_glfw.cpp
    ${DEP_DIR}/imgui_impl_opengl3.cpp
    ${DEP_DIR}/imgui_tables.cpp
    ${DEP_DIR}/imgui_widgets.cpp
    ${DEP_DIR}/stb_image.h)

file(GLOB_RECURSE inc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#file(GLOB_RECURSE inc App/UI/*.h
#        App/Common/*.h
#        DxrApplication.h)
#file(GLOB_RECURSE src App/UI/*.cpp
#        App/Common/*.cpp
#        DxrApplication.cpp
#        main.cpp)

#add_dependencies(${PROJECTNAME} Cored)
#add_dependencies(${PROJECTNAME} Common)
set(AllFile ${src})
# 对 AllFile 变量里面的所有文件分类(保留资源管理器的目录结构)
#foreach(fileItem ${AllFile})
#    message(${fileItem})
#endforeach ()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${inc})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${deps})

add_executable(${PROJECT_NAME} ${Main} ${src} ${inc} ${deps})
#add_dependencies(${PROJECT_NAME} Shaders)

target_include_directories(${PROJECT_NAME} PUBLIC "D:/ProgramData/imgui-1.89.5")
target_include_directories(${PROJECT_NAME} PUBLIC "D:/ProgramData/imgui-1.89.5/backends")

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_CORE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${COMPONENT_DIR})

#target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGLCore)
#target_link_libraries(${PROJECT_NAME} PRIVATE Common)
target_link_libraries(${PROJECT_NAME} PRIVATE Components)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "App")

if ( MSVC )
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Output/Lib" )
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Output/Bin" )
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Output/Bin" )
    # etc for the other available configuration types (MinSizeRel, RelWithDebInfo)
endif ( MSVC )

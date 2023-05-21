cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "Shaders")

file(GLOB_RECURSE frag ${CMAKE_CURRENT_SOURCE_DIR}/*.frag)
file(GLOB_RECURSE vert ${CMAKE_CURRENT_SOURCE_DIR}/*.vert)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${vert})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${frag})

add_custom_target(${PROJECT_NAME} ALL SOURCES ${vert} ${frag} DEPENDS ${vert} ${frag})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "App")


add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND}
        -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
        COMMENT "Copying shaders to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders \n")

foreach (file ${frag})
    if (${file} MATCHES "vulkan.frag")
        get_filename_component(filename ${file} NAME)
        add_custom_command(
                TARGET ${PROJECT_NAME}
                COMMAND glslc ${file} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/${filename}.spv
                COMMENT "Compiling ${filename} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/${filename}.spv \n"
        )
    endif ()
endforeach ()

foreach (file ${vert})
    if (${file} MATCHES "vulkan.vert")
        get_filename_component(filename ${file} NAME)
        add_custom_command(
                TARGET ${PROJECT_NAME}
                COMMAND glslc ${file} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/${filename}.spv
                COMMENT "Compiling ${filename} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/${filename}.spv \n"
        )
    endif ()
endforeach ()



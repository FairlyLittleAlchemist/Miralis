cmake_minimum_required(VERSION 3.21)
project(Miralis LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)



set(OUT_BASE "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-x64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUT_BASE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_BASE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUT_BASE}")
set(GLFW_BUILD_X11 ON)
set(GLFW_BUILD_WAYLAND ON)
add_subdirectory(Miralis/vendor/GLFW)
add_subdirectory(Miralis/vendor/GLM)
add_subdirectory(Miralis/vendor/spdlog)
add_subdirectory(cmake/imgui)

find_package(Vulkan REQUIRED)

add_subdirectory(Miralis)
add_subdirectory(SandBox)

if(TARGET glfw)
    set_target_properties(glfw PROPERTIES FOLDER "Vendor")
endif()
if(TARGET glm)
    set_target_properties(glm PROPERTIES FOLDER "Vendor")
endif()
if(TARGET spdlog)
    set_target_properties(spdlog PROPERTIES FOLDER "Vendor")
endif()
if(TARGET ImGui)
    set_target_properties(ImGui PROPERTIES FOLDER "Vendor")
endif()

set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT Sandbox)

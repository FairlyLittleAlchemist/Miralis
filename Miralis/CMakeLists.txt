
add_library(Miralis STATIC "")


file(GLOB_RECURSE MIRALIS_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.frag"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.comp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/ImGUI/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/ImGUI/*.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/Vulkan/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/Vulkan/*.h"      # add this
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/Vulkan/*.cpp"    # add this

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Miralis/*.geom"
)


if(UNIX)
    file(GLOB_RECURSE PLATFORM_SOURCES CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/Lunix/*.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Platfrom/Lunix/*.cpp"
    )
    list(APPEND MIRALIS_SOURCES ${PLATFORM_SOURCES})
endif()

if(WIN32)
    file(GLOB_RECURSE PLATFORM_SOURCES CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Windows/*.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Windows/*.cpp"
    )
    list(APPEND MIRALIS_SOURCES ${PLATFORM_SOURCES})
endif()
target_sources(Miralis PRIVATE ${MIRALIS_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${MIRALIS_SOURCES})

target_include_directories(Miralis
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/Miralis/vendor/VulkanMemoryAllocator/include"
)

target_link_libraries(Miralis
    PUBLIC
        glfw
        ImGui
        glm::glm
        spdlog::spdlog
        Vulkan::Vulkan
)

target_compile_definitions(Miralis
    PUBLIC
        $<$<PLATFORM_ID:Windows>:MR_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:MR_PLATFORM_LINUX>
        $<$<CONFIG:Debug>:MR_DEBUG;MR_ENABLE_ASSERT;FMT_USE_OSTREAM>
        $<$<CONFIG:Release>:MR_RELEASE>
)
if(WIN32)
    add_custom_target(MiralisShaders
            COMMAND cmd /c "compile.bat <NUL"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            COMMENT "Compiling shaders"
            VERBATIM
    )
elseif(UNIX)
    add_custom_target(MiralisShaders
            COMMAND bash compile.sh
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            COMMENT "Compiling shaders"
            VERBATIM
    )
endif()

set_target_properties(MiralisShaders PROPERTIES FOLDER "Build")
add_dependencies(Miralis MiralisShaders)

target_compile_definitions(Miralis
        PUBLIC
        SHADER_PATH="${CMAKE_SOURCE_DIR}/Miralis/src/Miralis/Shaders/Compiled"
)

message(STATUS "Miralis sources: ${MIRALIS_SOURCES}")
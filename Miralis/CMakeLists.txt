add_library(Miralis STATIC)

file(GLOB_RECURSE MIRALIS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.frag"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.comp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.geom"
)

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
        MR_PLATFORM_WINDOWS
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
    set_target_properties(MiralisShaders PROPERTIES FOLDER "Build")
    add_dependencies(Miralis MiralisShaders)
endif()

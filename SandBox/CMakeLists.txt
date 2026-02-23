add_executable(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(Sandbox PRIVATE ${SANDBOX_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${SANDBOX_SOURCES})

target_include_directories(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/Miralis/src")
target_link_libraries(Sandbox PRIVATE Miralis)

target_compile_definitions(Sandbox
    PRIVATE
        MR_PLATFORM_WINDOWS
        $<$<CONFIG:Debug>:MR_DEBUG;MR_ENABLE_ASSERT;FMT_USE_OSTREAM;SPDLOG_COMPILED_LIB>
        $<$<CONFIG:Release>:MR_RELEASE>
)

if(MSVC)
    target_compile_options(Sandbox PRIVATE "/utf-8")
endif()

if(WIN32)
    set_target_properties(Sandbox PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/SandBox"
    )
endif()

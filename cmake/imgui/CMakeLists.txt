add_library(ImGui STATIC
    "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui/imgui_widgets.cpp"
)

target_include_directories(ImGui
    PUBLIC
        "${CMAKE_SOURCE_DIR}/Miralis/vendor/imgui"
)

target_compile_features(ImGui PUBLIC cxx_std_17)
if(MSVC)
    target_compile_options(ImGui PRIVATE "/utf-8")
endif()

add_library(ImGui::ImGui ALIAS ImGui)

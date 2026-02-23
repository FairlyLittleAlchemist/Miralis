project "ImGui"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "../../Miralis/vendor/imgui/imconfig.h",
        "../../Miralis/vendor/imgui/imgui.h",
        "../../Miralis/vendor/imgui/imgui.cpp",
        "../../Miralis/vendor/imgui/imgui_draw.cpp",
        "../../Miralis/vendor/imgui/imgui_internal.h",
        "../../Miralis/vendor/imgui/imgui_tables.cpp",
        "../../Miralis/vendor/imgui/imgui_widgets.cpp",
        "../../Miralis/vendor/imgui/imstb_rectpack.h",
        "../../Miralis/vendor/imgui/imstb_textedit.h",
        "../../Miralis/vendor/imgui/imstb_truetype.h",
        "../../Miralis/vendor/imgui/imgui_demo.cpp"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

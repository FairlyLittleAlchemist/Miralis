project "GLFW"
    kind "StaticLib"
    language "C"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "../../Miralis/vendor/GLFW/include/GLFW/glfw3.h",
        "../../Miralis/vendor/GLFW/include/GLFW/glfw3native.h",
        "../../Miralis/vendor/GLFW/src/glfw_config.h",
        "../../Miralis/vendor/GLFW/src/context.c",
        "../../Miralis/vendor/GLFW/src/init.c",
        "../../Miralis/vendor/GLFW/src/input.c",
        "../../Miralis/vendor/GLFW/src/monitor.c",
        "../../Miralis/vendor/GLFW/src/vulkan.c",
        "../../Miralis/vendor/GLFW/src/window.c",
        "../../Miralis/vendor/GLFW/src/platform.c",
        "../../Miralis/vendor/GLFW/src/null_joystick.c"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        
        files
        {
            "../../Miralis/vendor/GLFW/src/platform.c",
            "../../Miralis/vendor/GLFW/src/null_init.c",
            "../../Miralis/vendor/GLFW/src/null_monitor.c",
            "../../Miralis/vendor/GLFW/src/null_window.c",
            "../../Miralis/vendor/GLFW/src/null_joystick.c",

            "../../Miralis/vendor/GLFW/src/win32_init.c",
            "../../Miralis/vendor/GLFW/src/win32_joystick.c",
            "../../Miralis/vendor/GLFW/src/win32_monitor.c",
            "../../Miralis/vendor/GLFW/src/win32_time.c",
            "../../Miralis/vendor/GLFW/src/win32_thread.c",
            "../../Miralis/vendor/GLFW/src/win32_window.c",
            "../../Miralis/vendor/GLFW/src/wgl_context.c",
            "../../Miralis/vendor/GLFW/src/egl_context.c",
            "../../Miralis/vendor/GLFW/src/osmesa_context.c",
            "../../Miralis/vendor/GLFW/src/win32_module.c"
        }

        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

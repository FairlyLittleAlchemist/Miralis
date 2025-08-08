workspace "Miralis"
   	architecture "x64"
      configurations
	   {
		"Debug",
		"Release"
	   }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includedir ={}
includedir["GLFW"] = "Miralis/vendor/GLFW/include"
includedir["Vulkan"] = "$(VULKAN_SDK)/Include"
includedir["ImGui"] = "Miralis/vendor/imgui"
includedir["spdlog"] = "Miralis/vendor/spdlog/include"

include "Miralis/vendor/GLFW"
include "Miralis/vendor/imgui"

project "Miralis"
      location "Miralis"
      kind "StaticLib"
	  language "C++"
	  cppdialect "C++17"
	  staticruntime "on"

      
   	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
      
   	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.frag",
		"%{prj.name}/src/**.vert",
		"%{prj.name}/src/**.comp",
		"%{prj.name}/src/**.geom"

	}
	externalincludedirs
	{
		"%{prj.name}/src",
		includedir["GLFW"],
		includedir["spdlog"],
		includedir["Vulkan"],
		includedir["ImGui"]
	}
	libdirs { "$(VULKAN_SDK)/Lib" }
	links
	{
		"GLFW",
		"vulkan-1" ,
		"ImGui"
	}

   filter "system:windows"
   staticruntime "On"
   systemversion "latest"
   prebuildcommands {
       "cd %{wks.location} && compile.bat"
   }


   defines
   {
      "MR_PLATFORM_WINDOWS",
   }

   filter "configurations:Debug"
   defines {"MR_DEBUG","MR_ENABLE_ASSERT","FMT_USE_OSTREAM" }
   symbols "On"

	filter "configurations:Release"
   defines "MR_RELEASE"
   optimize "On"




   project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	  staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


   files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	    
    includedirs  
    {
        "Miralis/src"
    }
    
	externalincludedirs
	{
		includedir["spdlog"],
	}

	links
	{
		"Miralis"
	}

   filter "system:windows"
		systemversion "latest"

		defines
		{
			"MR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
	defines {"MR_DEBUG","MR_ENABLE_ASSERT","FMT_USE_OSTREAM" ,  "SPDLOG_COMPILED_LIB" }
	symbols "On"

	filter "configurations:Release"
		defines "MR_RELEASE"
		optimize "On"

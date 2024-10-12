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
include "Miralis/vendor/GLFW"
project "Miralis"
      location "Miralis"
      kind "SharedLib"
	  language "C++"

      
   	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
      
   	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	externalincludedirs
	{
		"%{prj.name}/src",
		includedir["GLFW"],
		"%{prj.name}/vendor/spdlog/include",
		includedir["Vulkan"],
	}

	libdirs { "$(VULKAN_SDK)/Lib" }
	links
	{
		"GLFW",
		"opengl32"  ,
		"vulkan-1" 
	}

   filter "system:windows"
   cppdialect "C++17"
   staticruntime "On"
   systemversion "latest"

   defines
   {
      "MR_PLATFORM_WINDOWS",
      "MR_BUILD_DLL"
   }

   postbuildcommands
   {
      ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


   files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	externalincludedirs
	{
	"Miralis/vendor/spdlog/include",
	"Miralis/src"
	}
	links
	{
		"Miralis"
	}


   filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
	defines {"MR_DEBUG","MR_ENABLE_ASSERT","FMT_USE_OSTREAM" }
	symbols "On"

	filter "configurations:Release"
		defines "MR_RELEASE"
		optimize "On"

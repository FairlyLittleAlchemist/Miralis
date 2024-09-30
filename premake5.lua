workspace "Miralis"
   	architecture "x64"
      configurations
	   {
		"Debug",
		"Release"
	   }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["spdlog"] = "Miralis/vendor/spdlog"
project "Miralis"
      location "Miralis"
      kind "SharedLib"
      
   	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
      
   	files
	   {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	   }


      
	includedirs
	{
		"%{prj.name}/src",
      "%{IncludeDir.spdlog}"
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
   defines "MR_DEBUG"
   buildoptions "/MDd"
   symbols "On"

filter "configurations:Release"
   defines "MR_RELEASE"
   buildoptions "/MD"
   optimize "On"

filter "configurations:Dist"
   defines "MR_DIST"
   buildoptions "/MD"
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

	includedirs
	{
		"Miralis/src",
      "%{IncludeDir.spdlog}"
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
		defines "MR_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MR_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MR_DIST"
		buildoptions "/MD"
		optimize "On"
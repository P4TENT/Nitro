workspace "Nitro"
	architecture "x64"
	buildoptions {"/utf-8"}
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nitro/vendor/GLFW/include"
IncludeDir["Glad"] = "Nitro/vendor/Glad/include"
IncludeDir["ImGui"] = "Nitro/vendor/imgui"
include "Nitro/vendor/GLFW"
include "Nitro/vendor/Glad"
include "Nitro/vendor/imgui"

project "Nitro"
	location "Nitro"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	pchheader "ngpch.h"
	pchsource "Nitro/src/ngpch.cpp"
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links 
	{
		"GLFW", 
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"  -- SharedLib should use dynamic runtime
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS",
			"NG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Sandbox"
		}
	filter "configurations:Debug"
		runtime "Debug"
		defines "NG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		defines "NG_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		runtime "Release"
		defines "NG_DIST"
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
		"Nitro/vendor/spdlog/include",
		"Nitro/src"
	}
	links
	{
		"Nitro"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"  -- Ensure consistency with Nitro
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		runtime "Debug"
		defines "NG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		defines "NG_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		runtime "Release"
		defines "NG_DIST"
		optimize "On"

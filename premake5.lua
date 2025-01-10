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
IncludeDir["glm"] = "Nitro/vendor/glm"

include "Nitro/vendor/GLFW"
include "Nitro/vendor/Glad"
include "Nitro/vendor/imgui"

project "Nitro"
	location "Nitro"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ngpch.h"
	pchsource "Nitro/src/ngpch.cpp"
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	links 
	{
		"GLFW", 
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS",
			"NG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "NG_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Nitro/vendor/spdlog/include",
		"Nitro/vendor/imgui",
		"Nitro/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nitro"
	}

	filter "system:windows"
		staticruntime "On"  
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "NG_DIST"
		runtime "Release"
		optimize "on"

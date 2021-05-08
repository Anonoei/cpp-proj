workspace "PacMan"
	startproject "PacMan"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}
	
	platforms
	{
		"Win-64",
		"Win-32",
		"Linux-64",
		"Linux-32",
		"MacOS-64",
		"MacOS-32",
		"iOS-ARM",
		"Anrdoid-ARM",
	}
	
	filter {"platforms:Win-64 or Linux-64 or MacOS-64"}		--	x86_64
		architecture "x86_64"

	filter {"platforms:Win-32 or Linux-32 or MacOS-32"}		--	x86
		architecture "x86"

	filter {"platforms:iOS-64 or Android-64"}				--	ARM
		architecture "ARM"

	filter {"system:windows"}			--	WINDOWS
		removeplatforms { "Linux-32", "Linux-64", "MacOS-32", "MacOS-64" }
		defaultplatform "Win-64"

	filter {"system:linux"}				--	LINUX
		removeplatforms { "Win-32", "Win-64", "MacOS-32", "MacOS-64" }
		defaultplatform "Linux-64"

	filter {"system:macosx"}			--	MACOS
		removeplatforms { "Linux-32", "Linux-64", "Win-32", "Win-64" }
		defaultplatform "MacOS-64"
	filter ""

	flags
	{
		"MultiProcessorCompile"
	}
	
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}"
	
project "PacMan"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.cpp",
	}
	
	includedirs
	{
		"src",
		"../../tools/DAdbg/include"
	}
	
	filter {"system:windows"}			--	WINDOWS
		systemversion "latest"
		defines "Dr_PLATFORM_WINDOWS"

	filter {"system:linux"}				--	LINUX
		systemversion "latest"
		defines "Dr_PLATFORM_LINUX"

	filter {"system:macosx"}			--	MACOS
		systemversion "latest"
		defines "Dr_PLATFORM_MACOS"

	filter "configurations:Debug"	--	DEBUG
		defines "Dr_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"	--	RELEASE
		defines "Dr_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "Dr_DISTRIBUTION"
		runtime "Release"
		optimize "on"
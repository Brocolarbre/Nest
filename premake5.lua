newoption {
	trigger = "static-crt",
	description = "Build with static crt linkage"
}

workspace "Nest"
	platforms { "x86", "x64" }
	configurations { "Debug", "Release" }
	
	startproject "Nest"
	
	filter "platforms:x86"
		architecture "x86"
	
	filter "platforms:x64"
		architecture "x64"
	
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"
	
	filter {}
	
	filter "options:static-crt"
		staticruntime "On"
	
	filter "not options:static-crt"
		staticruntime "Off"
	
	filter {}
	
	outputdir = "%{wks.location}/build/%{cfg.system}/%{cfg.platform}/%{cfg.buildcfg}"
	
	includedirs "%{wks.location}/external/include"
	
project "Nest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")
	
	targetname("nest")
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}
project "Application"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"src"
	}
	
	links {

	}
	
	defines {
	
	}
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}
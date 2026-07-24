project "Application"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"%{wks.location}/Library/include",
		"src"
	}
	
	links {
		"Library"
	}
	
	filter "options:shared-library"
		disablewarnings {
			"4251",
			"4275"
		}
	
	filter "not options:shared-library"
		links {

		}
		
		defines {
			"LIBRARY_STATIC"
		}

	filter {}
	
	defines {
	
	}
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}
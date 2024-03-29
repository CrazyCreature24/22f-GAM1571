workspace "Game"
	configurations {"Debug", "Release" }
	platforms { "x64" }
	location "build"
	characterset "MBCS"
	startproject "GameProject"

	filter "configurations:Debug"
		symbols "on"
	
project "GameProject"
	kind "WindowedApp"
	files { 
		"Game/Source/**.cpp", 
		"Game/Source/**.h",
		"premake5.lua",
		"GenerateProjectFiles.bat",
		"Game/Data/Shaders/**.frag",
		"Game/Data/Shaders/**.vert"
	}
	includedirs { "Framework/Source" }
	links { "Framework", "opengl32" }
	debugdir "Game"
	pchheader "Framework.h"
	pchsource "Game/Source/main.cpp"
	
project "Framework"
	kind "StaticLib"
	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/imgui/*.cpp",
		"Framework/Libraries/imgui/*.h"
	}
	includedirs { "Framework/Source" }
	pchheader "CoreHeaders.h"
	pchsource "Framework/Source/FWCore.cpp"
	filter { "files:Framework/Libraries/imgui/*.cpp" }
        flags { "NoPCH" }
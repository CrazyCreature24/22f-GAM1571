workspace "Game"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	location "build"
	characterset "MBCS"
	startproject "GameProject"

	filter "configurations:Debug"
        symbols        "on"

project "GameProject"
	kind "WindowedApp"
	files {
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"Game/Data/Shaders/**.vert",
		"Game/Data/Shaders/**.frag",
		"premake5.lua"
	}
	includedirs { "Framework/Source" }
	links { "Framework", "opengl32" }
	debugdir "Game"

project "Framework"
	kind "StaticLib"
	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/imgui/*.cpp",
		"Framework/Libraries/imgui/*.h"
	}
	includedirs { "Framework/Source" }

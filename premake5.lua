workspace "Game"
	configurations {"Debug", "Release" }
	platforms { "x64" }
	location "build"
	characterset "MBCS"
	startproject "GameProject"
	
project "GameProject"
	kind "WindowedApp"
	files { 
		"Game/Source/**.cpp", 
		"Game/Source/**.h",
		"premake5.lua",
		"GenerateProjectFiles.bat"
	}
	includedirs { "Framework/Source" }
	links { "Framework", "opengl32" }
	
project "Framework"
	kind "StaticLib"
	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h"
	}
	includedirs { "Framework/Source" }
	
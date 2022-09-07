workspace "Game"
	configurations {"Debug", "Release" }
	platforms { "x64" }
	location "build"
	
project "GameProject"
	kind "WindowedApp"
	files { 
		"Game/Source/**.cpp", 
		"Game/Source/**.h",
		"premake5.lua",
		"GenerateProjectFiles.bat"
	}
	
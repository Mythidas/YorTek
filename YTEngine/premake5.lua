include "dependencies.lua"

project "YTEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "include/**.cpp",
        "src/**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
        "YAML_CPP_STATIC_DEFINE",
	}

    includedirs
    {
        "include",
        "%{IncludeDir.SPD}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.YAML_CPP}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "OpenGL32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "YT_PLAT_WINDOWS",
        }

    filter "configurations:Debug"
        defines
        {
            "YT_DEBUG",
            "YT_ASSERTS_ENABLED"
        }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "YT_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "YT_DIST"
        optimize "On"
        runtime "Release"
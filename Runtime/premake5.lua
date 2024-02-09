include "dependencies.lua"

project "Runtime"
    location "src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "include/**.cpp",
        "src/**.cpp",
    }

    includedirs
    {
        "include",
        "%{wks.location}/YTEngine/include",
    }

    links
    {
        "YTEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "YT_PLAT_WINDOWS",
        }

    filter "configurations:Debug"
        defines "YT_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "YT_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "YT_DIST"
        optimize "On"
        runtime "Release"
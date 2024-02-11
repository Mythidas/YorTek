include "dependencies.lua"

project "Editor"
    location "src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
        "%{wks.location}/YTEngine/include",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.SPD}",
    }

    links
    {
        "YTEngine",
        "ImGui"
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
include "dependencies.lua"

project "YTEngine.Physics"
    kind "SharedLib"
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
	}

    includedirs
    {
        "include",
        "%{wks.location}/YTEngine/include",
        "%{IncludeDir.GLM}",
    }

    links
    {
        "YTEngine"
    }

    postbuildcommands
    {
        {"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Runtime"},
        {"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Editor"},
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
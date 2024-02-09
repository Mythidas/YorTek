include "dependencies.lua"

project "NativeScripts"
    kind "SharedLib"
    location "src"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

    includedirs
    {
        "src",
        "%{wks.location}/YTEngine/include",
        "%{wks.location}/YTEngine.Physics/include",
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
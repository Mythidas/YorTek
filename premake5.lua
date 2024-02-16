include "dependencies.lua"

workspace "YorTek"
    architecture "x64"
    startproject "Editor"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "YTEngine/vendor/GLFW"
    include "YTEngine/vendor/glad"
    include "YTEngine/vendor/imgui"
    include "YTEngine/vendor/yaml-cpp"
group ""

group "Core"
    include "YTEngine"
    include "YTEngine.Rendering"
group ""

group "Executables"
    include "Runtime"
    include "Editor"
    include "NativeScripts"
group ""
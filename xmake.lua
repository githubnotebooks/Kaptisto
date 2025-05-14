local global_settings = function()
    set_languages("c++23")
    set_warnings("all")
    -- set_policy("build.c++.modules", true)
    add_rules("mode.debug", "mode.release")
    add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })
end

local platform_settings = function()
    if is_host("windows") then
        add_cxxflags("/EHsc", "/utf-8")
        add_defines("_CRT_SECURE_NO_WARNINGS")
        add_links("User32", "Shell32")
    end
end

local global_deps_settings = function()
    add_requires("spdlog", "cli11", "gtest", "benchmark", "cpptrace")
    add_requires("boost", { system = false, configs = { shared = false, cmake = false } })

    if is_mode("debug") then
        add_defines("SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE")
    elseif is_mode("release") then
        add_defines("SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_OFF")
    end
end

global_settings()
platform_settings()
global_deps_settings()

add_includedirs("common", ".", { public = true })
includes("tools", "libs", "tests", "examples")

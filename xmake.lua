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
    add_requires("spdlog", { system = true, configs = { shared = true } })
    add_requires("cli11", { system = true, configs = { shared = true } })
    add_requires("gtest", { system = true, configs = { shared = true } })
    add_requires("benchmark", { system = true, configs = { shared = true } })
    add_requires("cpptrace", { system = true, configs = { shared = true } })
    add_requires("boost", { system = true, configs = { shared = true, cmake = false } })

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
includes("tools", "libs", "tests", "app")

task("debug", function()
    set_category("action")
    set_menu {
        usage = "xmake debug",
        description = "Configure project in debug mode, build it, and run test and main programs.",
        options = {},
    }
    on_run(function()
        os.exec("xmake f -m debug")
        os.exec("xmake")
        os.exec("xmake run unit --gtest_color=yes")
        os.exec("xmake run Kaptisto")
    end)
end)

task("clean", function()
    set_category("action")
    set_menu {
        usage = "xmake clean",
        description = "Remove intermediate build directories and cache files using custom rm tool.",
        options = {},
    }
    on_run(function()
        local targets = {
            ".xmake",
            ".cache",
            "build"
        }
        local rm = nil
        if os.getenv("OS") and os.getenv("OS"):find("Windows") then
            rm = ".\\tools\\bin\\rm.exe"
        else
            rm = "./tools/bin/rm"
        end
        for _, j in ipairs(targets) do
            os.execv(rm, { j })
        end
    end)
end)

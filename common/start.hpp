#pragma once

#include "header.hpp"

template <typename Arg> class Start
{
  private:
    Arg arg_;

    Start(int argc, char **argv)
    {
        init_log();
        init_cli(argc, argv);
    }

    Start(const Start &) = delete;
    Start &operator=(const Start &) = delete;

    int init_log()
    {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
        spdlog::set_pattern("[%^%l%$] :%v");
        return 0;
    }

    void init_cli(int argc, char **argv)
    {
        CLI::App app;
        argv = app.ensure_utf8(argv);
        app.add_option("--echo", arg_, "example");
        init_cli_impl(app, argc, argv);
    }

    int init_cli_impl(CLI::App &app, int argc, char **argv)
    {
        CLI11_PARSE(app, argc, argv);
        return 0;
    }

  public:
    static void start(int argc, char **argv)
    {
        static Start i(argc, argv);
    }
};

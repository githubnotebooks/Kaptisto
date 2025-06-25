#pragma once

#include "header.hpp"

class Init
{
  private:
    std::string path_;

  public:
    Init(int argc, char **argv)
    {
        init_log();
        path_ = init_cli(argc, argv);
    }

    int init_log()
    {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
        spdlog::set_pattern("[%^%l%$] :%v");
        return 0;
    }

    std::string init_cli(int argc, char **argv)
    {
        CLI::App app;
        argv = app.ensure_utf8(argv);
        std::string arg;
        app.add_option("file", arg, "filename");
        init_cli_impl(app, argc, argv);
        return arg;
    }

    std::string get_path() const
    {
        return path_;
    }

  private:
    int init_cli_impl(CLI::App &app, int argc, char **argv)
    {
        CLI11_PARSE(app, argc, argv);
        return 0;
    }
};

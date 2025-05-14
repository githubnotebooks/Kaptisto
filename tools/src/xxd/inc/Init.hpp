#pragma once

#include "CLI/CLI.hpp"
#include "spdlog/spdlog.h"

namespace vim
{

class Init
{
  public:
    std::string infile_;
    std::string outfile_;
    bool upcase_{false};

    Init(int argc, char **argv)
    {
        init_log();
        init_cli(argc, argv);
    }

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

        app.add_flag("-u", upcase_, "use upper case hex letters.");
        app.add_option("infile", infile_, "Path to the input file");
        app.add_option("outfile", outfile_, "Path to the output file");

        init_cli_impl(app, argc, argv);
    }

  private:
    int init_cli_impl(CLI::App &app, int argc, char **argv)
    {
        CLI11_PARSE(app, argc, argv);
        return 0;
    }
};

} // namespace vim

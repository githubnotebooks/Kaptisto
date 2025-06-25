#include "Init.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <system_error>

using namespace std;
namespace fs = std::filesystem;

void remove_path(const fs::path &target_path)
{
    if (not fs::exists(target_path))
    {
        SPDLOG_ERROR("path does not exist: {}", target_path.string());
        return;
    }

    std::error_code ec;
    fs::remove_all(target_path, ec);

    if (ec)
    {
        SPDLOG_ERROR("failed to delete the path: {}", ec.message());
    }
    else
    {
        SPDLOG_INFO("successfully deleted: {}", target_path.string());
    }
}

int main(int argc, char **argv)
{
    Init app(argc, argv);
    remove_path(app.get_path());

    return 0;
}

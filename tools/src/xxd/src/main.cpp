#include "Init.hpp"
#include "xxd.hpp"
#include <fstream>

namespace vim
{

std::string get_raw_data_(std::string_view filename)
{
    std::ifstream file(filename.data(), std::ios::binary);
    if (!file)
    {
        throw std::logic_error("Failed to open file.");
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

void save_to_file(std::string_view filename, std::string_view contents)
{
    std::ofstream file(filename.data());
    if (!file)
    {
        throw std::logic_error(std::string("Failed to create file ") +
                               std::string(filename));
    }
    file << contents;
}

} // namespace vim

int main(int argc, char *argv[])
{
    vim::Init app(argc, argv);

    if (not app.infile_.empty())
    {
        vim::XXD xxd(vim::get_raw_data_(app.infile_));
        xxd.set_upper_case(app.upcase_);
        xxd.run();

        if (not app.outfile_.empty())
        {
            vim::save_to_file(app.outfile_, xxd.get_result());
        }
        else
        {
            std::cout << xxd.get_result();
        }
    }

    return 0;
}

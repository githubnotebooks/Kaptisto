#include "header.hpp"
#include "start.hpp"
#include "test_case.hpp"
#include "type.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Start<std::string>::start(argc, argv);
    for (auto &&it : test_table)
    {
        it.run(argc, argv);
    }
    return 0;
}

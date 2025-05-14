#include "header.hpp"
#include "test_case.hpp"

using namespace std;
#define main eg_test_impl

int main(int argc, char *argv[])
{
    return 0;
}

bool eg_test(int argc, char *argv[])
{
    return 0 == main(argc, argv);
}

INIT_TEST_TABLE(eg_test, "eg[test]");

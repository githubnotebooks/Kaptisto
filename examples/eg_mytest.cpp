#include "header.hpp"
#include "test_case.hpp"

using namespace std;
#define main eg_mytest_test_impl

int main(int argc, char *argv[])
{
    return 0;
}

bool eg_mytest_test(int argc, char *argv[])
{
    return 0 == main(argc, argv);
}

INIT_TEST_TABLE(eg_mytest_test, "eg_mytest[test]");

#pragma once

#include <print>
#include <string_view>
#include <vector>

class TestCase
{
  private:
    using TestFunc = bool(int, char *[]);
    TestFunc *test_func_;
    std::string_view test_name_;

  public:
    TestCase(TestFunc *tf, std::string_view tn) : test_func_(tf), test_name_(tn)
    {
    }

    void run(int argc, char *argv[])
    {
        if (test_func_(argc, argv))
        {
            std::println("{} is ok!", test_name_);
        }
        else
        {
            std::println("{} is wrong!", test_name_);
        }
    }
};

inline std::vector<TestCase> test_table;

struct Init
{
    Init(TestCase tc)
    {
        test_table.push_back(tc);
    }
};

#define INIT_TEST_TABLE(fun, desc) static Init init##__COUNTER__({fun, desc});

#include <gtest/gtest.h>

namespace
{

struct MyGDBStruct
{
    std::string name_;
    double scores_;
};

} // namespace

TEST(gdb, pretty_printer)
{
    MyGDBStruct mgs{"James", 8.0};
    EXPECT_EQ(mgs.name_, "James");
    EXPECT_DOUBLE_EQ(mgs.scores_, 8.0);
}

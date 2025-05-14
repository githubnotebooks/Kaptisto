#include "xxd.hpp"
#include <print>
#include <sstream>

namespace vim
{

using namespace std;

void XXD::run()
{
    for (int i = 0; i < row_count_ * 16; ++i)
    {
        int col_id = i % 16;
        int row_id = i / 16;

        if (0 == col_id)
        {
            stringstream ss;
            print(ss, "{:08x}: ", i);
            size_t idx = row_id * fmt_.row_length_ + fmt_.idx_col_;
            formated_data_.replace(idx, ss.str().length(), ss.str());
        }

        do
        {
            auto opt = cur_char(i);
            if (opt)
            {
                auto c = *opt;
                ascii_repr_ += isprint(c) ? c : '.';

                stringstream ss;
                if (upper_case_)
                    print(ss, "{:02X}", c);
                else
                    print(ss, "{:02x}", c);
                size_t idx = row_id * fmt_.row_length_ + fmt_.hex_col_[col_id];
                formated_data_.replace(idx, ss.str().length(), ss.str());
            }
        } while (0);

        if (15 == col_id)
        {
            size_t idx = row_id * fmt_.row_length_ + fmt_.ascii_col_;
            formated_data_.replace(idx, ascii_repr_.length(), ascii_repr_);
            idx += ascii_repr_.length();
            formated_data_[idx] = '\n';
            ascii_repr_.clear();
        }
    }
    auto endpos = formated_data_.find_last_not_of(" ");
    if (endpos != std::string::npos)
    {
        formated_data_.erase(endpos + 1);
    }
}
} // namespace vim

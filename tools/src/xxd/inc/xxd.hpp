#pragma once

#include <optional>
#include <string>

// xxd 是由 Vim 的作者 Bram Moolenaar 开发的，它最初作为 Vim
// 的配套工具分发。
namespace vim
{

class XXDFormat
{
  public:
    int idx_col_ = 0;
    int hex_col_[16] = {
        idx_col_ + 8 + 2,  idx_col_ + 8 + 4,  idx_col_ + 8 + 7,  idx_col_ + 8 + 9,
        idx_col_ + 8 + 12, idx_col_ + 8 + 14, idx_col_ + 8 + 17, idx_col_ + 8 + 19,
        idx_col_ + 8 + 22, idx_col_ + 8 + 24, idx_col_ + 8 + 27, idx_col_ + 8 + 29,
        idx_col_ + 8 + 32, idx_col_ + 8 + 34, idx_col_ + 8 + 37, idx_col_ + 8 + 39,
    };
    int ascii_col_ = hex_col_[15] + 2 + 2;
    int row_length_ = ascii_col_ + 16 + 1;
};

class XXD
{
  public:
    XXD(const std::string &raw_data) : raw_data_{raw_data}
    {
        row_count_ = (raw_data.length() + 15) / 16;
        total_size_ = row_count_ * fmt_.row_length_;
        formated_data_.resize(total_size_, ' ');
    }

    void set_upper_case(bool uppper_case)
    {
        upper_case_ = uppper_case;
    }

    void run();

    std::string get_result() const
    {
        return formated_data_;
    }

  private:
    std::optional<char> cur_char(size_t idx) const
    {
        if (idx >= raw_data_.length())
        {
            return std::nullopt;
        }
        else
            return raw_data_[idx];
    }

  private:
    std::string raw_data_;
    std::string formated_data_;
    std::string ascii_repr_;
    int row_count_ = 0;
    int total_size_ = 0;
    XXDFormat fmt_;
    bool upper_case_{false};
};

} // namespace vim

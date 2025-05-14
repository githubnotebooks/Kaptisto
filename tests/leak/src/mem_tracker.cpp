#include "mem_tracker.hpp"
#include "cpptrace/io.hpp"
#include <print>

namespace leak
{

MemTracker::~MemTracker()
{
    if (false == allocation_log.empty())
    {
        leak::MemTracker::can_track = false;
        size_t total = 0;
        for (auto &&it : allocation_log)
        {
            std::println("Leaked address: {} | Leaked size: {}", it.first,
                         it.second.mem_size_);
            std::println("{}", it.second.st_);
            total += it.second.mem_size_;
        }
        std::println("Total leaked size: {}", total);
    }
}

} // namespace leak

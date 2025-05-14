#pragma once

#include "cpptrace/basic.hpp"
#include <atomic>
#include <map>
#include <mutex>

namespace leak
{

class MemTracker
{
  public:
    class LocInfo
    {
      public:
        size_t mem_size_{0};
        cpptrace::stacktrace st_;
    };

    static MemTracker &instance()
    {
        static MemTracker mt;
        return mt;
    }

    inline static std::atomic<bool> can_track{true};
    using log_type = std::map<void *, LocInfo>;

    void insert(void *key, LocInfo &&value)
    {
        std::lock_guard<std::mutex> lock(mtx);
        allocation_log[key] = std::move(value);
    }

    log_type::iterator find(void *key)
    {
        std::lock_guard<std::mutex> lock(mtx);
        return allocation_log.find(key);
    }

    log_type::iterator end()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return allocation_log.end();
    }

    void erase(log_type::iterator it)
    {
        std::lock_guard<std::mutex> lock(mtx);
        allocation_log.erase(it);
    }

    ~MemTracker();

  private:
    log_type allocation_log;
    std::mutex mtx;
};

} // namespace leak

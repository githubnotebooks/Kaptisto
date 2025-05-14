#include "mem_tracker.hpp"
#include <cstdlib>
#include <iostream>
#include <new>

void *operator new(size_t sz)
{
    void *p = nullptr;

    /* malloc (0) is unpredictable; avoid it.  */
    if (sz == 0) [[unlikely]]
        sz = 1;
    while ((p = malloc(sz)) == 0)
    {
        std::new_handler handler = std::get_new_handler();
        if (!handler)
            throw std::bad_alloc();
        handler();
    }

    if (true == leak::MemTracker::can_track)
    {
        leak::MemTracker::can_track = false;
        // Capture stack trace for memory allocation
        auto loc = cpptrace::generate_trace();
        leak::MemTracker::instance().insert(p, {sz, std::move(loc)});
        leak::MemTracker::can_track = true;
    }

    return p;
}

void operator delete(void *p, size_t sz) noexcept
{
    if (nullptr != p)
    {
        if (true == leak::MemTracker::can_track)
        {
            leak::MemTracker::can_track = false;
            auto &&mt = leak::MemTracker::instance();
            auto it = mt.find(p);
            if (it != mt.end())
            {
                mt.erase(it);
            }
            else
            {
                std::cerr
                    << "Warning: Attempted to delete a pointer that was not tracked by "
                       "MemTracker: "
                    << p << std::endl;
            }
            leak::MemTracker::can_track = true;
        }
        std::free(p);
    }
}

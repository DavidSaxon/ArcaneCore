#include "arcanecore/base/clock/ClockOperations.hpp"

#include <chrono>
#include <ctime>

// allows us to use std::localtime, without warning it's unsafe.
#ifdef ARC_OS_WINDOWS
    #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#endif


namespace arc
{
namespace clock
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

arc::uint64 get_current_time(TimeMetric metric)
{
    return static_cast<arc::uint64>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
            ).count()
    ) / static_cast<arc::uint64>(metric);
}

arc::str::UTF8String get_datetime(
        arc::uint64 t,
        arc::str::UTF8String format,
        TimeMetric metric)
{
    // convert to time_t
    time_t t_t = static_cast<time_t>(t / (METRIC_SECONDS / metric));
    // get the date
    char buffer[50];
    strftime(
        buffer,
        sizeof(buffer),
        format.get_raw(),
        std::localtime(&t_t)
    );
    return arc::str::UTF8String(buffer);
}

} // namespace clock
} // namespace arc

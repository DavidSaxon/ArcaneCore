#include "arcanecore/base/clock/ClockOperations.hpp"

#include <chrono>

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

} // namespace clock
} // namespace arc

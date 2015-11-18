#include "chaoscore/base/clock/ClockOperations.hpp"

#include <chrono>

namespace chaos
{
namespace clock
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

chaos::uint64 get_current_time( TimeMetric metric )
{
    return static_cast< chaos::uint64 >(
            std::chrono::duration_cast< std::chrono::nanoseconds >(
                    std::chrono::system_clock::now().time_since_epoch()
            ).count()
    ) / static_cast< chaos::uint64 >( metric );
}

} // namespace clock
} // namespace chaos

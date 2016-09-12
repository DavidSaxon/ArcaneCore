/*!
 * \file
 * \brief Operations for measuring time.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_CLOCK_CLOCKOPERATIONS_HPP_
#define ARCANECORE_BASE_CLOCK_CLOCKOPERATIONS_HPP_

#include "arcanecore/base/Types.hpp"

namespace arc
{
namespace clock
{

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

/*!
 * \brief The available metrics for measuring time.
 */
enum TimeMetric
{
    METRIC_NANOSECONDS  = 1UL,
    METRIC_MICROSECONDS = 1000UL,
    METRIC_MILLISECONDS = 1000000UL,
    METRIC_SECONDS      = 1000000000UL,
};

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Returns the time elapsed since Linux Epoch (1st January 1970).
 *
 * \param metric Metric the returned value will be measured in. Defaults to
 *               METRIC_MILLISECONDS
 */
arc::uint64 get_current_time(TimeMetric metric = METRIC_MILLISECONDS);

} // namespace clock
} // namespace arc

#endif
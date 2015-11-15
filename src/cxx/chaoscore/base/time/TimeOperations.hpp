/*!
 * \file
 * \brief Utility functions relating to time.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_TIME_TIMEOPERATIONS_HPP_
#define CHAOSCORE_BASE_TIME_TIMEOPERATIONS_HPP_

#include "chaoscore/base/Types.hpp"

namespace chaos
{
/*!
 * \brief Operations and classes relating to time.
 */
namespace time
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Returns the time pass since epoch in milliseconds.
 */
chaos::uint64 get_current_time();

} // namespace time
} // namespace chaos

#endif

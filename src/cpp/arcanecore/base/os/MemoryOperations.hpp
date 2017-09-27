/*!
 * \file
 * \brief Memory related functionality.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_OS_MEMORYOPERATIONS_HPP_
#define ARCANECORE_BASE_OS_MEMORYOPERATIONS_HPP_

#include "arcanecore/base/Types.hpp"


namespace arc
{
namespace os
{

/*!
 * \brief Returns the current resident set size (physical memory use) measured
 *        in bytes.
 */
std::size_t get_rss();

/*!
 * \brief Returns the peak (maximum so far) resident set size (physical memory
 *        use) measured in bytes.
 */
std::size_t get_peak_rss();

} // namespace os
} // namespace arc

#endif

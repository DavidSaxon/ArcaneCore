/*!
 * \file
 * \brief Operations relating to Unicode string data.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_
#define CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace str
{

bool utf8_is_digit( chaos::uint32 code_point );

} // namespace str
} // namespace chaos

#endif

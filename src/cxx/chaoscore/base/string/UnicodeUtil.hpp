/*!
 * \file
 * \brief Operations relating to utf-8 encoded string data.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_UNICODEUTIL_HPP_
#define CHAOSCORE_BASE_STRING_UNICODEUTIL_HPP_

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace str
{

bool utf8_is_digit( chaos::uint32 code_point );

} // namespace str
} // namespace chaos

#endif

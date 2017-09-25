/*!
 * \file
 * \brief Platform independent implementation of the fnmatch function.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_STR_FNMATCH_HPP_
#define ARCANECORE_BASE_STR_FNMATCH_HPP_

#include "arcanecore/base/str/UTF8String.hpp"


namespace arc
{
namespace str
{

/*!
 * \brief Checks whether the s parameter matches the pattern parameter which is
 *        a shell wildcard pattern.
 */
bool fnmatch(
        const arc::str::UTF8String& pattern,
        const arc::str::UTF8String& s);

} // namespace str
} // namespace arc

#endif

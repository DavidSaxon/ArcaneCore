/*!
 * \file
 * \brief Operations relating to Unicode string data.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_
#define CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_

#include "chaoscore/base/Types.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Returns whether the given Unicode code point is a digit or not.
 *
 * Example usage:
 *
 * \code
 * chaos::str::UTF8String s( "5" );
 * chaos::str::is_digit( s.get_code_point( 0 ) ); // returns: true
 * \endcode
 *
 */
bool is_digit( chaos::uint32 code_point );

// chaos::str::UTF8String join(
//         const std::vector< chaos::str::UTF8String >& components,
//         const chaos::str::UTF8String& seperator );

} // namespace str
} // namespace chaos

#endif

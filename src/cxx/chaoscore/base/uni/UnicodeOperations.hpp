/*!
 * \file
 * \brief Operations relating to Unicode string data.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_
#define CHAOSCORE_BASE_STRING_UNICODEOPERATIONS_HPP_

#include "chaoscore/base/Types.hpp"
#include "chaoscore/base/uni/UTF8String.hpp"

namespace chaos
{
namespace uni
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
 * chaos::uni::UTF8String s( "5" );
 * chaos::uni::is_digit( s.get_code_point( 0 ) ); // returns: true
 * \endcode
 *
 */
bool is_digit( chaos::uint32 code_point );

// chaos::uni::UTF8String join(
//         const std::vector< chaos::uni::UTF8String >& components,
//         const chaos::uni::UTF8String& seperator );

} // namespace uni
} // namespace chaos

#endif

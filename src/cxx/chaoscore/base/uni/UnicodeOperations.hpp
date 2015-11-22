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

/*!
 * \brief Joins the given vector into a single chaos::uni::UTF8String.
 *
 * The components of the vector will be concatenated together with the separator
 * string between each component.
 *
 * Example usage:
 *
 * \code
 * std::vector< chaos::uni::UTF8String > components;
 * components.push_back( "Hello" );
 * components.push_back( "World" );
 * chaos::uni::join( components, "_" ); returns: "Hello_World";
 * \endcode
 *
 * \param components Vector of string components to join together as a single
 *                   string.
 * \param separator chaos::uni::UTF8String to join each component together with.
 * \return New chaos::uni::UTF8String containing the results of the operation.
 */
chaos::uni::UTF8String join(
        const std::vector< chaos::uni::UTF8String >& components,
        const chaos::uni::UTF8String& separator );

} // namespace uni
} // namespace chaos

#endif

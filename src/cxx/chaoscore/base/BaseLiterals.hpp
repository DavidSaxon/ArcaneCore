/*!
 * \file
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_LITERALS_HPP_
#define CHAOSCORE_BASE_LITERALS_HPP_

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
/*!
 * \brief User defined literal operators for ChaosCore.
 */
namespace literal
{

/*!
 * \brief Creates a chaos::UTF8String from a cstring literal
 *
 * Example usage:
 * \code
 * using chaos::literal::operator"" _utf8;
 * "Hello World!"_utf8
 * \endcode
 */
chaos::str::UTF8String operator"" _utf8 ( const char* literal, size_t length )
{
    return chaos::str::UTF8String( literal, length );
}

} // namespace literal
} // namespace chaos

//------------------------------------------------------------------------------
//                                     MACRO
//------------------------------------------------------------------------------

#define CHAOS_BASE_USE_LITERALS \
        using chaos::literal::operator"" _utf8;

#endif

/*!
 * \file
 * \brief Global constants relating to Unicode data.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STR_STRINGCONSTANTS_HPP_
#define CHAOSCORE_BASE_STR_STRINGCONSTANTS_HPP_

#include <cstddef>

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

/*!
 * \brief Encoding types for string data.
 */
enum Encoding
{
    ENCODING_ASCII = 0,
    ENCODING_UTF8,
    ENCODING_UTF16_LITTLE_ENDIAN,
    ENCODING_UTF16_BIG_ENDIAN
};

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

/*!
 * \brief Value used to signify an invalid Unicode based index.
 */
extern const std::size_t npos;

} // namespace str
} // namespace chaos

#endif

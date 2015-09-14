#ifndef CHAOSCORE_BASE_STRING_UTF8STRING_HPP_
#   define CHAOSCORE_BASE_STRING_UTF8STRING_HPP_

#include <string>

#include "base/string/__string.hpp"

namespace chaos
{
namespace str
{

/** \brief A generic string type that fully supports Unicode encoded with utf-8
  *
  * TODO: detailed description
  */
class UTF8String
{
public:

    /** Creates a new utf-8 encoded string from the given string literal */
    UTF8String( const char* data );
};


} // namespace str
} // namespace chaos

#endif

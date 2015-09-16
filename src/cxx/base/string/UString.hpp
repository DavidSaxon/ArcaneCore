/*! \file */

#ifndef CHAOSCORE_BASE_STRING_USTRING_HPP_
#   define CHAOSCORE_BASE_STRING_USTRING_HPP_

#include <string>

#include "base/string/__string.hpp"

namespace chaos
{
namespace str
{

/** \brief A generic string type for storing Unicode data.
  *
  * TODO: detailed description
  */
class UString
{
public:

    //--------------------------------------------------------------------------
    //                                ENUMERATORS
    //--------------------------------------------------------------------------

    enum Encoding
    {
        ENCODING_UTF8,
        ENCODING_UTF16
        // TODO: UTF4, UTF7, UTF32
    };

    enum DataWidth
    {
        DATAWIDTH_8,
        DATAWIDTH_16,
        DATAWIDTH_32
    };

    enum Packing
    {
        PACK_TIGHT,
        PACK_ALIGNED
    };

    //--------------------------------------------------------------------------
    //                               INNER CLASSES
    //--------------------------------------------------------------------------

    /** Inner class??? */
    struct DataDefinition
    {
        Encoding  inputEncoding;
        DataWidth inputWidth;
        Encoding  storedEncoding;
        DataWidth storedWidth;
        Packing   storedPacking;
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    UString( const void* data );

    UString( const void* data, const DataDefinition& definition );

};


} // namespace str
} // namespace chaos

#endif

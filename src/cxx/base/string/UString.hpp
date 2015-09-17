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
  * TODO: recommend string literals are presented explicitly, i.e. with u8
  * prefix
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
        // TODO: UTF7, UTF32
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

    /** TODO: DOC */
    struct DataDefinition
    {
        //---------------------------PUBLIC VARIABLES---------------------------

        /** TODO: DOC */
        Encoding  inputEncoding;
        /** TODO: DOC */
        DataWidth inputWidth;
        /** TODO: DOC */
        Encoding  storedEncoding;
        /** TODO: DOC */
        Packing   storedPacking;

        //-----------------------------CONSTRUCTORS-----------------------------

        DataDefinition()
            :
            inputEncoding ( UString::defaultInputEncoding ),
            inputWidth    ( UString::defaultInputWidth ),
            storedEncoding( UString::defaultStoredEncoding ),
            storedPacking ( UString::defaultStoredPacking )
        {
        }

        //------------------------------OPERATORS-------------------------------
    };

    //--------------------------------------------------------------------------
    //                              PUBLIC VARIABLES
    //--------------------------------------------------------------------------

    //-------------------------DEFAULT DATA DEFINITIONS-------------------------

    /** The default encoding that input data will be provided in. This value is
      * initially set to ENCODING_UTF8 on Unix systems and ENCODING_UTF16 on
      * Windows systems.
      *
      * For example if this value is set to ENCODING_UTF8, creating a UString
      * with:
      * \code
      * chaos::str::UString( "Ἦλθον, εἶδον, ἐνίκησα" );
      * \endcode
      * will assume the provided char array data is encoded with utf-8
      */
    static Encoding defaultInputEncoding;
    /** The default bit width of each character that input data will be provided
      * in. This value is initially set to DATAWIDTH_8.
      *
      * For example if this value was set to DATAWIDTH_8, creating a UString
      * with:
      * \code
      * chaos::str::UString( "Ἦλθον, εἶδον, ἐνίκησα" );
      * \endcode
      * would correctly read that data. Even though most of the characters are
      * stored across two 8-bit chars: the data is represented in an array of
      * 8-bit chars.
      *
      * Whereas creating a UString with:
      * \code
      * chaos::str::UString( u"Ἦλθον, εἶδον, ἐνίκησα" );
      * \endcode
      * would cause problems since the data is nor represented with an array of
      * 16-bit wide chars. To solve this you would need to either explicitly
      * pass the data width to the constructor through a DataDefinition struct,
      * or change this default value.
      */
    static DataWidth defaultInputWidth;
    /** TODO: DOC */
    static Encoding defaultStoredEncoding;
    /** TODO: DOC */
    static Packing defaultStoredPacking;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new Unicode string that contains the provided data. The data
      * definitions are defined by the global defaults
      * TODO: global definitions
      */
    UString( const void* data );

    /** TODO: DOC */
    UString( const void* data, const DataDefinition& definition );
};


} // namespace str
} // namespace chaos

#endif

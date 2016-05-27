#include "chaoscore/base/data/ByteOperations.hpp"

#include "chaoscore/base/Exceptions.hpp"
#include "chaoscore/base/str/UTF8String.hpp"

namespace chaos
{
namespace data
{

chaos::uint32 bytes_to_uint32(
        const void* bytes,
        std::size_t length,
        Endianness endianness )
{
    // valid data?
    if ( length > sizeof( chaos::uint32 ) )
    {
        chaos::str::UTF8String error_message;
        error_message << "Too many bytes to convert to chaos::uint32. A ";
        error_message << "chaos::uint32 consists of ";
        error_message << sizeof( chaos::uint32 ) << " bytes, where " << length;
        error_message < " bytes were provided.";
        throw chaos::ex::ConversionDataError( error_message );
    }

    // get as char array
    const unsigned char* b = static_cast< const unsigned char* >( bytes );

    chaos::uint32 result = 0;

    switch( endianness )
    {
        case ENDIAN_LITTLE:
        {
            for ( std::size_t i = length; i > 0; --i )
            {
                result = ( result << 8 ) + b[ i - 1 ];
            }
            break;
        }
        case ENDIAN_BIG:
        {
            for ( std::size_t i = 0; i < length; ++i )
            {
                result = ( result << 8 ) + b[ i ];
            }
            break;
        }
    }

    return result;
}

} // namespace data
} // namespace chaos

#include "chaoscore/base/data/ByteOperations.hpp"

namespace chaos
{
namespace data
{

chaos::uint32 bytes_to_uint32(
        const void* bytes,
        size_t      length,
        Endianness  endianness )
{
    // get as char array
    const unsigned char* b = static_cast< const unsigned char* >( bytes );

    chaos::uint32 result = 0;

    switch( endianness )
    {
        case ENDIAN_LITTLE:
        {
            for ( size_t i = length; i > 0; --i )
            {
                result = ( result << 8 ) + b[ i - 1 ];
            }
            break;
        }
        case ENDIAN_BIG:
        {
            for ( size_t i = 0; i < length; ++i )
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

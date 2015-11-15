#include "chaoscore/base/data/BinaryOperations.hpp"

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace data
{

Endianness get_system_endianness()
{
    chaos::int16 test = 0x1;
    char* test_ptr = ( char* ) &test;
    if ( test_ptr[ 0 ] == 1 )
    {
        return ENDIAN_LITTLE;
    }
    return ENDIAN_BIG;
}

} // namespace data
} // namespace chaos

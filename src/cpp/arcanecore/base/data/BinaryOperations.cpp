#include "arcanecore/base/data/BinaryOperations.hpp"

#include "arcanecore/base/Types.hpp"

namespace arc
{
namespace data
{

Endianness get_system_endianness()
{
    arc::int16 test = 0x1;
    char* test_ptr = ( char* ) &test;
    if ( test_ptr[ 0 ] == 1 )
    {
        return ENDIAN_LITTLE;
    }
    return ENDIAN_BIG;
}

} // namespace data
} // namespace arc

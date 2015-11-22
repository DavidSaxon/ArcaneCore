#include "chaoscore/base/uni/UnicodeOperations.hpp"

namespace chaos
{
namespace uni
{

bool is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

chaos::uni::UTF8String join(
        const std::vector< chaos::uni::UTF8String >& components,
        const chaos::uni::UTF8String& seperator )
{
    chaos::uni::UTF8String ret;

    for ( size_t i = 0; i < components.size(); ++i )
    {
        ret << components[ i ];
        if ( i != components.size() - 1 )
        {
            ret << seperator;
        }
    }

    return ret;
}

} // namespace uni
} // namespace chaos

#include "chaoscore/base/uni/UnicodeOperations.hpp"

#include "chaoscore/base/BaseExceptions.hpp"

namespace chaos
{
namespace uni
{

bool is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

chaos::uni::UTF8String utf16_to_utf8(
        const char* data,
        std::size_t symbol_length,
        chaos::data::Endianness endianness )
{
    // TODO:

    return chaos::uni::UTF8String();
}

char* utf8_to_utf16(
        const chaos::uni::UTF8String& data,
        std::size_t& r_length,
        chaos::data::Endianness endianness )
{
    std::vector< unsigned char > v_str;
    // convert
    for( std::size_t i = 0; i < data.get_length(); ++i )
    {
        chaos::uint32 code_point = data.get_code_point( i );
        if ( code_point < 0xFFFF )
        {
            if ( endianness == chaos::data::ENDIAN_LITTLE )
            {
                v_str.push_back( code_point );
                v_str.push_back( code_point >> 8 );
            }
            else
            {
                v_str.push_back( code_point >> 8 );
                v_str.push_back( code_point );
            }
        }
        else
        {
            throw chaos::ex::NotImplementedError(
                    "converting to UTF-16 symbols with greater than 2 byte"
                    "width is not yet supported."
            );
        }
    }
    // add the NULL terminator
    v_str.push_back( 0x00 );
    v_str.push_back( 0x00 );

    r_length = v_str.size();
    // allocate to array and copy
    char* s = new char[ r_length ];
    for( std::size_t i = 0; i < v_str.size(); ++i )
    {
        s[ i ] = static_cast< char >( v_str[ i ] );
    }

    return s;
}

chaos::uni::UTF8String join(
        const std::vector< chaos::uni::UTF8String >& components,
        const chaos::uni::UTF8String& seperator )
{
    chaos::uni::UTF8String ret;

    for ( std::size_t i = 0; i < components.size(); ++i )
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

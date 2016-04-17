#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/str/UnicodeOperations.hpp"

namespace chaos
{
namespace str
{

bool is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

chaos::str::UTF8String utf16_to_utf8(
        const char* data,
        std::size_t symbol_length,
        chaos::data::Endianness endianness )
{
    // ensure data is unsigned
    const unsigned char* d = reinterpret_cast< const unsigned char* >( data );

    // TODO: support 4 byte symbols
    std::vector< unsigned char > utf8;
    // iterate over each character
    for ( size_t i = 0;
          symbol_length == chaos::str::npos || i < ( symbol_length * 2 );
          i += 2 )
    {
        chaos::uint32 code_point = 0;
        if ( endianness == chaos::data::ENDIAN_BIG )
        {
            code_point = ( static_cast< chaos::uint32 >( d[ i ] ) << 8 ) |
                         static_cast< chaos::uint32 >( d[ i + 1 ] );
        }
        else
        {
            code_point = static_cast< chaos::uint32 >( d[ i ] ) |
                         ( static_cast< chaos::uint32 >( d[ i + 1 ] << 8 ) );
        }

        // null?
        if ( code_point == 0 && symbol_length == chaos::str::npos )
        {
            break;
        }
        // one byte UTF-8 character
        else if ( code_point < 0x80 )
        {
            utf8.push_back( static_cast< unsigned char >( code_point ) );
        }
        // two byte UTF-8 character
        else if  ( code_point < 0x800 )
        {
            utf8.push_back( static_cast< unsigned char >(
                    0xC0 + ( code_point >> 6 ) ) );
            utf8.push_back( static_cast< unsigned char >(
                    0x80 + ( code_point & 0x3F ) ) );
        }
        // three byte UTF-8 character
        else if ( code_point < 0x10000 )
        {
            utf8.push_back( static_cast< unsigned char >(
                    0xE0 + ( code_point >> 12 ) ) );
            utf8.push_back( static_cast< unsigned char >(
                    0x80 + ( ( code_point >> 6 ) & 0x3F ) ) );
            utf8.push_back( static_cast< unsigned char >(
                    0x80 + ( code_point & 0x3F ) ) );
        }
        // four byte UTF-8 character
        else
        {
            throw chaos::ex::NotImplementedError(
                    "converting UTF-16 symbols with greater than 2 byte"
                    "width to UTF-8 is not yet supported."
            );
        }
    }

    return chaos::str::UTF8String( ( const char* ) &utf8[ 0 ], utf8.size() );
}

char* utf8_to_utf16(
        const chaos::str::UTF8String& data,
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

chaos::str::UTF8String join(
        const std::vector< chaos::str::UTF8String >& components,
        const chaos::str::UTF8String& seperator )
{
    chaos::str::UTF8String ret;

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

} // namespace str
} // namespace chaos

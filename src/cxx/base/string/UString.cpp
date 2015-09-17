#include "base/string/UString.hpp"

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                                PUBLIC VARIABLES
//------------------------------------------------------------------------------

// TODO: should this be UTF16 for windows?
UString::Encoding  UString::defaultInputEncoding  = UString::ENCODING_UTF8;
UString::DataWidth UString::defaultInputWidth     = UString::DATAWIDTH_8;
UString::Encoding  UString::defaultStoredEncoding = UString::ENCODING_UTF8;

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

// TODO: do something with this...
// UString::UString( const char* data )
// {
//     // TESTING: let's inspect
//     std::string s( data );

//     std::cout << "STRING LENGTH: " << s.length() << std::endl;
//     std::cout << "STRING CONTENTS: " << s << std::endl;

//     std::cout << "CHARACTERS: ";
//     for ( size_t i = 0; i < s.length(); ++i )
//     {
//         std::cout << "|_" << s[ i ] << "_| ";
//     }
//     std::cout << std::endl;

//     std::cout << "VALUES: ";
//     for ( size_t i = 0; i < s.length(); ++i )
//     {
//         std::cout << "|_" << static_cast< int >( s[ i ] ) << "_| ";
//     }
//     std::cout << std::endl;
// }

UString::UString( const void* data )
{
    const char* p = static_cast< const char* >( data );

    std::cout << "data: " << p << std::endl;
}

UString::UString( const void* data, const DataDefinition& definition )
{

}

} // namespace str
} // namespace chaos

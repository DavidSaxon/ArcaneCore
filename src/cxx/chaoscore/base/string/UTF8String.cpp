#include "chaoscore/base/string/UTF8String.hpp"

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UTF8String::UTF8String( const char* data )
{
    // TESTING: let's inspect
    std::string s( data );

    std::cout << "STRING LENGTH: " << s.length() << std::endl;
    std::cout << "STRING CONTENTS: " << s << std::endl;

    std::cout << "CHARACTERS: ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_" << s[ i ] << "_| ";
    }
    std::cout << std::endl;

    std::cout << "VALUES: ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_" << static_cast< int >( s[ i ] ) << "_| ";
    }
    std::cout << std::endl;
}

} // namespace str
} // namespace chaos

#include <iostream>

#include "chaoscore/base/BaseLiterals.hpp"

CHAOS_BASE_USE_LITERALS

int main( int argc, char* argv[] )
{
    // TODO:
    chaos::str::UTF8String s( "Hello World %d"_utf8.format( 69 ) );
    std::cout << "STRING: "_utf8 << s << std::endl;
    std::cout << "SYMBOL: "_utf8 << s.getSymbol( 2 ) << std::endl;



    return 0;
}

#include "chaoscore/test/ChaosTest.hpp"

#include "chaoscore/base/string/UnicodeUtil.hpp"

CHAOS_TEST_MODULE( base.str.unicode )

//------------------------------------------------------------------------------
//                                 UTF8_IS_DIGIT
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( utf8_is_digit )
{
    CHAOS_TEST_MESSAGE( "Checking valid code points" );
    // since UTF8 has the same starting values as ASCII we can use ASCII digits
    // to test
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '0' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '1' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '2' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '3' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '4' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '5' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '6' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '7' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '8' ) );
    CHAOS_CHECK_TRUE( chaos::str::utf8_is_digit( '9' ) );

    CHAOS_TEST_MESSAGE( "Checking invalid code points" );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( 'A' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( 'z' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( '!' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( '$' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( '&' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( '_' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( '@' ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( 0 ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( 1024 ) );
    CHAOS_CHECK_FALSE( chaos::str::utf8_is_digit( 2153595 ) );
}

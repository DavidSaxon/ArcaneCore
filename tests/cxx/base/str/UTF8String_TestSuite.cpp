#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.str.utf8 )

CHAOS_TEST_UNIT( test_run )
{
    CHAOS_CHECK_EQUAL( 1, 2 );

    // char* seg = new char[ 2 ];
    // seg[ 56 ] = 12;
    // delete[] seg;
    // delete[] seg;

    CHAOS_CHECK_EQUAL( 1, 1 );
}

#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.str.utf8string )

#include "chaoscore/base/string/UTF8String.hpp"

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class UTF8StringFixture : public chaos::test::Fixture
{
public:

    // TODO:
};

CHAOS_TEST_UNIT( default_constructor )
{
    CHAOS_TEST_MESSAGE( "Checking internal data is empty" );
    chaos::str::UTF8String empty;
    CHAOS_CHECK_EQUAL( empty.get_length(), 0 );
    CHAOS_CHECK_EQUAL( empty.get_byte_length(), 1 );
    CHAOS_CHECK_EQUAL( empty.get_raw_data()[ 0 ], 0 );
}

CHAOS_TEST_UNIT( c_string_constructor )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );
    const char* cstring_1 = "Hello World";
    chaos::str::UTF8String v1( cstring_1 );
    CHAOS_CHECK_EQUAL( strcmp( v1.to_cstring(), cstring_1 ), 0 );

    const char* cstring_2 = "a";
    chaos::str::UTF8String v2( cstring_2 );
    CHAOS_CHECK_EQUAL( strcmp( v2.to_cstring(), cstring_2 ), 0 );

    const char* cstring_3 = "This is a really long string, that just keeps on"
                            "going on and on and on! It never seems to end, "
                            "but just when you think that it will not end. It "
                            "ends.\n\n\n\n\nNope still going here.\t\t\tThe "
                            "end!\n\n\n\t\t\t";
    chaos::str::UTF8String v3( cstring_3 );
    CHAOS_CHECK_EQUAL( strcmp( v3.to_cstring(), cstring_3 ), 0 );

    const char* cstring_4 = "";
    chaos::str::UTF8String v4( cstring_4 );
    CHAOS_CHECK_EQUAL( strcmp( v4.to_cstring(), cstring_4 ), 0 );

    // TODO: need to test actual non-ascii data
    // don't have to pass just yet though
}

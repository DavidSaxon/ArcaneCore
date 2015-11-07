#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.str.utf8string )

#include <cstring>

#include "chaoscore/base/string/UTF8String.hpp"

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class UTF8StringGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    const char* cstring_empty;
    const char* cstring_ascii_std;
    const char* cstring_ascii_short;
    const char* cstring_ascii_long;
    const char* cstring_unicode_std;
    const char* cstring_unicode_mix;
    const char* cstring_unicode_short;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void setup()
    {
        cstring_empty         = "";
        cstring_ascii_std     = "Hello World";
        cstring_ascii_short   = "a";
        cstring_ascii_long    = "This is a really long string, that just keeps "
                                "on going on and on and on! It never seems to "
                                "end, but just when you think that it will not "
                                "end. It ends.\n\n\n\n\nNope still going here."
                                "\t\t\tThe end!\n\n\n\t\t\t";
        cstring_unicode_std   = "γειά σου Κόσμε";
        cstring_unicode_mix   = "this is a مزيج of text";
        cstring_unicode_short = "간";
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    CHAOS_TEST_MESSAGE( "Checking internal data is empty" );
    chaos::str::UTF8String empty;
    CHAOS_CHECK_EQUAL( empty.get_length(), 0 );
    CHAOS_CHECK_EQUAL( empty.get_byte_length(), 1 );
    CHAOS_CHECK_EQUAL( empty.get_raw_data()[ 0 ], 0 );
}

//------------------------------------------------------------------------------
//                              CSTRING CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    chaos::str::UTF8String v_1( fixture->cstring_empty );
    CHAOS_CHECK_EQUAL( strcmp( v_1.to_cstring(), fixture->cstring_empty ), 0 );

    chaos::str::UTF8String v_2( fixture->cstring_ascii_std );
    CHAOS_CHECK_EQUAL(
            strcmp( v_2.to_cstring(), fixture->cstring_ascii_std ),
            0
    );

    chaos::str::UTF8String v_3( fixture->cstring_ascii_short );
    CHAOS_CHECK_EQUAL(
            strcmp( v_3.to_cstring(), fixture->cstring_ascii_short ),
            0
    );

    chaos::str::UTF8String v_4( fixture->cstring_ascii_long );
    CHAOS_CHECK_EQUAL(
            strcmp( v_4.to_cstring(), fixture->cstring_ascii_long ),
            0
    );

    chaos::str::UTF8String v_5( fixture->cstring_unicode_std );
    CHAOS_CHECK_EQUAL(
            strcmp( v_5.to_cstring(), fixture->cstring_unicode_std ),
            0
    );

    chaos::str::UTF8String v_6( fixture->cstring_unicode_mix );
    CHAOS_CHECK_EQUAL(
            strcmp( v_6.to_cstring(), fixture->cstring_unicode_mix ),
            0
    );

    chaos::str::UTF8String v_7( fixture->cstring_unicode_short );
    CHAOS_CHECK_EQUAL(
            strcmp( v_7.to_cstring(), fixture->cstring_unicode_short ),
            0
    );
}

//------------------------------------------------------------------------------
//                         CSTRING AND LENGTH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_length_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    chaos::str::UTF8String v_1(
            fixture->cstring_empty,
            strlen( fixture->cstring_empty )
    );
    CHAOS_CHECK_EQUAL( strcmp( v_1.to_cstring(), fixture->cstring_empty ), 0 );

    chaos::str::UTF8String v_2(
            fixture->cstring_ascii_std,
            strlen( fixture->cstring_ascii_std )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_2.to_cstring(), fixture->cstring_ascii_std ),
            0
    );

    chaos::str::UTF8String v_3(
            fixture->cstring_ascii_short,
            strlen( fixture->cstring_ascii_short )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_3.to_cstring(), fixture->cstring_ascii_short ),
            0
    );

    chaos::str::UTF8String v_4(
            fixture->cstring_ascii_long,
            strlen( fixture->cstring_ascii_long )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_4.to_cstring(), fixture->cstring_ascii_long ),
            0
    );

    chaos::str::UTF8String v_5(
            fixture->cstring_unicode_std,
            strlen( fixture->cstring_unicode_std )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_5.to_cstring(), fixture->cstring_unicode_std ),
            0
    );

    chaos::str::UTF8String v_6(
            fixture->cstring_unicode_mix,
            strlen( fixture->cstring_unicode_mix )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_6.to_cstring(), fixture->cstring_unicode_mix ),
            0
    );

    chaos::str::UTF8String v_7(
            fixture->cstring_unicode_short,
            strlen( fixture->cstring_unicode_short )
    );
    CHAOS_CHECK_EQUAL(
            strcmp( v_7.to_cstring(), fixture->cstring_unicode_short ),
            0
    );
}

//------------------------------------------------------------------------------
//                                INT8 CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( int8_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    const chaos::int8* data_1 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_empty );
    chaos::str::UTF8String v_1( data_1 );
    CHAOS_CHECK_EQUAL( strcmp( v_1.to_cstring(), fixture->cstring_empty ), 0 );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_1.get_raw_data(),
                    data_1, strlen( fixture->cstring_empty ) + 1
            ),
            0
    );

    const chaos::int8* data_2 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_std );
    chaos::str::UTF8String v_2( data_2 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_2.to_cstring(), fixture->cstring_ascii_std ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_2.get_raw_data(),
                    data_2, strlen( fixture->cstring_ascii_std ) + 1
            ),
            0
    );

    const chaos::int8* data_3 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_short );
    chaos::str::UTF8String v_3( data_3 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_3.to_cstring(), fixture->cstring_ascii_short ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_3.get_raw_data(),
                    data_3, strlen( fixture->cstring_ascii_short ) + 1
            ),
            0
    );

    const chaos::int8* data_4 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_long );
    chaos::str::UTF8String v_4( data_4 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_4.to_cstring(), fixture->cstring_ascii_long ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_4.get_raw_data(),
                    data_4, strlen( fixture->cstring_ascii_long ) + 1
            ),
            0
    );

    const chaos::int8* data_5 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_std );
    chaos::str::UTF8String v_5( data_5 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_5.to_cstring(), fixture->cstring_unicode_std ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_5.get_raw_data(),
                    data_5, strlen( fixture->cstring_unicode_std ) + 1
            ),
            0
    );

    const chaos::int8* data_6 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_mix );
    chaos::str::UTF8String v_6( data_6 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_6.to_cstring(), fixture->cstring_unicode_mix ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_6.get_raw_data(),
                    data_6, strlen( fixture->cstring_unicode_mix ) + 1
            ),
            0
    );

    const chaos::int8* data_7 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_short );
    chaos::str::UTF8String v_7( data_7 );
    CHAOS_CHECK_EQUAL(
            strcmp( v_7.to_cstring(), fixture->cstring_unicode_short ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_7.get_raw_data(),
                    data_7, strlen( fixture->cstring_unicode_short ) + 1
            ),
            0
    );
}

//------------------------------------------------------------------------------
//                          INT8 AND LENGTH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( int8_length_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    const chaos::int8* data_1 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_empty );
    chaos::str::UTF8String v_1( data_1, strlen( fixture->cstring_empty ) );
    CHAOS_CHECK_EQUAL( strcmp( v_1.to_cstring(), fixture->cstring_empty ), 0 );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_1.get_raw_data(),
                    data_1, strlen( fixture->cstring_empty ) + 1
            ),
            0
    );

    const chaos::int8* data_2 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_std );
    chaos::str::UTF8String v_2( data_2, strlen( fixture->cstring_ascii_std ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_2.to_cstring(), fixture->cstring_ascii_std ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_2.get_raw_data(),
                    data_2, strlen( fixture->cstring_ascii_std ) + 1
            ),
            0
    );

    const chaos::int8* data_3 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_short );
    chaos::str::UTF8String v_3( data_3, strlen( fixture->cstring_ascii_short ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_3.to_cstring(), fixture->cstring_ascii_short ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_3.get_raw_data(),
                    data_3, strlen( fixture->cstring_ascii_short ) + 1
            ),
            0
    );

    const chaos::int8* data_4 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_ascii_long );
    chaos::str::UTF8String v_4( data_4, strlen( fixture->cstring_ascii_long ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_4.to_cstring(), fixture->cstring_ascii_long ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_4.get_raw_data(),
                    data_4, strlen( fixture->cstring_ascii_long ) + 1
            ),
            0
    );

    const chaos::int8* data_5 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_std );
    chaos::str::UTF8String v_5(
            data_5, strlen( fixture->cstring_unicode_std ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_5.to_cstring(), fixture->cstring_unicode_std ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_5.get_raw_data(),
                    data_5, strlen( fixture->cstring_unicode_std ) + 1
            ),
            0
    );

    const chaos::int8* data_6 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_mix );
    chaos::str::UTF8String v_6(
            data_6, strlen( fixture->cstring_unicode_mix ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_6.to_cstring(), fixture->cstring_unicode_mix ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_6.get_raw_data(),
                    data_6, strlen( fixture->cstring_unicode_mix ) + 1
            ),
            0
    );

    const chaos::int8* data_7 = reinterpret_cast< const chaos::int8* >(
            fixture->cstring_unicode_short );
    chaos::str::UTF8String v_7(
            data_7, strlen( fixture->cstring_unicode_short ) );
    CHAOS_CHECK_EQUAL(
            strcmp( v_7.to_cstring(), fixture->cstring_unicode_short ),
            0
    );
    CHAOS_CHECK_EQUAL(
            memcmp(
                    v_7.get_raw_data(),
                    data_7, strlen( fixture->cstring_unicode_short ) + 1
            ),
            0
    );
}

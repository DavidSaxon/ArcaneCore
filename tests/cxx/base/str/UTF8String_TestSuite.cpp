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

    // cstrings
    std::vector< const char* > cstrings;
    // utf8strings
    std::vector< chaos::str::UTF8String > utf8_strings;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void setup()
    {
        // populate cstring data
        cstrings.push_back( "" );
        cstrings.push_back( "Hello World" );
        cstrings.push_back( "a" );
        cstrings.push_back( "This is a really long string, that just keeps on "
                            "going on and on and on! It never seems to end, "
                            "but just when you think that it will not end. It "
                            "ends.\n\n\n\n\nNope still going here.\t\t\tThe "
                            "end!\n\n\n\t\t\t" );
        cstrings.push_back( "γειά σου Κόσμε" );
        cstrings.push_back( "this is a مزيج of text" );
        cstrings.push_back( "간" );

        // copy to utf8string data
        CHAOS_FOR_EACH( it, cstrings )
        {
            utf8_strings.push_back( chaos::str::UTF8String( *it ) );
        }

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

    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        chaos::str::UTF8String v( *it );
        CHAOS_CHECK_EQUAL( strcmp( v.to_cstring(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                         CSTRING AND LENGTH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_length_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

        CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        chaos::str::UTF8String v( *it, strlen( *it ) );
        CHAOS_CHECK_EQUAL( strcmp( v.to_cstring(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                INT8 CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( int8_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        const chaos::int8* data = reinterpret_cast< const chaos::int8* >( *it );
        chaos::str::UTF8String v( data );
        CHAOS_CHECK_EQUAL( strcmp( v.to_cstring(), *it ), 0 );
        CHAOS_CHECK_EQUAL(
                memcmp( v.get_raw_data(), data, strlen( *it ) + 1 ),
                0
        );
    }
}

//------------------------------------------------------------------------------
//                          INT8 AND LENGTH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( int8_length_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        const chaos::int8* data = reinterpret_cast< const chaos::int8* >( *it );
        chaos::str::UTF8String v( data, strlen( *it ) );
        CHAOS_CHECK_EQUAL( strcmp( v.to_cstring(), *it ), 0 );
        CHAOS_CHECK_EQUAL(
                memcmp( v.get_raw_data(), data, strlen( *it ) + 1 ),
                0
        );
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( copy_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );

    CHAOS_FOR_EACH( it, fixture->utf8_strings )
    {
        chaos::str::UTF8String copy( *it );
        CHAOS_CHECK_EQUAL( copy, *it );
        CHAOS_CHECK_EQUAL( strcmp( copy.to_cstring(), it->to_cstring() ), 0 );
        CHAOS_CHECK_EQUAL(
                memcmp(
                        copy.get_raw_data(),
                        it->get_raw_data(),
                        it->get_byte_length()
                ),
                0
        );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( assignment_operator, UTF8StringGenericFixture )
{
    // populate strings to assign to
    std::vector< chaos::str::UTF8String > assigns;
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        assigns.push_back( "data will be overridden" );
    }

    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::str::UTF8String r = assigns[ i ] = fixture->utf8_strings[ i ];
        CHAOS_CHECK_EQUAL( r, assigns[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking length" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                assigns[ i ].get_byte_length(),
                fixture->utf8_strings[ i ].get_byte_length()
        );
        CHAOS_CHECK_EQUAL(
                strlen( assigns[ i ].to_cstring() ),
                strlen( fixture->utf8_strings[ i ].to_cstring() )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking contents match" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( assigns[ i ], fixture->utf8_strings[ i ] );
        CHAOS_CHECK_EQUAL(
                memcmp(
                        assigns[ i ].get_raw_data(),
                        fixture->utf8_strings[ i ].get_raw_data(),
                        fixture->utf8_strings[ i ].get_byte_length()
                ),
                0
        );
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( equality_operator, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking from literal data" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::str::UTF8String v( fixture->cstrings[ i ] );
        CHAOS_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking from copy constructor" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::str::UTF8String v( fixture->utf8_strings[ i ] );
        CHAOS_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

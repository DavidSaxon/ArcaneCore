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
    // lengths
    std::vector< size_t > lengths;
    // utf8strings
    std::vector< chaos::str::UTF8String > utf8_strings;
    // symbols
    std::vector< std::map< size_t, chaos::str::UTF8String > > symbols;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void setup()
    {
        // populate cstring data
        cstrings.push_back( "" );
        lengths.push_back( 0 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "Hello World" );
        lengths.push_back( 11 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::str::UTF8String( "H" );
            symbol_map[ 3  ] = chaos::str::UTF8String( "l" );
            symbol_map[ 7  ] = chaos::str::UTF8String( "o" );
            symbol_map[ 10 ] = chaos::str::UTF8String( "d" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "a" );
        lengths.push_back( 1 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0 ] = chaos::str::UTF8String( "a" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "This is a really long string, that just keeps on "
                            "going on and on and on! It never seems to end, "
                            "but just when you think that it will not end. It "
                            "ends.\n\n\n\n\nNope still going here.\t\t\tThe "
                            "end!\n\n\n\t\t\t" );
        lengths.push_back( 194 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0   ] = chaos::str::UTF8String( "T" );
            symbol_map[ 5   ] = chaos::str::UTF8String( "i" );
            symbol_map[ 34  ] = chaos::str::UTF8String( " " );
            symbol_map[ 87  ] = chaos::str::UTF8String( " " );
            symbol_map[ 88  ] = chaos::str::UTF8String( "t" );
            symbol_map[ 100 ] = chaos::str::UTF8String( "j" );
            symbol_map[ 125 ] = chaos::str::UTF8String( "i" );
            symbol_map[ 167 ] = chaos::str::UTF8String( "o" );
            symbol_map[ 190 ] = chaos::str::UTF8String( "\n" );
            symbol_map[ 193 ] = chaos::str::UTF8String( "\t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "γειά σου Κόσμε" );
        lengths.push_back( 14 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::str::UTF8String( "γ" );
            symbol_map[ 1  ] = chaos::str::UTF8String( "ε" );
            symbol_map[ 5  ] = chaos::str::UTF8String( "σ" );
            symbol_map[ 8  ] = chaos::str::UTF8String( " " );
            symbol_map[ 11 ] = chaos::str::UTF8String( "σ" );
            symbol_map[ 13 ] = chaos::str::UTF8String( "ε" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "this is a مزيج of text" );
        lengths.push_back( 22 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::str::UTF8String( "t" );
            symbol_map[ 2  ] = chaos::str::UTF8String( "i" );
            symbol_map[ 9  ] = chaos::str::UTF8String( " " );
            symbol_map[ 11 ] = chaos::str::UTF8String( "ز" );
            symbol_map[ 13 ] = chaos::str::UTF8String( "ج" );
            symbol_map[ 15 ] = chaos::str::UTF8String( "o" );
            symbol_map[ 18 ] = chaos::str::UTF8String( "t" );
            symbol_map[ 20 ] = chaos::str::UTF8String( "x" );
            symbol_map[ 21 ] = chaos::str::UTF8String( "t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "간" );
        lengths.push_back( 1 );
        {
            std::map< size_t, chaos::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::str::UTF8String( "간" );
            symbols.push_back( symbol_map );
        }

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

CHAOS_TEST_UNIT_FIXTURE( inequality_operator, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking from literal data" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::str::UTF8String v( "this שטריקל is not the same" );
        CHAOS_CHECK_NOT_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking from copy constructor" );
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::str::UTF8String org( "this שטריקל is not the same" );
        chaos::str::UTF8String v( org );
        CHAOS_CHECK_NOT_EQUAL( v, fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               LESS THAN FIXTURE
//------------------------------------------------------------------------------

class LessThanFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > less;
    std::vector< chaos::str::UTF8String > more;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void setup()
    {
        less.push_back( "abcdefg" );
        more.push_back( "bcdefgh" );

        less.push_back( "Z" );
        more.push_back( "ɿ" );

        less.push_back( "abcdefghZϚϣ" );
        more.push_back( "abcdefghɿϦZ" );

        less.push_back( "ޝ" );
        more.push_back( "ౠ" );

        less.push_back( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬ0" );
        more.push_back( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );

        less.push_back( "0" );
        more.push_back( "1" );

        less.push_back( "abcdefg" );
        more.push_back( "bcdefghijk" );
    }
};

//------------------------------------------------------------------------------
//                               LESS THAN OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( less_than_operator, LessThanFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true evaluation" );
    for ( size_t i = 0; i < fixture->less.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->less[ i ] < fixture->more[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking false evaluation" );
    for ( size_t i = 0; i < fixture->less.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->more[ i ] < fixture->less[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                   GET LENGTH
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_length, UTF8StringGenericFixture )
{
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->utf8_strings[ i ].get_length(),
                fixture->lengths[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   GET SYMBOL
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_symbol, UTF8StringGenericFixture )
{
    for ( size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_FOR_EACH( it, fixture->symbols[ i ] )
        {
            CHAOS_CHECK_EQUAL(
                    fixture->utf8_strings[ i ].get_symbol( it->first ),
                    it->second
            );
        }
    }
}

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
//                                ADDITION FIXTURE
//------------------------------------------------------------------------------

class ConcatenateFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::str::UTF8String > comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back ( "" );
        comp_2.push_back ( "" );
        results.push_back( "" );

        comp_1.push_back ( "Hello" );
        comp_2.push_back ( "" );
        results.push_back( "Hello" );

        comp_1.push_back ( "" );
        comp_2.push_back ( "World" );
        results.push_back( "World" );

        comp_1.push_back ( "Hello " );
        comp_2.push_back ( "World!" );
        results.push_back( "Hello World!" );

        comp_1.push_back ( "         " );
        comp_2.push_back ( "     " );
        results.push_back( "              " );

        comp_1.push_back ( "γειά σο" );
        comp_2.push_back ( "υ Κόσμε!" );
        results.push_back( "γειά σου Κόσμε!" );

        comp_1.push_back ( "this is a مز" );
        comp_2.push_back ( "يج of text" );
        results.push_back( "this is a مزيج of text" );
    }
};

//------------------------------------------------------------------------------
//                                 REPEAT FIXTURE
//------------------------------------------------------------------------------

class RepeatFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp;
    std::vector< chaos::uint32 >          count;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp.push_back( "*" );
        count.push_back( 12 );
        results.push_back( "************" );

        comp.push_back( "_" );
        count.push_back( 0 );
        results.push_back( "" );

        comp.push_back( "Hello" );
        count.push_back( 3 );
        results.push_back( "HelloHelloHello" );

        comp.push_back( "간" );
        count.push_back( 1 );
        results.push_back( "간" );

        comp.push_back( "γειά" );
        count.push_back( 5 );
        results.push_back( "γειάγειάγειάγειάγειά" );

        comp.push_back( "mج" );
        count.push_back( 2 );
        results.push_back( "mجmج" );

        comp.push_back( "" );
        count.push_back( 100 );
        results.push_back( "" );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    CHAOS_TEST_MESSAGE( "Checking internal data is empty" );
    chaos::str::UTF8String empty;
    CHAOS_CHECK_EQUAL( empty.get_length(), static_cast< size_t >( 0 ) );
    CHAOS_CHECK_EQUAL( empty.get_byte_length(), static_cast< size_t >( 1 ) );
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
//                               LESS THAN OPERATOR
//------------------------------------------------------------------------------

class LessThanFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > less;
    std::vector< chaos::str::UTF8String > more;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

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
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( addition_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] + fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                           COMPOUND ADDITION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( compound_addition_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] += fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                            MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( multiplication_operator, RepeatFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp[ i ] * fixture->count[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                        COMPOUND MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( compound_multiplication_operator, RepeatFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp[ i ] *= fixture->count[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              UTF8 STREAM OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( utf8_stream_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                            CSTRING STREAM OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_stream_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ].to_cstring(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              BOOL STREAM OPERATOR
//------------------------------------------------------------------------------

class BoolStreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< bool >                   comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( false );
        results.push_back( "0" );

        comp_1.push_back( "" );
        comp_2.push_back( true );
        results.push_back( "1" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( false );
        results.push_back( "Hello0" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( true );
        results.push_back( "Κόσμε1" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( bool_stream_operator, BoolStreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              CHAR STREAM OPERATOR
//------------------------------------------------------------------------------

class CharStreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< char >                   comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 'a' );
        results.push_back( "a" );

        comp_1.push_back( "" );
        comp_2.push_back( '!' );
        results.push_back( "!" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 'Z' );
        results.push_back( "HelloZ" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( '`' );
        results.push_back( "Κόσμε`" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( char_stream_operator, CharStreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INT8 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int8StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::int8 >            comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 'a' );
        results.push_back( "a" );

        comp_1.push_back( "" );
        comp_2.push_back( '!' );
        results.push_back( "!" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 'Z' );
        results.push_back( "HelloZ" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( '`' );
        results.push_back( "Κόσμε`" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int8_stream_operator, Int8StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT8 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint8StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::uint8 >           comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 'a' );
        results.push_back( "a" );

        comp_1.push_back( "" );
        comp_2.push_back( '!' );
        results.push_back( "!" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 'Z' );
        results.push_back( "HelloZ" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( '`' );
        results.push_back( "Κόσμε`" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( uint8_stream_operator, Uint8StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT16 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int16StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::int16 >           comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 512 );
        results.push_back( "512" );

        comp_1.push_back( "" );
        comp_2.push_back( -1893 );
        results.push_back( "-1893" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 12890 );
        results.push_back( "Hello12890" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( -0 );
        results.push_back( "Κόσμε0" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int16_stream_operator, Int16StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT16 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint16StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::uint16 >          comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 32 );
        results.push_back( "32" );

        comp_1.push_back( "" );
        comp_2.push_back( 65535 );
        results.push_back( "65535" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 9829 );
        results.push_back( "Hello9829" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( 0 );
        results.push_back( "Κόσμε0" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( uint16_stream_operator, Uint16StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT32 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int32StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::int32 >           comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 2048 );
        results.push_back( "2048" );

        comp_1.push_back( "" );
        comp_2.push_back( -2147483648 );
        results.push_back( "-2147483648" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 2147483647 );
        results.push_back( "Hello2147483647" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( -64 );
        results.push_back( "Κόσμε-64" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int32_stream_operator, Int32StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT32 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint32StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::uint32 >          comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 4294967295 );
        results.push_back( "4294967295" );

        comp_1.push_back( "" );
        comp_2.push_back( 0 );
        results.push_back( "0" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 2147483647 );
        results.push_back( "Hello2147483647" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( 234324 );
        results.push_back( "Κόσμε234324" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( uint32_stream_operator, Uint32StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT64 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int64StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::int64 >           comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 432487238429329 );
        results.push_back( "432487238429329" );

        comp_1.push_back( "" );
        comp_2.push_back( -1024 );
        results.push_back( "-1024" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 0 );
        results.push_back( "Hello0" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( -23480932849234 );
        results.push_back( "Κόσμε-23480932849234" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int64_stream_operator, Int64StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT64 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint64StreamOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > comp_1;
    std::vector< chaos::uint64 >          comp_2;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 0 );
        results.push_back( "0" );

        comp_1.push_back( "" );
        comp_2.push_back( 32493248920489324 );
        results.push_back( "32493248920489324" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 32 );
        results.push_back( "Hello32" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( 123781231 );
        results.push_back( "Κόσμε123781231" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( uint64_stream_operator, Uint64StreamOperatorFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
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

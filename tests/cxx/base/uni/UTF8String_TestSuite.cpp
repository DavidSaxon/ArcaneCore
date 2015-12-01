#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.uni.utf8_string )

#include <algorithm>
#include <cstring>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/uni/UTF8String.hpp"

namespace utf8_string_tests
{

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
    std::vector< std::size_t > lengths;
    // utf8strings
    std::vector< chaos::uni::UTF8String > utf8_strings;
    // symbols
    std::vector< std::map< std::size_t, chaos::uni::UTF8String > > symbols;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // populate cstring data
        cstrings.push_back( "" );
        lengths.push_back( 0 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "Hello World" );
        lengths.push_back( 11 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::uni::UTF8String( "H" );
            symbol_map[ 3  ] = chaos::uni::UTF8String( "l" );
            symbol_map[ 7  ] = chaos::uni::UTF8String( "o" );
            symbol_map[ 10 ] = chaos::uni::UTF8String( "d" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "a" );
        lengths.push_back( 1 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0 ] = chaos::uni::UTF8String( "a" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "This is a really long string, that just keeps on "
                            "going on and on and on! It never seems to end, "
                            "but just when you think that it will not end. It "
                            "ends.\n\n\n\n\nNope still going here.\t\t\tThe "
                            "end!\n\n\n\t\t\t" );
        lengths.push_back( 194 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0   ] = chaos::uni::UTF8String( "T" );
            symbol_map[ 5   ] = chaos::uni::UTF8String( "i" );
            symbol_map[ 34  ] = chaos::uni::UTF8String( " " );
            symbol_map[ 87  ] = chaos::uni::UTF8String( " " );
            symbol_map[ 88  ] = chaos::uni::UTF8String( "t" );
            symbol_map[ 100 ] = chaos::uni::UTF8String( "j" );
            symbol_map[ 125 ] = chaos::uni::UTF8String( "i" );
            symbol_map[ 167 ] = chaos::uni::UTF8String( "o" );
            symbol_map[ 190 ] = chaos::uni::UTF8String( "\n" );
            symbol_map[ 193 ] = chaos::uni::UTF8String( "\t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "γειά σου Κόσμε" );
        lengths.push_back( 14 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::uni::UTF8String( "γ" );
            symbol_map[ 1  ] = chaos::uni::UTF8String( "ε" );
            symbol_map[ 5  ] = chaos::uni::UTF8String( "σ" );
            symbol_map[ 8  ] = chaos::uni::UTF8String( " " );
            symbol_map[ 11 ] = chaos::uni::UTF8String( "σ" );
            symbol_map[ 13 ] = chaos::uni::UTF8String( "ε" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "this is a مزيج of text" );
        lengths.push_back( 22 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::uni::UTF8String( "t" );
            symbol_map[ 2  ] = chaos::uni::UTF8String( "i" );
            symbol_map[ 9  ] = chaos::uni::UTF8String( " " );
            symbol_map[ 11 ] = chaos::uni::UTF8String( "ز" );
            symbol_map[ 13 ] = chaos::uni::UTF8String( "ج" );
            symbol_map[ 15 ] = chaos::uni::UTF8String( "o" );
            symbol_map[ 18 ] = chaos::uni::UTF8String( "t" );
            symbol_map[ 20 ] = chaos::uni::UTF8String( "x" );
            symbol_map[ 21 ] = chaos::uni::UTF8String( "t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "간" );
        lengths.push_back( 1 );
        {
            std::map< std::size_t, chaos::uni::UTF8String > symbol_map;
            symbol_map[ 0  ] = chaos::uni::UTF8String( "간" );
            symbols.push_back( symbol_map );
        }

        // copy to utf8string data
        CHAOS_FOR_EACH( it, cstrings )
        {
            utf8_strings.push_back( chaos::uni::UTF8String( *it ) );
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::uni::UTF8String > comp_2;
    std::vector< chaos::uni::UTF8String > results;

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

    std::vector< chaos::uni::UTF8String > comp;
    std::vector< chaos::uint32 >          count;
    std::vector< chaos::uni::UTF8String > results;

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
//                                  FIND FIXTURE
//------------------------------------------------------------------------------

class FindFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > strings;
    std::vector< chaos::uni::UTF8String > find;
    std::vector< std::size_t > first_results;
    std::vector< std::size_t > last_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        strings.push_back( " " );
        find.push_back   ( " " );
        first_results.push_back( 0 );
        last_results.push_back( 0 );

        strings.push_back( "Hello World" );
        find.push_back   ( "H" );
        first_results.push_back( 0 );
        last_results.push_back( 0 );

        strings.push_back( "Hello World" );
        find.push_back   ( "l" );
        first_results.push_back( 2 );
        last_results.push_back( 9 );

        strings.push_back( "Hello World" );
        find.push_back   ( "ጵ" );
        first_results.push_back( chaos::uni::npos );
        last_results.push_back( chaos::uni::npos );

        strings.push_back( "γειά σου Κόσμε!" );
        find.push_back   ( "μ" );
        first_results.push_back( 12 );
        last_results.push_back( 12 );

        strings.push_back( "**||**||**@@^^" );
        find.push_back   ( "**" );
        first_results.push_back( 0 );
        last_results.push_back( 8 );

        strings.push_back( "ጸጷጶጵጸጷጶጵጲጱጰጯጮጬᚡጲጱጰጯጮ" );
        find.push_back   ( "ጲጱጰጯጮ" );
        first_results.push_back( 8 );
        last_results.push_back( 15 );

        strings.push_back( "this is a مزيج" );
        find.push_back   ( "ج" );
        first_results.push_back( 13 );
        last_results.push_back( 13 );

        strings.push_back( "γειά σου Κόσμε" );
        find.push_back   ( "γειά σου Κόσμε!" );
        first_results.push_back( chaos::uni::npos );
        last_results.push_back( chaos::uni::npos );
    }
};

//------------------------------------------------------------------------------
//                                 INDEX FIXTURE
//------------------------------------------------------------------------------

class IndexFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::uni::UTF8String       symbols;
    std::vector< chaos::uint32 > byte_indices;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        byte_indices.push_back( 0 );
        symbols << "a";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "f";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "0";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "Z";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "`";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "$";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << ">";

        byte_indices.push_back( byte_indices.back() + 1 );
        symbols << "¡";

        byte_indices.push_back( byte_indices.back() + 2 );
        symbols << "ø";

        byte_indices.push_back( byte_indices.back() + 2 );
        symbols << "Ȼ";

        byte_indices.push_back( byte_indices.back() + 2 );
        symbols << "Ф";

        byte_indices.push_back( byte_indices.back() + 2 );
        symbols << "Թ";

        byte_indices.push_back( byte_indices.back() + 2 );
        symbols << "ः";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "ക";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "ན";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "᎗";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "ᔹ";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "Ḝ";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "ℝ";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "ℬ";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "⌆";

        byte_indices.push_back( byte_indices.back() + 3 );
        symbols << "𐂣";

        byte_indices.push_back( byte_indices.back() + 4 );
        symbols << "𐃕";

        byte_indices.push_back( byte_indices.back() + 4 );
        symbols << "𐃴";

        byte_indices.push_back( byte_indices.back() + 4 );
        symbols << "𐃹";
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::uni::UTF8String empty;
    CHAOS_CHECK_EQUAL(
            empty.get_length(),
            static_cast< std::size_t >( 0 )
    );
    CHAOS_CHECK_EQUAL(
            empty.get_byte_length(),
            static_cast< std::size_t >( 1 )
    );
}

//------------------------------------------------------------------------------
//                              CSTRING CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_constructor, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );
    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        chaos::uni::UTF8String v( *it );
        CHAOS_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
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
        chaos::uni::UTF8String v( *it, strlen( *it ) );
        CHAOS_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
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
        chaos::uni::UTF8String copy( *it );
        CHAOS_CHECK_EQUAL( copy, *it );
        CHAOS_CHECK_EQUAL( strcmp( copy.get_raw(), it->get_raw() ), 0 );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( assignment_operator, UTF8StringGenericFixture )
{
    // populate strings to assign to
    std::vector< chaos::uni::UTF8String > assigns;
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        assigns.push_back( "data will be overridden" );
    }

    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::uni::UTF8String r = assigns[ i ] = fixture->utf8_strings[ i ];
        CHAOS_CHECK_EQUAL( r, assigns[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking length" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                assigns[ i ].get_byte_length(),
                fixture->utf8_strings[ i ].get_byte_length()
        );
        CHAOS_CHECK_EQUAL(
                strlen( assigns[ i ].get_raw() ),
                strlen( fixture->utf8_strings[ i ].get_raw() )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking contents match" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::uni::UTF8String v( fixture->cstrings[ i ] );
        CHAOS_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking from copy constructor" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::uni::UTF8String v( fixture->utf8_strings[ i ] );
        CHAOS_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( inequality_operator, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking from literal data" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::uni::UTF8String v( "this שטריקל is not the same" );
        CHAOS_CHECK_NOT_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking from copy constructor" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        chaos::uni::UTF8String org( "this שטריקל is not the same" );
        chaos::uni::UTF8String v( org );
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

    std::vector< chaos::uni::UTF8String > less;
    std::vector< chaos::uni::UTF8String > more;

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
    CHAOS_TEST_MESSAGE( "Checking less than cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->less[ i ] < fixture->more[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking greater than cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->more[ i ] < fixture->less[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking equals cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->less[ i ] < fixture->less[ i ] );
    }
    for ( std::size_t i = 0; i < fixture->more.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->more[ i ] < fixture->more[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( addition_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] += fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp[ i ] *= fixture->count[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ].get_raw(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                           STD STRING STREAM OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( stdstring_stream_operator, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ].to_std_string(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< bool >                   comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< char >                   comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::int8 >            comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::uint8 >           comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::int16 >           comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::uint16 >          comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::int32 >           comp_2;
    std::vector< chaos::uni::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 2048 );
        results.push_back( "2048" );

        comp_1.push_back( "" );
        comp_2.push_back( -static_cast< chaos::int32 >( 214483648 ) );
        results.push_back( "-214483648" );

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::uint32 >          comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::int64 >           comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
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

    std::vector< chaos::uni::UTF8String > comp_1;
    std::vector< chaos::uint64 >          comp_2;
    std::vector< chaos::uni::UTF8String > results;

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
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                 CSTRING ASSIGN
//------------------------------------------------------------------------------


CHAOS_TEST_UNIT_FIXTURE( cstring_assign, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );
    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        chaos::uni::UTF8String v;
        v.assign( *it );
        CHAOS_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                           CSTRING AND LENGTH ASSIGN
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( cstring_length_assign, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );
    CHAOS_FOR_EACH( it, fixture->cstrings )
    {
        chaos::uni::UTF8String v;
        v.assign( *it, strlen( *it ) );
        CHAOS_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                  UTF8 ASSIGN
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( utf8_assign, UTF8StringGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking internal data matches original string" );
    CHAOS_FOR_EACH( it, fixture->utf8_strings )
    {
        chaos::uni::UTF8String v;
        v.assign( *it );
        CHAOS_CHECK_EQUAL( v, *it );
        CHAOS_CHECK_EQUAL( strcmp( v.get_raw(), it->get_raw() ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                  CONCATENATE
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( concatenate, ConcatenateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp_1[ i ].concatenate( fixture->comp_2[ i ] ),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                     REPEAT
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( repeat, RepeatFixture )
{
    CHAOS_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->comp[ i ].repeat( fixture->count[ i ] ),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->comp[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                  STARTS WITH
//------------------------------------------------------------------------------

class StartsWithFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > strings;
    std::vector< chaos::uni::UTF8String > starts_with;
    std::vector< chaos::uni::UTF8String > not_starts_with;


    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        strings.push_back        ( "" );
        starts_with.push_back    ( "" );
        not_starts_with.push_back( "+" );

        strings.push_back        ( "(" );
        starts_with.push_back    ( "(" );
        not_starts_with.push_back( "&" );

        strings.push_back        ( "Hello World" );
        starts_with.push_back    ( "Hello" );
        not_starts_with.push_back( "Hello\t" );

        strings.push_back        ( "         " );
        starts_with.push_back    ( "         " );
        not_starts_with.push_back( "          " );

        strings.push_back        ( "γειά σου Κόσμε!" );
        starts_with.push_back    ( "γ" );
        not_starts_with.push_back( "ε" );

        strings.push_back        ( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
        starts_with.push_back    ( "ጺጹጸጷጶጵ" );
        not_starts_with.push_back( "ጺጹጷጸጶጵ" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( starts_with, StartsWithFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_TRUE(
                fixture->strings[ i ].starts_with( fixture->starts_with[ i ] )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->strings[ i ].starts_with(
                fixture->not_starts_with[ i ] ) );
    }
}

//------------------------------------------------------------------------------
//                                   ENDS WITH
//------------------------------------------------------------------------------

class EndsWithFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > strings;
    std::vector< chaos::uni::UTF8String > ends_with;
    std::vector< chaos::uni::UTF8String > not_ends_with;


    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        strings.push_back      ( "" );
        ends_with.push_back    ( "" );
        not_ends_with.push_back( "+" );

        strings.push_back      ( "(" );
        ends_with.push_back    ( "(" );
        not_ends_with.push_back( "&" );

        strings.push_back      ( "Hello World" );
        ends_with.push_back    ( "World" );
        not_ends_with.push_back( "\tWorld" );

        strings.push_back      ( "         " );
        ends_with.push_back    ( "         " );
        not_ends_with.push_back( "          " );

        strings.push_back      ( "γειά σου Κόσμε!" );
        ends_with.push_back    ( "!" );
        not_ends_with.push_back( "γ" );

        strings.push_back      ( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
        ends_with.push_back    ( "ጮጭጬᚡ" );
        not_ends_with.push_back( "ጵጴጳጲጱጰ" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( ends_with, EndsWithFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_TRUE(
                fixture->strings[ i ].ends_with( fixture->ends_with[ i ] )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->strings[ i ].ends_with(
                fixture->not_ends_with[ i ] ) );
    }
}

//------------------------------------------------------------------------------
//                                   FIND FIRST
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( find_first, FindFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->strings[ i ].find_first( fixture->find[ i ] ),
                fixture->first_results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   FIND LAST
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( find_last, FindFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->strings[ i ].find_last( fixture->find[ i ] ),
                fixture->last_results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                     SPLIT
//------------------------------------------------------------------------------

class SplitFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String >                strings;
    std::vector< chaos::uni::UTF8String >                delimiters;
    std::vector< std::vector< chaos::uni::UTF8String > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            strings.push_back   ( "" );
            delimiters.push_back( "!" );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "Hello" );
            delimiters.push_back( "ጬ" );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "Hello" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "split this string" );
            delimiters.push_back( " " );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "split" );
            r.push_back( "this" );
            r.push_back( "string" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "." );
            delimiters.push_back( "." );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "" );
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "γειά σου Κόσμε!" );
            delimiters.push_back( "!" );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "γειά σου Κόσμε" );
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "γειά σου Κόσμε!" );
            delimiters.push_back( "ε" );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "γ" );
            r.push_back( "ιά σου Κόσμ" );
            r.push_back( "!" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
            delimiters.push_back( "ጺ" );
            std::vector< chaos::uni::UTF8String > r;
            r.push_back( "" );
            r.push_back( "ጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
            results.push_back( r );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( split, SplitFixture )
{
    std::vector< std::vector< chaos::uni::UTF8String > > all_elements;
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        std::vector< chaos::uni::UTF8String > elements =
                fixture->strings[ i ].split( fixture->delimiters[ i ] );
        all_elements.push_back( elements );
    }

    CHAOS_TEST_MESSAGE( "Checking elements length" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                all_elements[ i ].size(),
                fixture->results[ i ].size()
        );
    }

    CHAOS_TEST_MESSAGE( "Checking elements contents" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        std::size_t check_count = std::min(
                all_elements[ i ].size(),
                fixture->results[ i ].size()
        );

        for ( std::size_t j = 0; j < check_count; ++j )
        {
            CHAOS_CHECK_EQUAL(
                    all_elements[ i ][ j ],
                    fixture->results[ i ][ j ]
            );
        }
    }

    CHAOS_TEST_MESSAGE( "Checking empty delimiters" );
    CHAOS_FOR_EACH( it, fixture->strings )
    {
        CHAOS_CHECK_THROW(
                it->split( ""),
                chaos::ex::ValueError
        );
    }
}

//------------------------------------------------------------------------------
//                               REMOVE DUPLICATES
//------------------------------------------------------------------------------

class RemoveDuplicatesFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > inputs;
    std::vector< chaos::uni::UTF8String > substrings;
    std::vector< chaos::uni::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        inputs.push_back( "" );
        substrings.push_back( "_" );
        results.push_back( "" );

        inputs.push_back( "HelloWorld" );
        substrings.push_back( "_" );
        results.push_back( "HelloWorld" );

        inputs.push_back( "Hello_World" );
        substrings.push_back( "_" );
        results.push_back( "Hello_World" );

        inputs.push_back( "Hello  World" );
        substrings.push_back( "" );
        results.push_back( "Hello  World" );

        inputs.push_back( "Hello__World" );
        substrings.push_back( "_" );
        results.push_back( "Hello_World" );

        inputs.push_back( "__Hello__World__" );
        substrings.push_back( "_" );
        results.push_back( "_Hello_World_" );

        inputs.push_back( "Hello World" );
        substrings.push_back( "Hello World!" );
        results.push_back( "Hello World" );

        inputs.push_back( "__!!Hello__!!__World__!!" );
        substrings.push_back( "!" );
        results.push_back( "__!Hello__!__World__!" );

        inputs.push_back( "@@@@@Hello@@@@World@@@" );
        substrings.push_back( "@@" );
        results.push_back( "@@@Hello@@World@@@" );

        inputs.push_back( "γειάγειάHelloγειάγειάγειάWorldγειάγει" );
        substrings.push_back( "γειά" );
        results.push_back( "γειάHelloγειάWorldγειάγει" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( remove_duplicates, RemoveDuplicatesFixture )
{
    for( std::size_t i = 0; i < fixture->inputs.size(); ++i )
    {
        fixture->inputs[ i ].remove_duplicates( fixture->substrings[ i ] );
        CHAOS_CHECK_EQUAL(
                fixture->inputs[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                     IS INT
//------------------------------------------------------------------------------

class IsIntFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > ints;
    std::vector< chaos::uni::UTF8String > not_ints;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        ints.push_back( "0" );
        ints.push_back( "1" );
        ints.push_back( "-0" );
        ints.push_back( "712" );
        ints.push_back( "-225" );
        ints.push_back( "874794" );
        ints.push_back( "-59803" );
        ints.push_back( "34259806260490234" );
        ints.push_back( "-728598729572057340" );
        ints.push_back( "983425235923857925803257938503245782623423541085097" );
        ints.push_back( "-34589023459205825709574513753154039580418045843051" );

        not_ints.push_back( "" );
        not_ints.push_back( "a" );
        not_ints.push_back( "0p" );
        not_ints.push_back( "--48" );
        not_ints.push_back( "43252-" );
        not_ints.push_back( "3-67" );
        not_ints.push_back( "-32432k989" );
        not_ints.push_back( "a82409f" );
        not_ints.push_back( "Hello World!" );
        not_ints.push_back( "γειά σου Κόσμε" );
        not_ints.push_back( "ጲጱጰጯጮጭ" );
        not_ints.push_back( "_08723457925" );
        not_ints.push_back( "342576594569252542670625925925623957252956296ጮ" );
        not_ints.push_back( "0xd7" );
        not_ints.push_back( "0x64" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( is_int, IsIntFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->ints.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->ints[ i ].is_int() );
    }

    CHAOS_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_ints.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->not_ints[ i ].is_int() );
    }
}

//------------------------------------------------------------------------------
//                                    IS UINT
//------------------------------------------------------------------------------

class IsUintFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > uints;
    std::vector< chaos::uni::UTF8String > not_uints;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        uints.push_back( "0" );
        uints.push_back( "1" );
        uints.push_back( "34" );
        uints.push_back( "712" );
        uints.push_back( "225" );
        uints.push_back( "874794" );
        uints.push_back( "59803" );
        uints.push_back( "34259806260490234" );
        uints.push_back( "728598729572057340" );
        uints.push_back( "98342523592385792580325793850324578262343541085097" );
        uints.push_back( "34589023459205825709574513753154039580418045843051" );

        not_uints.push_back( "" );
        not_uints.push_back( "a" );
        not_uints.push_back( "0p" );
        not_uints.push_back( "-0" );
        not_uints.push_back( "-324328989" );
        not_uints.push_back( "a82409f" );
        not_uints.push_back( "Hello World!" );
        not_uints.push_back( "γειά σου Κόσμε" );
        not_uints.push_back( "ጲጱጰጯጮጭ" );
        not_uints.push_back( "_08723457925" );
        not_uints.push_back( "34257659456925254267062592925623957252956296ጮ" );
        not_uints.push_back( "0xd7" );
        not_uints.push_back( "0x64" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( is_uint, IsUintFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->uints.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->uints[ i ].is_uint() );
    }

    CHAOS_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_uints.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->not_uints[ i ].is_uint() );
    }
}

//------------------------------------------------------------------------------
//                                    IS FLOAT
//------------------------------------------------------------------------------

class IsFloatFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > floats;
    std::vector< chaos::uni::UTF8String > not_floats;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        floats.push_back( "0" );
        floats.push_back( ".0" );
        floats.push_back( "-.0" );
        floats.push_back( "-536." );
        floats.push_back( "-21414." );
        floats.push_back( ".435345" );
        floats.push_back( "0.3453564" );
        floats.push_back( "-345345.457657" );
        floats.push_back( "59803.878933" );
        floats.push_back( "34259806260490234435935.4357893573985739856015434" );
        floats.push_back( ".745893583459038593048530598359828598729572057340" );
        floats.push_back( "-983.42523592385792580325793850324578262343510850" );
        floats.push_back( "345890234592058257095745137531540395804.180458405" );
        floats.push_back( "-348" );

        not_floats.push_back( "0.0F" );
        not_floats.push_back( "3432432.4553534f" );
        not_floats.push_back( "435346,657657" );
        not_floats.push_back( "+5463465.3756538" );
        not_floats.push_back( "324328-989" );
        not_floats.push_back( "324920489325.75843578923572985725ጮ" );
        not_floats.push_back( "Hello World!" );
        not_floats.push_back( "γειά σου Κόσμε" );
        not_floats.push_back( "ጲጱጰጯጮጭ" );
        not_floats.push_back( "4359835..45892345825" );
        not_floats.push_back( "3425765945692525426..706259292562395725295626" );
        not_floats.push_back( "0xd7" );
        not_floats.push_back( "0x64" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( is_float, IsFloatFixture )
{
    CHAOS_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->floats[ i ].is_float() );
    }

    CHAOS_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_floats.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->not_floats[ i ].is_float() );
    }
}

//------------------------------------------------------------------------------
//                                   SUBSTRING
//------------------------------------------------------------------------------

class SubstringFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > strings;
    std::vector< std::size_t >                 indices;
    std::vector< std::size_t >                 lengths;
    std::vector< chaos::uni::UTF8String > results;
    std::vector< std::size_t >                 out_of_bounds;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        strings.push_back( "Hello World" );
        indices.push_back( 0 );
        lengths.push_back( 5 );
        results.push_back( "Hello" );
        out_of_bounds.push_back( 89 );

        strings.push_back( "Hello World" );
        indices.push_back( 11 );
        lengths.push_back( 1 );
        results.push_back( "" );
        out_of_bounds.push_back( 734 );

        strings.push_back( " " );
        indices.push_back( 0 );
        lengths.push_back( 0 );
        results.push_back( "" );
        out_of_bounds.push_back( 2 );

        strings.push_back( "γειά σου Κόσμε!" );
        indices.push_back( 8 );
        lengths.push_back( 6 );
        results.push_back( " Κόσμε" );
        out_of_bounds.push_back( 23 );

        strings.push_back( "this is a مزيج of text" );
        indices.push_back( 12 );
        lengths.push_back( 1 );
        results.push_back( "ي" );
        out_of_bounds.push_back( 1247832429 );

        strings.push_back( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
        indices.push_back( 13 );
        lengths.push_back( 14353458 );
        results.push_back( "ጭጬᚡ" );
        out_of_bounds.push_back( 832 );
    }
};

CHAOS_TEST_UNIT_FIXTURE( substring, SubstringFixture )
{
    CHAOS_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->strings[ i ].substring(
                        fixture->indices[ i ], fixture->lengths[ i ]
                ),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_THROW(
                fixture->strings[ i ].substring(
                        fixture->out_of_bounds[ i ], 10
                ),
                chaos::ex::IndexOutOfBoundsError
        );
    }
}

//------------------------------------------------------------------------------
//                                 TO STD STRING
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( to_std_string, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->utf8_strings[ i ].to_std_string(),
                std::string( fixture->cstrings[ i ] )
        );
    }
}

//------------------------------------------------------------------------------
//                                    TO BOOL
//------------------------------------------------------------------------------

class ToBoolFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > valid;
    std::vector< bool >                   results;
    std::vector< chaos::uni::UTF8String > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        valid.push_back( "0" );
        results.push_back( false );

        valid.push_back( "1" );
        results.push_back( true );

        valid.push_back( "000000" );
        results.push_back( false );

        valid.push_back( "0000001" );
        results.push_back( true );

        valid.push_back( "100000000" );
        results.push_back( true );

        valid.push_back( "100001000000" );
        results.push_back( true );

        valid.push_back( "2" );
        results.push_back( true );

        valid.push_back( "5475325" );
        results.push_back( true );

        valid.push_back( "-23" );
        results.push_back( true );

        valid.push_back( "-2" );
        results.push_back( true );

        invalid.push_back( "o" );
        invalid.push_back( "0a" );
        invalid.push_back( "0XFF" );
        invalid.push_back( "0X67" );
        invalid.push_back( " 3457835" );
        invalid.push_back( "0 " );
        invalid.push_back( "yes 0" );
        invalid.push_back( "Hello World" );
        invalid.push_back( "γειά σου Κόσμε" );
        invalid.push_back( "this is a مزيج of text" );
        invalid.push_back( "간" );
        invalid.push_back( " " );
        invalid.push_back( "\n0" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( to_bool, ToBoolFixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->valid[ i ].to_bool(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid cases" );
    CHAOS_FOR_EACH( it, fixture->invalid )
    {
        CHAOS_CHECK_THROW( it->to_bool(), chaos::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                    TO INT32
//------------------------------------------------------------------------------

class ToInt32Fixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > valid;
    std::vector< chaos::int32 >           results;
    std::vector< chaos::uni::UTF8String > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        valid.push_back( "0" );
        results.push_back( 0 );

        valid.push_back( "1" );
        results.push_back( 1 );

        valid.push_back( "000000" );
        results.push_back( 0 );

        valid.push_back( "0000001" );
        results.push_back( 1 );

        valid.push_back( "100000000" );
        results.push_back( 100000000 );

        valid.push_back( "100001000" );
        results.push_back( 100001000 );

        valid.push_back( "2" );
        results.push_back( 2 );

        valid.push_back( "5475325" );
        results.push_back( 5475325 );

        valid.push_back( "-23" );
        results.push_back( -23 );

        valid.push_back( "-2" );
        results.push_back( -2 );

        valid.push_back( "-34589345" );
        results.push_back( -34589345 );

        invalid.push_back( "o" );
        invalid.push_back( "0a" );
        invalid.push_back( "0XFF" );
        invalid.push_back( "0X67" );
        invalid.push_back( " 3457835" );
        invalid.push_back( "0 " );
        invalid.push_back( "yes 0" );
        invalid.push_back( "Hello World" );
        invalid.push_back( "γειά σου Κόσμε" );
        invalid.push_back( "this is a مزيج of text" );
        invalid.push_back( "간" );
        invalid.push_back( " " );
        invalid.push_back( "\n0" );
        invalid.push_back( "435345834h95" );
        invalid.push_back( "3.6" );
        invalid.push_back( "345345L" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( to_int32, ToInt32Fixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->valid[ i ].to_int32(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid cases" );
    CHAOS_FOR_EACH( it, fixture->invalid )
    {
        CHAOS_CHECK_THROW( it->to_int32(), chaos::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   TO UINT32
//------------------------------------------------------------------------------

class ToUint32Fixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > valid;
    std::vector< chaos::uint32 >          results;
    std::vector< chaos::uni::UTF8String > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        valid.push_back( "0" );
        results.push_back( 0 );

        valid.push_back( "1" );
        results.push_back( 1 );

        valid.push_back( "000000" );
        results.push_back( 0 );

        valid.push_back( "0000001" );
        results.push_back( 1 );

        valid.push_back( "100000000" );
        results.push_back( 100000000 );

        valid.push_back( "100001000" );
        results.push_back( 100001000 );

        valid.push_back( "2" );
        results.push_back( 2 );

        valid.push_back( "5475325" );
        results.push_back( 5475325 );

        valid.push_back( "437583530" );
        results.push_back( 437583530 );

        invalid.push_back( "o" );
        invalid.push_back( "0a" );
        invalid.push_back( "0XFF" );
        invalid.push_back( "0X67" );
        invalid.push_back( " 3457835" );
        invalid.push_back( "0 " );
        invalid.push_back( "yes 0" );
        invalid.push_back( "Hello World" );
        invalid.push_back( "γειά σου Κόσμε" );
        invalid.push_back( "this is a مزيج of text" );
        invalid.push_back( "간" );
        invalid.push_back( " " );
        invalid.push_back( "\n0" );
        invalid.push_back( "435345834h95" );
        invalid.push_back( "3.6" );
        invalid.push_back( "345345L" );
        invalid.push_back( "-0" );
        invalid.push_back( "- 435345" );
        invalid.push_back( "-1342" );
        invalid.push_back( "-943589345" );
        invalid.push_back( "-435384573958" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( to_uint32, ToUint32Fixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->valid[ i ].to_uint32(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid cases" );
    CHAOS_FOR_EACH( it, fixture->invalid )
    {
        CHAOS_CHECK_THROW( it->to_uint32(), chaos::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                    TO INT64
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( to_int64, ToInt32Fixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->valid[ i ].to_int64(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid cases" );
    CHAOS_FOR_EACH( it, fixture->invalid )
    {
        CHAOS_CHECK_THROW( it->to_int64(), chaos::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   TO UINT64
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( to_uint64, ToUint32Fixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->valid[ i ].to_uint64(),
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid cases" );
    CHAOS_FOR_EACH( it, fixture->invalid )
    {
        CHAOS_CHECK_THROW( it->to_uint64(), chaos::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   GET LENGTH
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_length, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->utf8_strings[ i ].get_length(),
                fixture->lengths[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                    IS EMPTY
//------------------------------------------------------------------------------

class IsEmptyFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > strings;
    std::vector< bool >                   results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        strings.push_back( "!" );
        results.push_back( false );

        strings.push_back( "" );
        results.push_back( true );

        strings.push_back( "Hello World" );
        results.push_back( false );

        strings.push_back( "γειά σου Κόσμε" );
        results.push_back( false );

        strings.push_back( "this is a مزيج of text" );
        results.push_back( false );

        strings.push_back( "간" );
        results.push_back( false );
    }
};

CHAOS_TEST_UNIT_FIXTURE( is_empty, IsEmptyFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->strings[ i ].is_empty(),
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   GET SYMBOL
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_symbol, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
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

//------------------------------------------------------------------------------
//                                GET SYMBOL VALUE
//------------------------------------------------------------------------------

class GetSymbolValueFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::uni::UTF8String       symbols;
    std::vector< chaos::uint32 > values;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        symbols << "a";
        values.push_back( 0x61 );

        symbols << "f";
        values.push_back( 0x66 );

        symbols << "0";
        values.push_back( 0x30 );

        symbols << "Z";
        values.push_back( 0x5A );

        symbols << "`";
        values.push_back( 0x60 );

        symbols << "$";
        values.push_back( 0x24 );

        symbols << ">";
        values.push_back( 0x3E );

        symbols << "¡";
        values.push_back( 0xA1C2 );

        symbols << "¢";
        values.push_back( 0xA2C2 );

        symbols << "Ħ";
        values.push_back( 0xA6C4 );

        symbols << "͚";
        values.push_back( 0x9ACD );

        symbols << "؟";
        values.push_back( 0x9FD8 );

        symbols << "ॐ";
        values.push_back( 0x90A5E0 );

        symbols << "ൠ";
        values.push_back( 0xA0B5E0 );

        symbols << "ቓ";
        values.push_back( 0x9389E1 );

        symbols << "ᕔ";
        values.push_back( 0x9495E1 );

        symbols << "ᴫ";
        values.push_back( 0xABB4E1 );

        symbols << "Ṥ";
        values.push_back( 0xA4B9E1 );

        symbols << "ᾤ";
        values.push_back( 0xA4BEE1 );

        symbols << "※";
        values.push_back( 0xBB80E2 );

        symbols << "→";
        values.push_back( 0x9286E2 );

        symbols << "∴";
        values.push_back( 0xB488E2 );

        symbols << "𐂩";
        values.push_back( 0xA98290F0 );

        symbols << "𐃮";
        values.push_back( 0xAE8390F0 );

        symbols << "𐀠";
        values.push_back( 0xA08090F0 );

        symbols << "𐁙";
        values.push_back( 0x998190F0 );
    }
};

CHAOS_TEST_UNIT_FIXTURE( get_symbol_value, GetSymbolValueFixture )
{
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_symbol_value( i ),
                fixture->values[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                 GET CODE POINT
//------------------------------------------------------------------------------

class GetCodePointFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::uni::UTF8String       symbols;
    std::vector< chaos::uint32 > code_points;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        symbols << "a";
        code_points.push_back( 0x61 );

        symbols << "f";
        code_points.push_back( 0x66 );

        symbols << "0";
        code_points.push_back( 0x30 );

        symbols << "Z";
        code_points.push_back( 0x5A );

        symbols << "`";
        code_points.push_back( 0x60 );

        symbols << "$";
        code_points.push_back( 0x24 );

        symbols << ">";
        code_points.push_back( 0x3E );

        symbols << "¡";
        code_points.push_back( 0xA1 );

        symbols << "Ģ";
        code_points.push_back( 0x0122 );

        symbols << "Σ";
        code_points.push_back( 0x3A3 );

        symbols << "Ο";
        code_points.push_back( 0x39F );

        symbols << "ޟ";
        code_points.push_back( 0x79F );

        symbols << "࠴";
        code_points.push_back( 0x834 );

        symbols << "ঃ";
        code_points.push_back( 0x983 );

        symbols << "४";
        code_points.push_back( 0x96A );

        symbols << "ආ";
        code_points.push_back( 0xD86 );

        symbols << "൶";
        code_points.push_back( 0xD76 );

        symbols << "ᐖ";
        code_points.push_back( 0x1416 );

        symbols << "Ⅎ";
        code_points.push_back( 0x2132 );

        symbols << "⡚";
        code_points.push_back( 0x285A );

        symbols << "𖬏";
        code_points.push_back( 0x16B0F );

        symbols << "𛲢";
        code_points.push_back( 0x1BCA2 );

        symbols << "𝄞";
        code_points.push_back( 0x1D11E );

        symbols << "𝇜";
        code_points.push_back( 0x1D1DC );

        symbols << "𝓍";
        code_points.push_back( 0x1D4CD );

        symbols << "😼";
        code_points.push_back( 0x1F63C );
    }
};

CHAOS_TEST_UNIT_FIXTURE( get_code_point, GetCodePointFixture )
{
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_code_point( i ),
                fixture->code_points[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                        GET BYTE INDEX FOR SYMBOL INDEX
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_byte_index_for_symbol_index, IndexFixture )
{
    CHAOS_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_byte_index_for_symbol_index( i ),
                fixture->byte_indices[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    CHAOS_CHECK_THROW(
            fixture->symbols.get_byte_index_for_symbol_index( 58435 ),
            chaos::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                GET SYMBOL WIDTH
//------------------------------------------------------------------------------

class GetSymbolWidthFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::uni::UTF8String       symbols;
    std::vector< chaos::uint32 > widths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        symbols << "a";
        widths.push_back( 1 );

        symbols << "f";
        widths.push_back( 1 );

        symbols << "0";
        widths.push_back( 1 );

        symbols << "Z";
        widths.push_back( 1 );

        symbols << "`";
        widths.push_back( 1 );

        symbols << "$";
        widths.push_back( 1 );

        symbols << ">";
        widths.push_back( 1 );

        symbols << "¡";
        widths.push_back( 2 );

        symbols << "ø";
        widths.push_back( 2 );

        symbols << "Ȼ";
        widths.push_back( 2 );

        symbols << "Ф";
        widths.push_back( 2 );

        symbols << "Թ";
        widths.push_back( 2 );

        symbols << "ः";
        widths.push_back( 3 );

        symbols << "ക";
        widths.push_back( 3 );

        symbols << "ན";
        widths.push_back( 3 );

        symbols << "᎗";
        widths.push_back( 3 );

        symbols << "ᔹ";
        widths.push_back( 3 );

        symbols << "Ḝ";
        widths.push_back( 3 );

        symbols << "ℝ";
        widths.push_back( 3 );

        symbols << "ℬ";
        widths.push_back( 3 );

        symbols << "⌆";
        widths.push_back( 3 );

        symbols << "𐂣";
        widths.push_back( 4 );

        symbols << "𐃕";
        widths.push_back( 4 );

        symbols << "𐃴";
        widths.push_back( 4 );

        symbols << "𐃹";
        widths.push_back( 4 );
    }
};

CHAOS_TEST_UNIT_FIXTURE( get_symbol_width, GetSymbolWidthFixture )
{
    CHAOS_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_symbol_width( i ),
                fixture->widths[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    CHAOS_CHECK_THROW(
            fixture->symbols.get_symbol_width( 832423 ),
            chaos::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                    GET RAW
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_raw, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( strcmp(
                fixture->utf8_strings[ i ].get_raw(),
                fixture->cstrings[ i ]
        ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                GET BYTE LENGTH
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_byte_length, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->utf8_strings[ i ].get_byte_length(),
                strlen( fixture->cstrings[ i ] ) + 1
        );
    }
}

//------------------------------------------------------------------------------
//                        GET SYMBOL INDEX FOR BYTE INDEX
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_symbol_index_for_byte_index, IndexFixture )
{
    CHAOS_TEST_MESSAGE( "Checking values" );
    std::size_t symbol_index = 0;
    for ( std::size_t i = 0; i < fixture->symbols.get_byte_length() - 1; ++i )
    {
        if ( symbol_index < fixture->symbols.get_length() - 1 &&
             i >= fixture->byte_indices[ symbol_index + 1 ] )
        {
            ++symbol_index;
        }

        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_symbol_index_for_byte_index( i ),
                symbol_index
        );
    }

    CHAOS_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    CHAOS_CHECK_THROW(
            fixture->symbols.get_symbol_index_for_byte_index( 512 ),
            chaos::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                 GET BYTE WIDTH
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_byte_width, GetSymbolWidthFixture )
{
    CHAOS_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        std::size_t byte_index =
                fixture->symbols.get_byte_index_for_symbol_index( i );

        CHAOS_CHECK_EQUAL(
                fixture->symbols.get_byte_width( byte_index ),
                fixture->widths[ i ]
        );

        i += fixture->widths[ i ];
    }

    CHAOS_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    CHAOS_CHECK_THROW(
            fixture->symbols.get_byte_width( chaos::uni::npos ),
            chaos::ex::IndexOutOfBoundsError
    );
}

} // namespace utf8_string_tests

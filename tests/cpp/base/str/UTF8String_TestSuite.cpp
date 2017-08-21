#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.str.UTF8String)

#include <algorithm>
#include <cstring>

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/str/UTF8String.hpp"

namespace
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class UTF8StringGenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    // cstrings
    std::vector<const char*> cstrings;
    // lengths
    std::vector< std::size_t > lengths;
    // utf8strings
    std::vector< arc::str::UTF8String > utf8_strings;
    // symbols
    std::vector< std::map< std::size_t, arc::str::UTF8String > > symbols;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // populate cstring data
        cstrings.push_back( "" );
        lengths.push_back( 0 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "Hello World" );
        lengths.push_back( 11 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = arc::str::UTF8String( "H" );
            symbol_map[ 3  ] = arc::str::UTF8String( "l" );
            symbol_map[ 7  ] = arc::str::UTF8String( "o" );
            symbol_map[ 10 ] = arc::str::UTF8String( "d" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "a" );
        lengths.push_back( 1 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0 ] = arc::str::UTF8String( "a" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "This is a really long string, that just keeps on "
                            "going on and on and on! It never seems to end, "
                            "but just when you think that it will not end. It "
                            "ends.\n\n\n\n\nNope still going here.\t\t\tThe "
                            "end!\n\n\n\t\t\t"
        );
        lengths.push_back( 194 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0   ] = arc::str::UTF8String( "T" );
            symbol_map[ 5   ] = arc::str::UTF8String( "i" );
            symbol_map[ 34  ] = arc::str::UTF8String( " " );
            symbol_map[ 87  ] = arc::str::UTF8String( " " );
            symbol_map[ 88  ] = arc::str::UTF8String( "t" );
            symbol_map[ 100 ] = arc::str::UTF8String( "j" );
            symbol_map[ 125 ] = arc::str::UTF8String( "i" );
            symbol_map[ 167 ] = arc::str::UTF8String( "o" );
            symbol_map[ 190 ] = arc::str::UTF8String( "\n" );
            symbol_map[ 193 ] = arc::str::UTF8String( "\t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "γειά σου Κόσμε" );
        lengths.push_back( 14 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = arc::str::UTF8String( "γ" );
            symbol_map[ 1  ] = arc::str::UTF8String( "ε" );
            symbol_map[ 5  ] = arc::str::UTF8String( "σ" );
            symbol_map[ 8  ] = arc::str::UTF8String( " " );
            symbol_map[ 11 ] = arc::str::UTF8String( "σ" );
            symbol_map[ 13 ] = arc::str::UTF8String( "ε" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "this is a مزيج of text" );
        lengths.push_back( 22 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = arc::str::UTF8String( "t" );
            symbol_map[ 2  ] = arc::str::UTF8String( "i" );
            symbol_map[ 9  ] = arc::str::UTF8String( " " );
            symbol_map[ 11 ] = arc::str::UTF8String( "ز" );
            symbol_map[ 13 ] = arc::str::UTF8String( "ج" );
            symbol_map[ 15 ] = arc::str::UTF8String( "o" );
            symbol_map[ 18 ] = arc::str::UTF8String( "t" );
            symbol_map[ 20 ] = arc::str::UTF8String( "x" );
            symbol_map[ 21 ] = arc::str::UTF8String( "t" );
            symbols.push_back( symbol_map );
        }

        cstrings.push_back( "간" );
        lengths.push_back( 1 );
        {
            std::map< std::size_t, arc::str::UTF8String > symbol_map;
            symbol_map[ 0  ] = arc::str::UTF8String( "간" );
            symbols.push_back( symbol_map );
        }

        // copy to utf8string data
        ARC_FOR_EACH( it, cstrings )
        {
            utf8_strings.push_back( arc::str::UTF8String( *it ) );
        }
    }
};

//------------------------------------------------------------------------------
//                                ADDITION FIXTURE
//------------------------------------------------------------------------------

class ConcatenateFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::str::UTF8String > comp_2;
    std::vector< arc::str::UTF8String > results;

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

class RepeatFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp;
    std::vector< arc::uint32 >          count;
    std::vector< arc::str::UTF8String > results;

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

class FindFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > strings;
    std::vector< arc::str::UTF8String > find;
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
        first_results.push_back( arc::str::npos );
        last_results.push_back( arc::str::npos );

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
        first_results.push_back( arc::str::npos );
        last_results.push_back( arc::str::npos );
    }
};

//------------------------------------------------------------------------------
//                                 INDEX FIXTURE
//------------------------------------------------------------------------------

class IndexFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::str::UTF8String       symbols;
    std::vector< arc::uint32 > byte_indices;

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

ARC_TEST_UNIT( default_constructor )
{
    arc::str::UTF8String empty;
    ARC_CHECK_EQUAL(
            empty.get_length(),
            static_cast< std::size_t >( 0 )
    );
    ARC_CHECK_EQUAL(
            empty.get_byte_length(),
            static_cast< std::size_t >( 1 )
    );
}

//------------------------------------------------------------------------------
//                              CSTRING CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( cstring_constructor, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->cstrings )
    {
        arc::str::UTF8String v( *it );
        ARC_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                         CSTRING AND LENGTH CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( cstring_length_constructor, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->cstrings )
    {
        arc::str::UTF8String v( *it, strlen( *it ) );
        ARC_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( copy_constructor, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->utf8_strings )
    {
        arc::str::UTF8String copy( *it );
        ARC_CHECK_EQUAL( copy, *it );
        ARC_CHECK_EQUAL( strcmp( copy.get_raw(), it->get_raw() ), 0 );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( assignment_operator, UTF8StringGenericFixture )
{
    // populate strings to assign to
    std::vector< arc::str::UTF8String > assigns;
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        assigns.push_back( "data will be overridden" );
    }

    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        arc::str::UTF8String r = assigns[ i ] = fixture->utf8_strings[ i ];
        ARC_CHECK_EQUAL( r, assigns[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking length" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                assigns[ i ].get_byte_length(),
                fixture->utf8_strings[ i ].get_byte_length()
        );
        ARC_CHECK_EQUAL(
                strlen( assigns[ i ].get_raw() ),
                strlen( fixture->utf8_strings[ i ].get_raw() )
        );
    }

    ARC_TEST_MESSAGE( "Checking contents match" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL( assigns[ i ], fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( equality_operator, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking from literal data" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        arc::str::UTF8String v( fixture->cstrings[ i ] );
        ARC_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking from copy constructor" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        arc::str::UTF8String v( fixture->utf8_strings[ i ] );
        ARC_CHECK_EQUAL( v, fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( inequality_operator, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking from literal data" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        arc::str::UTF8String v( "this שטריקל is not the same" );
        ARC_CHECK_NOT_EQUAL( v, fixture->utf8_strings[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking from copy constructor" );
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        arc::str::UTF8String org( "this שטריקל is not the same" );
        arc::str::UTF8String v( org );
        ARC_CHECK_NOT_EQUAL( v, fixture->utf8_strings[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               LESS THAN OPERATOR
//------------------------------------------------------------------------------

class LessThanFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > less;
    std::vector< arc::str::UTF8String > more;

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

ARC_TEST_UNIT_FIXTURE( less_than_operator, LessThanFixture )
{
    ARC_TEST_MESSAGE( "Checking less than cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->less[ i ] < fixture->more[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking greater than cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->more[ i ] < fixture->less[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking equals cases" );
    for ( std::size_t i = 0; i < fixture->less.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->less[ i ] < fixture->less[ i ] );
    }
    for ( std::size_t i = 0; i < fixture->more.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->more[ i ] < fixture->more[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( addition_operator, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] + fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                           COMPOUND ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( compound_addition_operator, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] += fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                            MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( multiplication_operator, RepeatFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp[ i ] * fixture->count[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                        COMPOUND MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( compound_multiplication_operator, RepeatFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp[ i ] *= fixture->count[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              UTF8 STREAM OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( utf8_stream_operator, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                            CSTRING STREAM OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( cstring_stream_operator, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ].get_raw(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                           STD STRING STREAM OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( stdstring_stream_operator, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ].to_std_string(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              BOOL STREAM OPERATOR
//------------------------------------------------------------------------------

class BoolStreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< bool >                   comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( bool_stream_operator, BoolStreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              CHAR STREAM OPERATOR
//------------------------------------------------------------------------------

class CharStreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< char >                   comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( char_stream_operator, CharStreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INT8 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int8StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::int8 >            comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( int8_stream_operator, Int8StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT8 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint8StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::uint8 >           comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( uint8_stream_operator, Uint8StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT16 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int16StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::int16 >           comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( int16_stream_operator, Int16StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT16 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint16StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::uint16 >          comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( uint16_stream_operator, Uint16StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT32 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int32StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::int32 >           comp_2;
    std::vector< arc::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 2048 );
        results.push_back( "2048" );

        comp_1.push_back( "" );
        comp_2.push_back( -static_cast< arc::int32 >( 214483648 ) );
        results.push_back( "-214483648" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 2147483647 );
        results.push_back( "Hello2147483647" );

        comp_1.push_back( "Κόσμε" );
        comp_2.push_back( -64 );
        results.push_back( "Κόσμε-64" );
    }
};

ARC_TEST_UNIT_FIXTURE( int32_stream_operator, Int32StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT32 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint32StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::uint32 >          comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( uint32_stream_operator, Uint32StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             INT64 STREAM OPERATOR
//------------------------------------------------------------------------------

class Int64StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::int64 >           comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( int64_stream_operator, Int64StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             UINT64 STREAM OPERATOR
//------------------------------------------------------------------------------

class Uint64StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< arc::uint64 >          comp_2;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( uint64_stream_operator, Uint64StreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             FLOAT STREAM OPERATOR
//------------------------------------------------------------------------------

class FloatStreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > comp_1;
    std::vector< float >                  comp_2;
    std::vector< arc::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back( "" );
        comp_2.push_back( 0.0F );
        results.push_back( "0" );

        comp_1.push_back( "" );
        comp_2.push_back( 1.0F );
        results.push_back( "1" );

        comp_1.push_back( "" );
        comp_2.push_back( 3.14F );
        results.push_back( "3.14" );

        comp_1.push_back( "Hello" );
        comp_2.push_back( 12.3456F );
        results.push_back( "Hello12.3456" );

        comp_1.push_back( "Κόσμε " );
        comp_2.push_back( 0.00034F );
        results.push_back( "Κόσμε 0.00034" );
    }
};

ARC_TEST_UNIT_FIXTURE( float_stream_operator, FloatStreamOperatorFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ] << fixture->comp_2[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             DOUBLE STREAM OPERATOR
//------------------------------------------------------------------------------

class DoubleStreamOperator : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<arc::str::UTF8String> comp_1;
    std::vector<double> comp_2;
    std::vector<arc::str::UTF8String> results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_1.push_back("");
        comp_2.push_back(0.0);
        results.push_back("0");

        comp_1.push_back("");
        comp_2.push_back(1.0);
        results.push_back("1");

        comp_1.push_back("");
        comp_2.push_back(3.14);
        results.push_back("3.14");

        comp_1.push_back("Hello");
        comp_2.push_back(12.3456);
        results.push_back("Hello12.3456");

        comp_1.push_back("Κόσμε ");
        comp_2.push_back(0.00034);
        results.push_back("Κόσμε 0.00034");
    }
};

ARC_TEST_UNIT_FIXTURE(double_stream_operator, DoubleStreamOperator)
{
    ARC_TEST_MESSAGE("Checking return value");
    for (std::size_t i = 0; i < fixture->comp_1.size(); ++i)
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[i] << fixture->comp_2[i],
                fixture->results[i]
        );
    }

    ARC_TEST_MESSAGE("Checking in place modification" );
    for (std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(fixture->comp_1[i], fixture->results[i]);
    }
}

//------------------------------------------------------------------------------
//                                 CSTRING ASSIGN
//------------------------------------------------------------------------------


ARC_TEST_UNIT_FIXTURE( cstring_assign, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->cstrings )
    {
        arc::str::UTF8String v;
        v.assign( *it );
        ARC_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                           CSTRING AND LENGTH ASSIGN
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( cstring_length_assign, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->cstrings )
    {
        arc::str::UTF8String v;
        v.assign( *it, strlen( *it ) );
        ARC_CHECK_EQUAL( strcmp( v.get_raw(), *it ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                  UTF8 ASSIGN
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( utf8_assign, UTF8StringGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking internal data matches original string" );
    ARC_FOR_EACH( it, fixture->utf8_strings )
    {
        arc::str::UTF8String v;
        v.assign( *it );
        ARC_CHECK_EQUAL( v, *it );
        ARC_CHECK_EQUAL( strcmp( v.get_raw(), it->get_raw() ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                     CLAIM
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(claim, UTF8StringGenericFixture)
{
    ARC_FOR_EACH(it, fixture->cstrings)
    {
        // copy the string first
        std::size_t length = strlen(*it) + 1;
        char* copy = new char[length];
        memcpy(copy, *it, length);

        arc::str::UTF8String v;
        v.claim(copy);
        ARC_CHECK_EQUAL(strcmp( v.get_raw(), *it), 0);
    }
}

//------------------------------------------------------------------------------
//                                  CONCATENATE
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( concatenate, ConcatenateFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp_1[ i ].concatenate( fixture->comp_2[ i ] ),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp_1[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                     REPEAT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( repeat, RepeatFixture )
{
    ARC_TEST_MESSAGE( "Checking return value" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->comp[ i ].repeat( fixture->count[ i ] ),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking in place modification" );
    for ( std::size_t i = 0; i < fixture->comp.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->comp[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                  STARTS WITH
//------------------------------------------------------------------------------

class StartsWithFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > strings;
    std::vector< arc::str::UTF8String > starts_with;
    std::vector< arc::str::UTF8String > not_starts_with;


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

ARC_TEST_UNIT_FIXTURE( starts_with, StartsWithFixture )
{
    ARC_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_TRUE(
                fixture->strings[ i ].starts_with( fixture->starts_with[ i ] )
        );
    }

    ARC_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->strings[ i ].starts_with(
                fixture->not_starts_with[ i ] ) );
    }
}

//------------------------------------------------------------------------------
//                                   ENDS WITH
//------------------------------------------------------------------------------

class EndsWithFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > strings;
    std::vector< arc::str::UTF8String > ends_with;
    std::vector< arc::str::UTF8String > not_ends_with;


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

ARC_TEST_UNIT_FIXTURE( ends_with, EndsWithFixture )
{
    ARC_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_TRUE(
                fixture->strings[ i ].ends_with( fixture->ends_with[ i ] )
        );
    }

    ARC_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->strings[ i ].ends_with(
                fixture->not_ends_with[ i ] ) );
    }
}

//------------------------------------------------------------------------------
//                                   FIND FIRST
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( find_first, FindFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->strings[ i ].find_first( fixture->find[ i ] ),
                fixture->first_results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   FIND LAST
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( find_last, FindFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->strings[ i ].find_last( fixture->find[ i ] ),
                fixture->last_results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                     SPLIT
//------------------------------------------------------------------------------

class SplitFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String >                strings;
    std::vector< arc::str::UTF8String >                delimiters;
    std::vector< std::vector< arc::str::UTF8String > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            strings.push_back   ( "" );
            delimiters.push_back( "!" );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "Hello" );
            delimiters.push_back( "ጬ" );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "Hello" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "split this string" );
            delimiters.push_back( " " );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "split" );
            r.push_back( "this" );
            r.push_back( "string" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "." );
            delimiters.push_back( "." );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "" );
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "γειά σου Κόσμε!" );
            delimiters.push_back( "!" );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "γειά σου Κόσμε" );
            r.push_back( "" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "γειά σου Κόσμε!" );
            delimiters.push_back( "ε" );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "γ" );
            r.push_back( "ιά σου Κόσμ" );
            r.push_back( "!" );
            results.push_back( r );
        }

        {
            strings.push_back   ( "ጺጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
            delimiters.push_back( "ጺ" );
            std::vector< arc::str::UTF8String > r;
            r.push_back( "" );
            r.push_back( "ጹጸጷጶጵጴጳጲጱጰጯጮጭጬᚡ" );
            results.push_back( r );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( split, SplitFixture )
{
    std::vector< std::vector< arc::str::UTF8String > > all_elements;
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        std::vector< arc::str::UTF8String > elements =
                fixture->strings[ i ].split( fixture->delimiters[ i ] );
        all_elements.push_back( elements );
    }

    ARC_TEST_MESSAGE( "Checking elements length" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                all_elements[ i ].size(),
                fixture->results[ i ].size()
        );
    }

    ARC_TEST_MESSAGE( "Checking elements contents" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        std::size_t check_count = std::min(
                all_elements[ i ].size(),
                fixture->results[ i ].size()
        );

        for ( std::size_t j = 0; j < check_count; ++j )
        {
            ARC_CHECK_EQUAL(
                    all_elements[ i ][ j ],
                    fixture->results[ i ][ j ]
            );
        }
    }

    ARC_TEST_MESSAGE( "Checking empty delimiters" );
    ARC_FOR_EACH( it, fixture->strings )
    {
        ARC_CHECK_THROW(
                it->split( ""),
                arc::ex::ValueError
        );
    }
}

//------------------------------------------------------------------------------
//                               REMOVE DUPLICATES
//------------------------------------------------------------------------------

class RemoveDuplicatesFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > inputs;
    std::vector< arc::str::UTF8String > substrings;
    std::vector< arc::str::UTF8String > results;

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

ARC_TEST_UNIT_FIXTURE( remove_duplicates, RemoveDuplicatesFixture )
{
    for( std::size_t i = 0; i < fixture->inputs.size(); ++i )
    {
        fixture->inputs[ i ].remove_duplicates( fixture->substrings[ i ] );
        ARC_CHECK_EQUAL(
                fixture->inputs[ i ],
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                     IS INT
//------------------------------------------------------------------------------

class IsIntFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > ints;
    std::vector< arc::str::UTF8String > not_ints;

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

ARC_TEST_UNIT_FIXTURE( is_int, IsIntFixture )
{
    ARC_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->ints.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->ints[ i ].is_int() );
    }

    ARC_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_ints.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->not_ints[ i ].is_int() );
    }
}

//------------------------------------------------------------------------------
//                                    IS UINT
//------------------------------------------------------------------------------

class IsUintFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > uints;
    std::vector< arc::str::UTF8String > not_uints;

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

ARC_TEST_UNIT_FIXTURE( is_uint, IsUintFixture )
{
    ARC_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->uints.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->uints[ i ].is_uint() );
    }

    ARC_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_uints.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->not_uints[ i ].is_uint() );
    }
}

//------------------------------------------------------------------------------
//                                    IS FLOAT
//------------------------------------------------------------------------------

class IsFloatFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > floats;
    std::vector< arc::str::UTF8String > not_floats;

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

ARC_TEST_UNIT_FIXTURE( is_float, IsFloatFixture )
{
    ARC_TEST_MESSAGE( "Checking true cases" );
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->floats[ i ].is_float() );
    }

    ARC_TEST_MESSAGE( "Checking false cases" );
    for ( std::size_t i = 0; i < fixture->not_floats.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->not_floats[ i ].is_float() );
    }
}

//------------------------------------------------------------------------------
//                                   SUBSTRING
//------------------------------------------------------------------------------

class SubstringFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > strings;
    std::vector< std::size_t >                 indices;
    std::vector< std::size_t >                 lengths;
    std::vector< arc::str::UTF8String > results;
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

ARC_TEST_UNIT_FIXTURE( substring, SubstringFixture )
{
    ARC_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->strings[ i ].substring(
                        fixture->indices[ i ], fixture->lengths[ i ]
                ),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_THROW(
                fixture->strings[ i ].substring(
                        fixture->out_of_bounds[ i ], 10
                ),
                arc::ex::IndexOutOfBoundsError
        );
    }
}

//------------------------------------------------------------------------------
//                                 TO STD STRING
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_std_string, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->utf8_strings[ i ].to_std_string(),
                std::string( fixture->cstrings[ i ] )
        );
    }
}

//------------------------------------------------------------------------------
//                                    TO BOOL
//------------------------------------------------------------------------------

class ToBoolFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > valid;
    std::vector< bool >                   results;
    std::vector< arc::str::UTF8String > invalid;

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

ARC_TEST_UNIT_FIXTURE( to_bool, ToBoolFixture )
{
    ARC_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->valid[ i ].to_bool(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking invalid cases" );
    ARC_FOR_EACH( it, fixture->invalid )
    {
        ARC_CHECK_THROW( it->to_bool(), arc::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                    TO INT32
//------------------------------------------------------------------------------

class ToInt32Fixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > valid;
    std::vector< arc::int32 >           results;
    std::vector< arc::str::UTF8String > invalid;

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

ARC_TEST_UNIT_FIXTURE( to_int32, ToInt32Fixture )
{
    ARC_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->valid[ i ].to_int32(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking invalid cases" );
    ARC_FOR_EACH( it, fixture->invalid )
    {
        ARC_CHECK_THROW( it->to_int32(), arc::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   TO UINT32
//------------------------------------------------------------------------------

class ToUint32Fixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > valid;
    std::vector< arc::uint32 >          results;
    std::vector< arc::str::UTF8String > invalid;

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

ARC_TEST_UNIT_FIXTURE( to_uint32, ToUint32Fixture )
{
    ARC_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->valid[ i ].to_uint32(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking invalid cases" );
    ARC_FOR_EACH( it, fixture->invalid )
    {
        ARC_CHECK_THROW( it->to_uint32(), arc::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                    TO INT64
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_int64, ToInt32Fixture )
{
    ARC_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->valid[ i ].to_int64(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking invalid cases" );
    ARC_FOR_EACH( it, fixture->invalid )
    {
        ARC_CHECK_THROW( it->to_int64(), arc::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   TO UINT64
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_uint64, ToUint32Fixture )
{
    ARC_TEST_MESSAGE( "Checking valid cases" );
    for ( std::size_t i = 0; i < fixture->valid.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->valid[ i ].to_uint64(),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking invalid cases" );
    ARC_FOR_EACH( it, fixture->invalid )
    {
        ARC_CHECK_THROW( it->to_uint64(), arc::ex::ConversionDataError );
    }
}

//------------------------------------------------------------------------------
//                                   GET LENGTH
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_length, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->utf8_strings[ i ].get_length(),
                fixture->lengths[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                    IS EMPTY
//------------------------------------------------------------------------------

class IsEmptyFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > strings;
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

ARC_TEST_UNIT_FIXTURE( is_empty, IsEmptyFixture )
{
    for ( std::size_t i = 0; i < fixture->strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->strings[ i ].is_empty(),
                fixture->results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   GET SYMBOL
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_symbol, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_FOR_EACH( it, fixture->symbols[ i ] )
        {
            ARC_CHECK_EQUAL(
                    fixture->utf8_strings[ i ].get_symbol( it->first ),
                    it->second
            );
        }
    }
}

//------------------------------------------------------------------------------
//                                GET SYMBOL VALUE
//------------------------------------------------------------------------------

class GetSymbolValueFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::str::UTF8String       symbols;
    std::vector< arc::uint32 > values;

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

ARC_TEST_UNIT_FIXTURE( get_symbol_value, GetSymbolValueFixture )
{
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->symbols.get_symbol_value( i ),
                fixture->values[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                 GET CODE POINT
//------------------------------------------------------------------------------

class GetCodePointFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::str::UTF8String       symbols;
    std::vector< arc::uint32 > code_points;

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

ARC_TEST_UNIT_FIXTURE( get_code_point, GetCodePointFixture )
{
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->symbols.get_code_point( i ),
                fixture->code_points[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                        GET BYTE INDEX FOR SYMBOL INDEX
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_byte_index_for_symbol_index, IndexFixture )
{
    ARC_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->symbols.get_byte_index_for_symbol_index( i ),
                fixture->byte_indices[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    ARC_CHECK_THROW(
            fixture->symbols.get_byte_index_for_symbol_index( 58435 ),
            arc::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                GET SYMBOL WIDTH
//------------------------------------------------------------------------------

class GetSymbolWidthFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::str::UTF8String       symbols;
    std::vector< arc::uint32 > widths;

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

ARC_TEST_UNIT_FIXTURE( get_symbol_width, GetSymbolWidthFixture )
{
    ARC_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->symbols.get_symbol_width( i ),
                fixture->widths[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    ARC_CHECK_THROW(
            fixture->symbols.get_symbol_width( 832423 ),
            arc::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                    GET RAW
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_raw, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL( strcmp(
                fixture->utf8_strings[ i ].get_raw(),
                fixture->cstrings[ i ]
        ), 0 );
    }
}

//------------------------------------------------------------------------------
//                                GET BYTE LENGTH
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_byte_length, UTF8StringGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->utf8_strings.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->utf8_strings[ i ].get_byte_length(),
                strlen( fixture->cstrings[ i ] ) + 1
        );
    }
}

//------------------------------------------------------------------------------
//                        GET SYMBOL INDEX FOR BYTE INDEX
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_symbol_index_for_byte_index, IndexFixture )
{
    ARC_TEST_MESSAGE( "Checking values" );
    std::size_t symbol_index = 0;
    for ( std::size_t i = 0; i < fixture->symbols.get_byte_length() - 1; ++i )
    {
        if ( symbol_index < fixture->symbols.get_length() - 1 &&
             i >= fixture->byte_indices[ symbol_index + 1 ] )
        {
            ++symbol_index;
        }

        ARC_CHECK_EQUAL(
                fixture->symbols.get_symbol_index_for_byte_index( i ),
                symbol_index
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    ARC_CHECK_THROW(
            fixture->symbols.get_symbol_index_for_byte_index( 512 ),
            arc::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                 GET BYTE WIDTH
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_byte_width, GetSymbolWidthFixture )
{
    ARC_TEST_MESSAGE( "Checking values" );
    for ( std::size_t i = 0; i < fixture->symbols.get_length(); ++i )
    {
        std::size_t byte_index =
                fixture->symbols.get_byte_index_for_symbol_index( i );

        ARC_CHECK_EQUAL(
                fixture->symbols.get_byte_width( byte_index ),
                fixture->widths[ i ]
        );

        i += fixture->widths[ i ];
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    ARC_CHECK_THROW(
            fixture->symbols.get_byte_width( arc::str::npos ),
            arc::ex::IndexOutOfBoundsError
    );
}

//------------------------------------------------------------------------------
//                                 OPTIMISATIONS
//------------------------------------------------------------------------------

class OptimisationsFixture : public arc::test::Fixture
{
public:

    //--------------------------------ATTRIBUTES--------------------------------

    arc::str::UTF8String::Opt skip_valid;
    std::vector<const char*> valid_utf8;
    std::vector<const char*> invalid_utf8;

    arc::str::UTF8String::Opt fixed_width;
    std::vector<const char*> width_1;
    std::vector<const char*> width_mixed;

    // TODO: ASCII

    //--------------------------------FUNCTIONS---------------------------------

    void setup()
    {
        skip_valid.flags = arc::str::UTF8String::Opt::SKIP_VALID_CHECK;

        valid_utf8.push_back("");
        valid_utf8.push_back("Hello World");
        valid_utf8.push_back("a");
        valid_utf8.push_back(
            "This is a really long string, that just keeps on going on and on "
            "and on! It never seems to end, but just when you think that it "
            "will not end. It ends.\n\n\n\n\nNope still going here.\t\t\tThe "
            "end!\n\n\n\t\t\t"
        );
        valid_utf8.push_back("γειά σου Κόσμε");
        valid_utf8.push_back("this is a مزيج of text");
        valid_utf8.push_back("간");
        valid_utf8.push_back("𐂣");

        invalid_utf8.push_back("\x80");
        invalid_utf8.push_back("\x0A\x80");
        invalid_utf8.push_back("\xC2\x80\x80");
        invalid_utf8.push_back("\xC8\x02");
        invalid_utf8.push_back("\xE1\x80\x80\x80");
        invalid_utf8.push_back("\xE3\x06");
        invalid_utf8.push_back("\xEE\x80\xC3");
        invalid_utf8.push_back("\xFA\x80\x80\x80\x80");
        invalid_utf8.push_back("\xFA\xC4");
        invalid_utf8.push_back("\xFA\x80\x05");
        invalid_utf8.push_back("\xFA\x80\x80\xEE");

        fixed_width.flags = arc::str::UTF8String::Opt::FIXED_WIDTH;

        width_1.push_back("");
        width_1.push_back("Hello World");
        width_1.push_back("a");
        width_1.push_back(
            "This is a really long string, that just keeps on going on and on "
            "and on! It never seems to end, but just when you think that it "
            "will not end. It ends.\n\n\n\n\nNope still going here.\t\t\tThe "
            "end!\n\n\n\t\t\t"
        );
        width_1.push_back("abcdefgehijklmnopqrstuvwxyz1234567890");

        width_mixed.push_back("γειά σου Κόσμε");
        width_mixed.push_back("this is a مزيج of text");
        width_mixed.push_back("γειά σου Κόσμε");
        width_mixed.push_back("간");
    }
};

ARC_TEST_UNIT_FIXTURE(optimisations, OptimisationsFixture)
{
    ARC_TEST_MESSAGE("Testing valid UTF-8 with no optimisations");
    ARC_FOR_EACH(it_1, fixture->valid_utf8)
    {
        arc::str::UTF8String s(*it_1);
    }

    ARC_TEST_MESSAGE("Testing invalid UTF-8 with no optimisations");
    ARC_FOR_EACH(it_2, fixture->invalid_utf8)
    {
        ARC_CHECK_THROW(
                arc::str::UTF8String(*it_2),
                arc::ex::EncodingError
        );
    }

    ARC_TEST_MESSAGE("Testing valid UTF-8 with SKIP_VALID_CHECK");
    ARC_FOR_EACH(it_3, fixture->valid_utf8)
    {
        arc::str::UTF8String(*it_3, fixture->skip_valid);
    }

    ARC_TEST_MESSAGE("Testing invalid UTF-8 with SKIP_VALID_CHECK");
    ARC_FOR_EACH(it_4, fixture->invalid_utf8)
    {
        arc::str::UTF8String(*it_4, fixture->skip_valid);
    }

    ARC_TEST_MESSAGE("Testing 1 byte sized symbols with fixed width");
    ARC_FOR_EACH(it_5, fixture->width_1)
    {
        arc::str::UTF8String s(*it_5);
        arc::str::UTF8String s_opt(*it_5, fixture->fixed_width);

        ARC_CHECK_EQUAL(s_opt.get_length(), s.get_length());
    }

    ARC_TEST_MESSAGE("Testing mixed byte sized symbols with fixed width");
    ARC_FOR_EACH(it_6, fixture->width_mixed)
    {
        arc::str::UTF8String s(*it_6);
        arc::str::UTF8String s_opt(*it_6, fixture->fixed_width);

        ARC_CHECK_NOT_EQUAL(s_opt.get_length(), s.get_length());
    }
}

} // namespace anonymous
